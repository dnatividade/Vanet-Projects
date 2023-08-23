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
    } else {
        //stage 1 - Here the vehicle already have the link layer ID (myId)
    }
}


//This method is called when a VEHICLE receive a message
void TraCIDemo11p::onWSM(BaseFrame1609_4* frame)
{
    TraCIDemo11pMessage* wsm = check_and_cast<TraCIDemo11pMessage*>(frame);

    findHost()->getDisplayString().setTagArg("i", 1, "yellow"); //if message was received and readable, car color = green
    //Sometimes in the simulation we see the message hit a vehicle, but the car doesn't change color.
    //This is because the message arrived with errors and the vehicle was unable to decode the message.

    //if msg to me...
    if (messageToMe(wsm->getMulticastAddr())) {
        findHost()->getDisplayString().updateWith("r=30,green");
    }
}


//Handle the schedules
void TraCIDemo11p::handleSelfMsg(cMessage* msg)
{
    if (TraCIDemo11pMessage* wsm = dynamic_cast<TraCIDemo11pMessage*>(msg)) {
        //make something with the received message
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
