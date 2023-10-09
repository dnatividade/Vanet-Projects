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

/*
 * Simple flooding to find a car
 */


#include <veins/modules/application/traci/Cars.h>
#include "veins/modules/application/traci/MsgFind_m.h"
#include "veins/modules/application/traci/MsgData_m.h"

using namespace veins;

Define_Module(veins::Cars);

/*
 * @dnat
 * Check msg ID into the idVector
 */
bool Cars::msgVector(simtime_t idToCheck) {
    bool idExists = false;
    for (const simtime_t& id : idVector) {
        if (id == idToCheck) {
            idExists = true;
            break;
        }
    }
    // IF ID not exists, add
    if (!idExists) {
        idVector.push_back(idToCheck);
        //std::cout << "#" << myId << " ID add: " << idToCheck << endl; //DEBUG ONLY
    }

    //DEBUG ONLY
    /*
    else {
        std::cout << "ID alredy exists into the vector." << std::endl;
    }
    */

    return idExists;
}


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
            //schedule the message to TIME
            scheduleAt(TIME, findReq);
        }
    }
}


void Cars::onWSM(BaseFrame1609_4* frame) {

    if (MsgFind* find = dynamic_cast<MsgFind*>(frame)) {

        // ***********************
        // *** MSG FIND-CANCEL ***
        // ***********************
        if (find->getType() == FIND_CANCEL) {
            if (cancelSent == 0) {
                cancelSent = 1;
                cancelMsgRep = 1;
                find->setSenderAddress(myId);
                sendDelayedDown(find->dup(), uniform(DELAY_1, DELAY_2));
            }
        }

        // ************************
        // *** MSG FIND-REQUEST ***
        // ************************
        // if MsgFind-request...
        if (find->getType() == FIND_REQUEST) {
            findHost()->getDisplayString().setTagArg("i", 1, "yellow");
            //std::cout << "CAR:  " << myId << " | *FIND_REQUEST* received | SRC: " << find->getSrc() << " | DST: " << find->getDst() << " | SimTime: " << simTime() << endl; //print information

            // if it is me...
            if (myId == find->getDst()) {
                if (cancelMsgRep == 0) {
                    cancelMsgRep = 1;
                    //findHost()->getDisplayString().setTagArg("i", 1, "yellow");
                    findHost()->getDisplayString().updateWith("r=30,green");
                    std::cout << "CAR:  " << myId << " | *I AM HERE* | SimTime: " << simTime() << endl; //print information

                    // //////////////////////
                    // Create first Msg-Reply
                    // //////////////////////
                    MsgFind* findRep = new MsgFind();
                    populateWSM(findRep, -1);
                    findRep->setId(simTime()); //set message serial (current simulation time)
                    findRep->setSenderAddress(myId);
                    findRep->setType(FIND_REPLAY);
                    findRep->setSrc(myId);
                    findRep->setDst(find->getSrc());
                    sendDelayedDown(findRep, uniform(DELAY_1, DELAY_2));
                }
            }

            // if it is not me
            else {
                if (!msgVector(find->getId())) {
                    int ttl = find->getTtl();
                    ttl--; //decrement ttl
                    if (ttl > 0 and cancelMsgReq == 0) {
                        find->setTtl(ttl);
                        find->setSenderAddress(myId);
                        scheduleAt(simTime() + DELAY_FW, find->dup());
                    }
                }
            }
        }

        // ***********************
        // *** MSG FIND-REPLAY ***
        // ***********************
        // IF MsgFind-replay...
        else if (find->getType() == FIND_REPLAY) { //else MSG-FIND-Replay
            cancelMsgReq = 1;

            // IF it is ME...
            if (myId == find->getDst()) {
                if (cancelSent == 0) {
                    cancelSent = 1 ;
                    //findHost()->getDisplayString().setTagArg("i", 1, "green");
                    findHost()->getDisplayString().updateWith("r=30,green");
                    std::cout << "CAR:  " << myId << " | *CAR FOUND* | SimTime: " << simTime() << endl; //print information
                    std::cout << "Hops: " << find->getHops() << endl;

                    // MSG Find-Cancel
                    MsgFind* findCanc = new MsgFind();
                    populateWSM(findCanc, -1);
                    findCanc->setSenderAddress(myId);
                    findCanc->setType(FIND_CANCEL);
                    findCanc->setSrc(myId);
                    findCanc->setDst(find->getSrc());
                    sendDelayedDown(findCanc, uniform(DELAY_1, DELAY_2));
                    //sendDown(findCanc);

                    // MSG Data
                    // /////////////////////////////////////////////////////////////////////////////////////////////
                    MsgData* wsm = new MsgData();

                    std::string hops = find->getHops(); //get hops
                    int nextHop;
                    size_t pos = hops.find(';'); // Encontre a posição do primeiro ';'
                    if (pos != std::string::npos) {
                        std::string firstNumber = hops.substr(0, pos); // Use substr para extrair o primeiro número da string
                        std::istringstream iss(firstNumber); // Converta o primeiro número para um inteiro
                        iss >> nextHop;
                        hops = hops.substr(pos + 1); // Atualize a string para remover o primeiro número
                    } else {
                        nextHop = 0; // Se não houver ';', a string está vazia e nextHop é 0
                        hops = "";
                    }

                    populateWSM(wsm, nextHop);
                    wsm->setSenderAddress(myId);
                    wsm->setType(0);
                    wsm->setSrc(myId);
                    wsm->setDst(find->getSrc());
                    wsm->setHops(hops.c_str());
                    wsm->setData(PAYLOAD);
                    std::cout << "Sending MSG DATA... | Dst: " << nextHop << " | SimTime(): " << simTime() << endl;
                    sendDelayedDown(wsm, uniform(DELAY_1, DELAY_2));
                    //sendDown(wsm);
                    // /////////////////////////////////////////////////////////////////////////////////////////////
                }
            }

            // IF it is NOT me
            else {
                if (!msgVector(find->getId())) {
                    int ttl = find->getTtl();
                    ttl--; //decrement ttl
                    if (ttl > 0 and cancelMsgRep == 0) {
                        find->setTtl(ttl);
                        find->setSenderAddress(myId);
                        std::string hops = find->getHops();

                        hops = std::to_string(myId) + ";" + hops; //new HOP + old hops (this order is important!)

                        find->setHops(hops.c_str());
                        scheduleAt(simTime() + DELAY_FW, find->dup());
                        //sendDelayedDown(find->dup(), uniform(0.01, 0.2));
                    }
                }
            }
        } //end else MSG-FIND-Replay
    } //end MsgFind type



    else if (MsgData* wsm = dynamic_cast<MsgData*>(frame)) {

        //IF it is NOT me...
        if (wsm->getDst() != myId) {

            findHost()->getDisplayString().setTagArg("i", 1, "blue");

            std::string hops = wsm->getHops(); //get hops
            std::cout << "Hops: " << hops << endl << endl;
            int nextHop;
            size_t pos = hops.find(';'); // Encontre a posição do primeiro ';'
            if (pos != std::string::npos) {
                std::string firstNumber = hops.substr(0, pos); // Use substr para extrair o primeiro número da string
                std::istringstream iss(firstNumber); // Converta o primeiro número para um inteiro
                iss >> nextHop;
                hops = hops.substr(pos + 1); // Atualize a string para remover o primeiro número
            } else {
                nextHop = 0; // Se não houver ';', a string está vazia e nextHop é 0
                hops = "";
            }

            //hop list is NOT empty, send to nextHop
            if (nextHop != 0)
                populateWSM(wsm, nextHop);
            //hop list is empty, send to DST
            else
                populateWSM(wsm, wsm->getDst());

            wsm->setSenderAddress(myId);
            wsm->setType(0);
            wsm->setHops(hops.c_str());
            sendDelayedDown(wsm->dup(), uniform(0.01, 0.2));
            std::cout << "CAR: " << myId << " | Forwarding MSG DATA to: " << wsm->getRecipientAddress() << " | SimTime: " << simTime() << endl;
        }

        // IF its is ME..
        else {
            findHost()->getDisplayString().updateWith("r=30,blue");
            std::cout << "CAR: " << myId << " | **MSG DATA RECEIVED**" << " | SimTime: " << simTime() << endl;
            std::cout << ">> " << wsm->getData() << endl << endl;
        }
    } //end MsgData type
}


