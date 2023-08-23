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

void TraCIDemoRSU11p::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0) {
        //stage 0
    } else {
        //after stage 0
        TraCIDemo11pMessage* wsm = new TraCIDemo11pMessage(); //create a message called wssm
        populateWSM(wsm, -1, 0); //fill principal message fields [wsm = message] [-1 = send broadcast] [0 = any serial number]
        scheduleAt(simTime() + 2, wsm);//
        //sendDown(wsm); //send the message now
        //sendDelayedDown(wsm, 0.05); //send message with a fixed delay [0.05 seconds]
        //sendDelayedDown(wsm, 2 + uniform(0.01, 0.2)); //send message with a random delay [between 0.01 and 0.2 seconds]
    }
}


void TraCIDemoRSU11p::onWSM(BaseFrame1609_4* frame)
{
    TraCIDemo11pMessage* wsm = check_and_cast<TraCIDemo11pMessage*>(frame);

    // this rsu repeats the received traffic update in 2 seconds plus some random delay
    sendDelayedDown(wsm->dup(), 2 + uniform(0.01, 0.2));
}

void TraCIDemoRSU11p::handleSelfMsg(cMessage* msg)
{
    if (TraCIDemo11pMessage* wsm = dynamic_cast<TraCIDemo11pMessage*>(msg)) {
        sendDown(wsm->dup()); //send the message now
        //sendDelayedDown(wsm, 0.05); //send message with a fixed delay [0.05 seconds]
        //sendDelayedDown(wsm, 2 + uniform(0.01, 0.2)); //send message with a random delay [between 0.01 and 0.2 seconds]
        scheduleAt(simTime() + 2, wsm); //

    } else {
        DemoBaseApplLayer::handleSelfMsg(msg);

    }

}
