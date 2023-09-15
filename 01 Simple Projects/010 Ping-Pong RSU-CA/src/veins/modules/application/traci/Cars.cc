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

#include <veins/modules/application/traci/Cars.h>
#include "veins/modules/application/traci/Message_m.h"

using namespace veins;

Define_Module(veins::Cars);

void Cars::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    if (stage == 1) {
        if (myId == CAR1) { //node[0] = ID 22
            Message* wsm = new Message();
            populateWSM(wsm, RSU1); //RSU[0] = id 11
            wsm->setSenderAddress(myId);
            wsm->setDemoData("MSG from car!");
            scheduleAt(simTime() + 75, wsm); //schedule the message to 75s
        }
    }
}


void Cars::onWSM(BaseFrame1609_4* frame) {
    if (Message* wsm = check_and_cast<Message*>(frame)) {
        findHost()->getDisplayString().setTagArg("i", 1, "green");
    }
}

void Cars::handleSelfMsg(cMessage* msg) {
    if (Message* wsm = dynamic_cast<Message*>(msg)) {
        sendDelayedDown(wsm, uniform(0.01, 0.2)); //send message to RSU

    }
    else {
        DemoBaseApplLayer::handleSelfMsg(msg);
    }
}
