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

#include <veins/modules/application/traci/CA.h>
#include "veins/modules/application/traci/Message_m.h"

using namespace veins;

Define_Module(veins::CA);


void CA::onWSM(BaseFrame1609_4* frame) {
    if (Message* wsm = check_and_cast<Message*>(frame)) {
        // Print information about the received message
        std::cout << "CA:   " << myId << " | Message received... " << " | SimTime: " << simTime() << endl;
        std::cout << "Src:  " << wsm->getSenderAddress() << endl;
        std::cout << "Dst:  " << wsm->getRecipientAddress() << endl;
        std::cout << "DATA: " << wsm->getDemoData() << endl;
        std::cout << "-------------------------------------------" << endl;

        // Create a new message to send
        Message* newWSM = new Message();
        // Fill the fields
        populateWSM(newWSM, RSU1);
        newWSM->setSenderAddress(myId);
        // Custom msg data
        std::string msgData = "MSG created by CA ";
        msgData = msgData + std::to_string(myId);
        newWSM->setDemoData(msgData.c_str());
        // Send message with delay
        sendDelayedDown(newWSM, uniform(0.01, 0.2));


        /* Alternative: forward the received message sending via broadcast
          populateWSM(wsm, -1);
          wsm->setDemoData("Created by CA 16");
          wsm->setSenderAddress(myId);
          sendDelayedDown(wsm, uniform(0.01, 0.2));
        */
    }
}

