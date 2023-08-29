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

#include "veins/modules/application/traci/TraCIDemo11p.h"

#include "veins/modules/application/traci/TraCIDemo11pMessage_m.h"

using namespace veins;

Define_Module(veins::TraCIDemo11p);

int color = 0; //0=red; 1=green; 2=blue

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
    } else {
        //stage 1 - Here the vehicle already have the link layer ID (myId)

        //if myId is divisible by 4
        if (myId % 5 == 0) {
            TraCIDemo11pMessage* wsm = new TraCIDemo11pMessage(); //create a message called wsm
            populateWSM(wsm, 10, 1); //fill the principal message fields [wsm = message] [10 = send to RSU] [1 = any serial number]
            wsm->setSenderAddress(myId); //set source address
            wsm->setDemoData("ping"); //set msg content: "ping"
            scheduleAt(simTime() + 10, wsm); //Make an schedule for 10 seconds from now [using self messages]
        }
    }
}


//This method is called when a VEHICLE receive a message
void TraCIDemo11p::onWSM(BaseFrame1609_4* frame)
{
    TraCIDemo11pMessage* wsm = check_and_cast<TraCIDemo11pMessage*>(frame);

    //if received message = "ping"...
    if (strcmp(wsm->getDemoData(), "pong") == 0) {

        //color rotation - RGB
        if (color == 0) {
            findHost()->getDisplayString().updateWith("r=30,red"); //if message was received and readable, car circle radius = 30; color = red
            color = 1;
        }
        else if (color == 1) {
            findHost()->getDisplayString().updateWith("r=30,green"); //if message was received and readable, car circle radius = 30; color = green
            color = 2;
        }
        else if (color == 2) {
            findHost()->getDisplayString().updateWith("r=30,blue"); //if message was received and readable, car circle radius = 30; color = blue
            color = 0;
        }
        //////////////

        msgReceived = 1; //set Flag to cancel sending
        std::cout << "CAR " << myId << " | *pong* received from RSU!" << " | SimTime: " << simTime() << endl; //print information
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
            std::cout << "CAR " << myId << " | *ping* sent to RSU..." << " | SimTime: " << simTime() << endl; //print information
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
