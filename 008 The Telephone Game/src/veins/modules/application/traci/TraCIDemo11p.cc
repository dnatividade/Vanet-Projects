//
// Copyright (C) 2006-2011 Christoph Sommer <christoph.sommer@uibk.ac.at>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// SPDX-License-Identifier: GPL-2.0-or-later
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

/*//Telephone game (Telefone sem fio)
 * node[0] -> node[1] -> node[2] -> node[3] -> ... -> node[last]
 */


#include "veins/modules/application/traci/TraCIDemo11p.h"

#include "veins/modules/application/traci/TraCIDemo11pMessage_m.h"

using namespace veins;

Define_Module(veins::TraCIDemo11p);

int color = 0; //0=green; 1=yellow; 2=blue; 3=white /*Brazil colors*/


//My FUnctions

//This method selects the car color
void TraCIDemo11p::selectCarColor() {
    if (color == 0) {
        findHost()->getDisplayString().setTagArg("i", 1, "green");  //car color = green
        color = 1;
    }
    else if (color == 1) {
        findHost()->getDisplayString().setTagArg("i", 1, "yellow");  //car color = yellow
        color = 2;
    }
    else if (color == 2) {
        findHost()->getDisplayString().setTagArg("i", 1, "blue");  //car color = blue
        color = 3;
    }
    else {
        findHost()->getDisplayString().setTagArg("i", 1, "white");  //car color = white
        color = 0;
    }
}


//This method sends a ACK from 'src' to 'dst'
void TraCIDemo11p::sendAck(int src, int dst) {
    TraCIDemo11pMessage* ack = new TraCIDemo11pMessage();
    populateWSM(ack, dst); //send back message to car - link layer ID get from wsm message ********
    ack->setSenderAddress(myId); //set source address
    ack->setDemoData("ack"); //set data = "ack"
    sendDelayedDown(ack, uniform(0.01, 0.2)); //send message with a random delay [between 0.01 and 0.2 seconds]
    //std::cout << "CAR " << myId << "| ack sent to RSU " << " | SimTime: " << simTime() << endl; //print information
}


//This method changes the message fields to forward to another node
void TraCIDemo11p::forwardWsm(TraCIDemo11pMessage* wsm) {
    wsm->setRecipientAddress(myId+6); //set new destination
    wsm->setSerial(wsm->getSerial() + 1); //set a sequential number; start with 1
    wsm->setSenderAddress(myId); //set source address
    wsm->setDemoData("Forward this message..."); //set msg content
    sendDelayedDown(wsm->dup(), uniform(0.01, 0.2)); //send message with a random delay [between 0.01 and 0.2 seconds]
    std::cout << "CAR " << myId << " | sent msg to CAR: " << wsm->getRecipientAddress() << " | SimTime: " << simTime() << endl; //print information
}


//Two stages execution: stage 0; stage 1
//This method is called 2 times when the VEHICLE is created
void TraCIDemo11p::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0) {
        //stage 0 - Here the vehicles still do not have the link layer id (myId)
        sentMessage = false;
        lastDroveAt = simTime();
        currentSubscribedServiceId = -1;

        findHost()->getDisplayString().setTagArg("i", 1, "red");  //car color = red
    }

    else {
        //stage 1 - Here the vehicle already have the link layer ID (myId)
        //if myId is 16 (node[0]), send the message to RSU...
        if (myId  == 16) {
            TraCIDemo11pMessage* wsm = new TraCIDemo11pMessage(); //create a message called wsm
            populateWSM(wsm, myId+6); //fill the principal message fields [wsm = message] [10 = send to RSU] [1 = any serial number]
            wsm->setSerial(1); //set a sequencial number; start with 1
            wsm->setSenderAddress(myId); //set source address
            wsm->setDemoData("Forward this message..."); //set msg content
            scheduleAt(simTime() + 250, wsm); //Make an schedule for 250 seconds from now [using self messages]
        }
    }
}


//This method is called when a VEHICLE receive a message
void TraCIDemo11p::onWSM(BaseFrame1609_4* frame)
{
    TraCIDemo11pMessage* wsm = check_and_cast<TraCIDemo11pMessage*>(frame);

    //if received ack...
    if (strcmp(wsm->getDemoData(), "ack") == 0) {
       msgReceived = 1;
    }

    //if received message...
    else {
        std::cout << "CAR " << myId << " | received the msg *" << wsm->getDemoData() << "* | Serial: " << std::to_string(wsm->getSerial()) << " | from CAR: " << wsm->getSenderAddress() << " | SimTime: " << simTime() << endl; //print information

        //select the car color
        selectCarColor();

        //send a ack to car: sedAck(SRC, DST)
        sendAck(myId, wsm->getSenderAddress());

        //forward the message
        forwardWsm(wsm);
        scheduleAt(simTime() + 2, wsm->dup()); //Make an schedule for 250 seconds from now [using self messages]
    }
}


//Handle the schedules
void TraCIDemo11p::handleSelfMsg(cMessage* msg)
{
    if (TraCIDemo11pMessage* wsm = dynamic_cast<TraCIDemo11pMessage*>(msg)) {
        //if not received ack (confirmation message), continue sending...
        if (msgReceived == 0) {
            //sendDown(wsm->dup()); //send the message now
            //sendDelayedDown(wsm, 0.05); //send message with a fixed delay [0.05 seconds]
            sendDelayedDown(wsm->dup(), uniform(0.01, 0.2)); //send message with a random delay [between 0.01 and 0.2 seconds]
            scheduleAt(simTime() + 2, wsm); //Make an schedule for 2 seconds from now [using self messages]
            std::cout << "CAR " << myId << " | sent msg to CAR: " << wsm->getRecipientAddress() << " | SimTime: " << simTime() << endl; //print information
        }

        //if already received ack (confirmation message), stop sending and delete the message!
        else {
            delete(wsm); //delete the message
        }
    }

    else {
        DemoBaseApplLayer::handleSelfMsg(msg);
    }
}

void TraCIDemo11p::handlePositionUpdate(cObject* obj)
{
    DemoBaseApplLayer::handlePositionUpdate(obj);

    //if stopped vehicle
    if (mobility->getSpeed() < 1) {
        //vehicle stopped for at least 10s?
        if (simTime() - lastDroveAt >= 10 && sentMessage == false) {
            findHost()->getDisplayString().setTagArg("i", 1, "red");  //car color = red
        }
    }

    //if running vehicle
    else {
        lastDroveAt = simTime();
    }
}
