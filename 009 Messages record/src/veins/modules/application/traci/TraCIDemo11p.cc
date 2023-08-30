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

//used in CRC32 function (//https://stackoverflow.com/a/25018742)
#include <zlib.h>

using namespace veins;

Define_Module(veins::TraCIDemo11p);


/* My Functions
 * @author: dnatividade
 */
unsigned long TraCIDemo11p::hashCRCMsg(TraCIDemo11pMessage* wsm){
    //https://stackoverflow.com/a/25018742
    unsigned long  crc = crc32(0L, Z_NULL, 0);
    //get message fields
    int serialWsm = wsm->getSerial();
    LAddress::L2Type srcWsm = wsm->getSenderAddress();
    std::string dataWsm = wsm->getDemoData();

    /*concatenate all message fields to compute hash
     * serial(int)  +  sender address(long)  +  demoData(string)
     * if not using serial, put 0
     */
    std::string allWsmFields = std::to_string(serialWsm) + std::to_string(srcWsm) + dataWsm;
    //compute hash (for simplicity i am using CRC32 as hash function)
    //https://stackoverflow.com/a/25018742
    crc = crc32(crc, (const unsigned char*)allWsmFields.c_str(), strlen(allWsmFields.c_str()));

    return crc;
}


//Store received message into "Message Table"
void TraCIDemo11p::storeMsg(TraCIDemo11pMessage* wsm, unsigned long crc) {
    //get message fields
    int serialWsm = wsm->getSerial();
    LAddress::L2Type srcWsm = wsm->getSenderAddress();
    std::string dataWsm = wsm->getDemoData();

    msgRecord wsm1 = { serialWsm, srcWsm, dataWsm };
    msgRec[crc] = wsm1;
}


//Print all messages received
void TraCIDemo11p::printAllReceivMsg(void) {
    std::map<unsigned long, msgRecord>::iterator it;
    std::cout << "Received Messages" << myId << endl;
    std::cout << "MyID:        " << myId << endl;
    for(it=msgRec.begin(); it!=msgRec.end(); ++it){
        std::cout << "Hash(CRC32): " << it->first << " | " << "MSG content: " << it->second.data << endl;
        std::cout << "serial >>>>> " << it->second.serial << endl;
        std::cout << "src ID >>>>> " << it->second.srcId << endl;
        std::cout << "-------------" << endl;
    }
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


//This method is called when the vehicle exits the simulation
void TraCIDemo11p::finish() {
    if (myId == 16) {
        printAllReceivMsg();
    }
}

//This method is called when a VEHICLE receive a message
void TraCIDemo11p::onWSM(BaseFrame1609_4* frame)
{
    TraCIDemo11pMessage* wsm = check_and_cast<TraCIDemo11pMessage*>(frame);

    findHost()->getDisplayString().setTagArg("i", 1, "green"); //if message was received and readable, car color = green
    //Sometimes in the simulation we see the message hit a vehicle, but the car doesn't change color.
    //This is because the message arrived with errors and the vehicle was unable to decode the message.

    //std::cout << "CAR " << myId << " | received the msg *" << wsm->getDemoData() << "* | Serial: " << std::to_string(wsm->getSerial()) << " | from CAR: " << wsm->getSenderAddress() << " | SimTime: " << simTime() << endl; //print information

    //create CRC32 (used as hash function)
    unsigned long crc = hashCRCMsg(wsm);
    //store message in MAP
    storeMsg(wsm, crc);

    //DEBUG - print messages arriving
    /*
    if (myId == 16) {
        //DEBUG
        std::cout << "MyID:        " << myId << endl;
        std::cout << "Hash(CRC32): " << crc << endl;
        std::cout << "MSG content: " << msgRec[crc].data << endl;
        std::cout << "serial >>>>> " << msgRec[crc].serial << endl;
        std::cout << "src ID >>>>> " << msgRec[crc].srcId << endl << endl;
    }
    */
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
