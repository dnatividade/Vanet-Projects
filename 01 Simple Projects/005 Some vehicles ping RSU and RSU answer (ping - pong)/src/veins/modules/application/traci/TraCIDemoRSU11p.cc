//
// Copyright (C) 2016 David Eckhoff <david.eckhoff@fau.de>
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

#include "veins/modules/application/traci/TraCIDemoRSU11p.h"

#include "veins/modules/application/traci/TraCIDemo11pMessage_m.h"

using namespace veins;

Define_Module(veins::TraCIDemoRSU11p);


//Two stages execution: stage 0; stage 1
//This method is called 2 times when the RSU is created
void TraCIDemoRSU11p::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0) {
        //stage 0 - Here the RSU still do not have the link layer id (myId)
    } else {
        //stage 1 - Here the vehicle already have the link layer ID (myId)
    }
}


//This method is called when a RSU receive a message
void TraCIDemoRSU11p::onWSM(BaseFrame1609_4* frame)
{
    TraCIDemo11pMessage* wsm = check_and_cast<TraCIDemo11pMessage*>(frame);

    //if received message = "msg received"...
    if (strcmp(wsm->getDemoData(), "ping") == 0) {
        std::cout << "RSU | *ping* received from car: " << wsm->getSenderAddress() << " | SimTime: " << simTime() << endl; //print information


        //create "pong" message to send back to RSU
        TraCIDemo11pMessage* ack = new TraCIDemo11pMessage();
        populateWSM(ack, wsm->getSenderAddress(), 1); //send back message to car - link layer ID get from wsm message
        ack->setSenderAddress(myId); //set source address
        ack->setDemoData("pong");
        sendDelayedDown(ack, uniform(0.01, 0.2)); //send message with a random delay [between 0.01 and 0.2 seconds]
        std::cout << "RSU | *pong* sent to car:       " << wsm->getSenderAddress() << " | SimTime: " << simTime() << endl; //print information
    }
}


//Handle the schedules
void TraCIDemoRSU11p::handleSelfMsg(cMessage* msg)
{
    if (TraCIDemo11pMessage* wsm = dynamic_cast<TraCIDemo11pMessage*>(msg)) {
        //if not received ack (confirmation message), continue sending...
        if (msgReceived == 0) {
            sendDown(wsm->dup()); //send the message now
            //sendDelayedDown(wsm, 0.05); //send message with a fixed delay [0.05 seconds]
            //sendDelayedDown(wsm, uniform(0.01, 0.2)); //send message with a random delay [between 0.01 and 0.2 seconds]
            scheduleAt(simTime() + 2, wsm); //Make an appointment for 2 seconds from now [using self messages]
            std::cout << "RSU | Message sent to vehicle..." << " | SimTime: " << simTime() << endl; //print information
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
