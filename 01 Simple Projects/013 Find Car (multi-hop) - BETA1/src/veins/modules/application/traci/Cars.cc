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
#include "veins/modules/application/traci/MsgFind_m.h"

using namespace veins;

Define_Module(veins::Cars);


void Cars::initialize(int stage) {
    DemoBaseApplLayer::initialize(stage);
    if (stage == 1) {
        if (myId == CAR1) {
            findHost()->getDisplayString().setTagArg("i", 1, "red");
            msgCreatedByMe = 1;
            MsgFind* findReq = new MsgFind();
            populateWSM(findReq, -1);
            findReq->setSenderAddress(myId);
            findReq->setType(FIND_REQUEST);
            findReq->setSrc(myId);
            findReq->setDst(CAR2);

            scheduleAt(TIME, findReq); //schedule the message to TIME
        }
    }
}


void Cars::onWSM(BaseFrame1609_4* frame) {
    if (MsgFind* find = check_and_cast<MsgFind*>(frame)) {

        if (find->getType() == FIND_CANCEL) {
            if (cancelSent == 0) {
                cancelSent = 1;
                cancelMsgRep = 1;
                find->setSenderAddress(myId);
                //scheduleAt(simTime()+0.5, find->dup());
                sendDelayedDown(find->dup(), uniform(0.01, 0.2));
            }
        }

        // if MsgFind-request...
        if (find->getType() == FIND_REQUEST) {
            //TODO
            findHost()->getDisplayString().setTagArg("i", 1, "yellow");
            //std::cout << "CAR:  " << myId << " | *FIND_REQUEST* received | SRC: " << find->getSrc() << " | DST: " << find->getDst() << " | SimTime: " << simTime() << endl; //print information

            // if it is me...
            if (myId == find->getDst()) {
                if (cancelMsgRep == 0) {
                    cancelMsgRep = 1;
                    findHost()->getDisplayString().setTagArg("i", 1, "yellow");
                    std::cout << "CAR:  " << myId << " | *I AM SRC* | SimTime: " << simTime() << endl; //print information
                    MsgFind* findRep = new MsgFind();
                    populateWSM(findRep, -1);
                    findRep->setSenderAddress(myId);
                    findRep->setType(FIND_REPLAY);
                    findRep->setSrc(myId);
                    findRep->setDst(find->getSrc());
                    sendDelayedDown(findRep, uniform(0.01, 0.2));
                }
            }

            // if it is not me
            else {
                int ttl = find->getTtl();
                ttl--;
                if (ttl > 0 and cancelMsgReq == 0) {
                    find->setTtl(ttl);
                    find->setSenderAddress(myId);
                    scheduleAt(simTime()+0.5, find->dup());
                    //sendDelayedDown(find->dup(), uniform(0.01, 0.2));
                }
            }
        }

        // if MsgFind-replay...
        else if (find->getType() == FIND_REPLAY) {

            cancelMsgReq = 1;

            // if it is me...
            if (myId == find->getDst()) {
                if (cancelSent == 0) {
                    cancelSent = 1 ;
                    findHost()->getDisplayString().setTagArg("i", 1, "green");
                    std::cout << "CAR:  " << myId << " | *CAR FOUND* | SimTime: " << simTime() << endl; //print information
                    MsgFind* findCanc = new MsgFind();
                    populateWSM(findCanc, -1);
                    findCanc->setSenderAddress(myId);
                    findCanc->setType(FIND_CANCEL);
                    findCanc->setSrc(myId);
                    findCanc->setDst(find->getSrc());
                    sendDelayedDown(findCanc, uniform(0.01, 0.2));
                }
            }

            // if it is not me
            else {
                int ttl = find->getTtl();
                ttl--;
                if (ttl > 0 and cancelMsgRep == 0) {
                    find->setTtl(ttl);
                    find->setSenderAddress(myId);
                    scheduleAt(simTime()+0.5, find->dup());
                    //sendDelayedDown(find->dup(), uniform(0.01, 0.2));
                }
            }
        }
    }
}


void Cars::handleSelfMsg(cMessage* msg) {
    if (MsgFind* find = dynamic_cast<MsgFind*>(msg)) {

        //if message created by me...
        if (msgCreatedByMe){
            sendDelayedDown(find, uniform(0.01, 0.2)); //send message to broadcast
        }

        // if message NOT created by me...
        else {
            if (find->getType() == FIND_REQUEST and cancelMsgReq == 0) {
            //if (cancelMsgFind == 0) {
                sendDelayedDown(find, uniform(0.01, 0.2)); //send message to broadcast
            }
            else if (find->getType() == FIND_REPLAY and cancelMsgRep == 0) {
                //if (cancelMsgFind == 0) {
                    sendDelayedDown(find, uniform(0.01, 0.2)); //send message to broadcast
            }

            else {
                delete find;
            }
        }

    }

    else {
        DemoBaseApplLayer::handleSelfMsg(msg);
    }
}
