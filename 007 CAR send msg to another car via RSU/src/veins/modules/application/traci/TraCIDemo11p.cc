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
//App: @dnat

#include "veins/modules/application/traci/TraCIDemo11p.h"

#include "veins/modules/application/traci/TraCIDemo11pMessage_m.h"

using namespace veins;

Define_Module(veins::TraCIDemo11p);

int color = 0; //0=red; 1=green; 2=blue

//My Functions

//return: 0=NO, msg not addressed to me; 1=YES, msg addressed to me
int TraCIDemo11p::messageToMe(std::string multicastAddr) {
    int res = 0;
    //split multicast string
    std::stringstream ss(multicastAddr);
    std::string addr;
    while (getline(ss,  addr, ';'))
        //if myId is in multicast field
        if (std::strcmp(addr.c_str(), std::to_string(myId).c_str()) == 0) {
            res = 1;
        }
    return res;
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
    }

    else {
        //stage 1 - Here the vehicle already have the link layer ID (myId)

        //node[0] 16 -> node[45] 285
        //if myId is 16 (node[0]), dend the message to RSU...
        if (myId  == 16) {
            TraCIDemo11pMessage* wsm = new TraCIDemo11pMessage(); //create a message called wsm
            populateWSM(wsm, 10, 1); //fill the principal message fields [wsm = message] [10 = send to RSU] [1 = any serial number]
            wsm->setSenderAddress(myId); //set source address
            wsm->setSrc(myId); //set source address (message source)
            wsm->setDst(286); //set final destination address (message destination) - node[45] ID: 286
            wsm->setDemoData("Any message"); //set msg content: "ping"
            scheduleAt(simTime() + 10, wsm); //Make an schedule for 10 seconds from now [using self messages]
        }
    }
}


//This method is called when a VEHICLE receive a message
void TraCIDemo11p::onWSM(BaseFrame1609_4* frame)
{
    TraCIDemo11pMessage* wsm = check_and_cast<TraCIDemo11pMessage*>(frame);

    //if received message = "ping"...
    if (strcmp(wsm->getDemoData(), "ack") == 0) {

       findHost()->getDisplayString().updateWith("r=30,green"); //if message was received and readable, car circle radius = 30; color = green
       msgReceived = 1;

        std::cout << "CAR " << myId << " | received the ack from RSU!" << " | SimTime: " << simTime() << endl; //print information
    }

    else {
        findHost()->getDisplayString().updateWith("r=30,blue"); //if message was received and readable, car circle radius = 30; color = blue
        std::cout << "CAR " << myId << " | received the msg *" << wsm->getDemoData() << "* from RSU!" << " | SimTime: " << simTime() << endl; //print information

        //send a ack to car
        TraCIDemo11pMessage* ack = new TraCIDemo11pMessage();
        populateWSM(ack, wsm->getSenderAddress(), 1); //send back message to car - link layer ID get from wsm message ********
        ack->setSenderAddress(myId); //set source address
        ack->setDemoData("ack"); //set dato = "ack"
        sendDelayedDown(ack, uniform(0.01, 0.2)); //send message with a random delay [between 0.01 and 0.2 seconds]
        std::cout << "CAR " << myId << "| ack sent to RSU " << " | SimTime: " << simTime() << endl; //print information
    }
}


//Handle the schedules
void TraCIDemo11p::handleSelfMsg(cMessage* msg)
{
    if (TraCIDemo11pMessage* wsm = dynamic_cast<TraCIDemo11pMessage*>(msg)) {
        //if not received ack (confirmation message), continue sending...
        if (msgReceived == 0) {
            sendDown(wsm->dup()); //send the message now
            //sendDelayedDown(wsm, 0.05); //send message with a fixed delay [0.05 seconds]
            //sendDelayedDown(wsm, uniform(0.01, 0.2)); //send message with a random delay [between 0.01 and 0.2 seconds]
            scheduleAt(simTime() + 2, wsm); //Make an schedule for 2 seconds from now [using self messages]
            std::cout << "CAR " << myId << " | sent msg to RSU..." << " | SimTime: " << simTime() << endl; //print information
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