void Cars::handleSelfMsg(cMessage* msg) {

    //if (MsgFind* find = check_and_cast<MsgFind*>(msg)) {
    if (MsgFind* find = dynamic_cast<MsgFind*>(msg)) {

        //IF message created by ME...
        if (msgCreatedByMe){
            findHost()->getDisplayString().updateWith("r=30,red");
            find->setId(simTime()); //set message serial (current simulation time)
            std::cout << "CAR:  " << myId << " | *FINDING CAR* | ID: " << find->getDst() << " | SimTime: " << simTime() << endl; //print information
            sendDelayedDown(find, uniform(DELAY_1, DELAY_2)); //send message to broadcast
        }

        // if message NOT created by me...
        else {
            if (find->getType() == FIND_REQUEST and cancelMsgReq == 0) {
            //if (cancelMsgFind == 0) {
                sendDelayedDown(find, uniform(DELAY_1, DELAY_2)); //send message to broadcast
            }
            else if (find->getType() == FIND_REPLAY and cancelMsgRep == 0) {
                //if (cancelMsgFind == 0) {
                    sendDelayedDown(find, uniform(DELAY_1, DELAY_2)); //send message to broadcast
            }

            else {
                delete find; //delete message
            }
        }

    }

    //else if (MsgData* wsm = check_and_cast<MsgData*>(msg)) {

    //}

    /*
      else {
        DemoBaseApplLayer::handleSelfMsg(msg);
    }*/
}
