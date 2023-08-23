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
        TraCIDemo11pMessage* wsm = new TraCIDemo11pMessage(); //create a message called wsm

        //send message to node[3] - nic layer ID 34
        populateWSM(wsm, 34, 0); //fill the principal message fields [wsm = message] [34 = send a message to vehicle ID=34] [0 = any serial number]
        scheduleAt(simTime() + 65, wsm); //Make an appointment for 65 seconds from now [using self messages]
    }
}


//This method is called when a RSU receive a message
void TraCIDemoRSU11p::onWSM(BaseFrame1609_4* frame)
{
    TraCIDemo11pMessage* wsm = check_and_cast<TraCIDemo11pMessage*>(frame);
}


//Handle the schedules
void TraCIDemoRSU11p::handleSelfMsg(cMessage* msg)
{
    if (TraCIDemo11pMessage* wsm = dynamic_cast<TraCIDemo11pMessage*>(msg)) {
        sendDown(wsm->dup()); //send the message now
        //sendDelayedDown(wsm, 0.05); //send message with a fixed delay [0.05 seconds]
        //sendDelayedDown(wsm, uniform(0.01, 0.2)); //send message with a random delay [between 0.01 and 0.2 seconds]
        delete(wsm); //delete the message

    } else {
        DemoBaseApplLayer::handleSelfMsg(msg);
    }
}
