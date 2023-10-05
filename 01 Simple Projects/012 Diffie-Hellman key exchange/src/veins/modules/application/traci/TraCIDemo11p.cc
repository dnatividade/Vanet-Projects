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
//@dnat

/*
 * ALICE send a message to BOB with selected Diffie-Hellman parameters: P, G, step_1 (computed)
 * BOB reply ALICE with the same parameters P and G. BOB send your step_1 (computed)
 * Both compute the same secret KEY!
 *
 * OBS.: Using only bigint.h class to handle with Big Integers
 */

#include "veins/modules/application/traci/TraCIDemo11p.h"
#include "veins/modules/application/traci/MSG_DH_m.h"

// /////////////////////////////////////////////// //
// BEGIN - CHANGE HERE YOUR OWN PARAMETERS - BEGIN //
//Define ALICE and BOB address
#define ALICE    16
#define BOB      40
//Define Diffie-Hellman parameters
#define G        4373
#define P        1223
#define K_ALICE  1069
#define K_BOB    941
// END - CHANGE HERE YOUR OWN PARAMETERS - END //
// /////////////////////////////////////////////// //


//Define types
const int MSG_SENT = 0;
const int MSG_RECV = 1;


using namespace veins;

Define_Module(veins::TraCIDemo11p);


/*
 * Print sent and received message
 */
void TraCIDemo11p::printMSG(int carId, int step, int g, int p, int myQ, int inOut) {
    std::cout << "#" << myId;

    if (inOut == MSG_SENT)
        std::cout << " === > ";
    else
        std::cout << " < === ";

    std::cout << "| Msg step: " << step << " | G: " << g << " | P: " << p << " | Q: " << myQ << " |" << endl << endl;
}


/*
 * Compute DH step 1
 */
int TraCIDemo11p::DH_computeMyQ(int g, int p, int myK) {
    //compute: g^myK MOD p

    bigint g2(to_bigint(g));
    bigint p2(to_bigint(p));
    bigint myK2(to_bigint(myK));

    bigint powTmp(0);
    powTmp = big_pow(g2, myK2);
    bigint myQBigint(0);
    myQBigint = powTmp % p2;
    std::stringstream ss;
    ss << myQBigint;
    int myQInt;
    ss >> myQInt;

    return myQInt; //return the step_1
}


/*
 * Compute DH step 2
 */
int TraCIDemo11p::DH_computeKey(int your_q, int myk, int p) {
    //compute: your_g^myK MOD p

    bigint your_q2(to_bigint(your_q));
    bigint myk2(to_bigint(myk));
    bigint p2(to_bigint(p));

    bigint powTmp(0);
    powTmp = big_pow(your_q2, myk2);

    bigint keyBigInt(0);
    keyBigInt = powTmp % p2;
    std::stringstream ss;
    ss << keyBigInt;
    int keyInt;
    ss >> keyInt;

    return keyInt; //return the step_2 = KEY
}


void TraCIDemo11p::initialize(int stage) {
    DemoBaseApplLayer::initialize(stage);

    if (stage == 1) {
        // if ALICE: schedule a message to send to BOB
        if (myId == ALICE) {
            MSG_DH* wsm = new MSG_DH();  //create a new message
            populateWSM(wsm, BOB);       //populate message with BOB destination address
            wsm->setSenderAddress(myId); //set myId
            wsm->setStep(1);   //set the first step of exchanging messages

            int g = G;         //get G (defined at the beginning of the code)
            int p = P;         //get P (defined at the beginning of the code)
            myK   = K_ALICE; ; //get my private temporary key (defined at the beginning of the code)
            myQ   = DH_computeMyQ(g, p, myK); //compute step_1

            wsm->setG(g);     //set G
            wsm->setP(p);     //set P
            wsm->setMyQ(myQ); //set my computed step_1
            scheduleAt(simTime() + 85, wsm); //schedule the message to NOW + 85s
        }
    }
}


void TraCIDemo11p::onWSM(BaseFrame1609_4* frame) {

    //if message is a MSG_DH
    if (MSG_DH* wsm = check_and_cast<MSG_DH*>(frame)) {

        //BOB receives: computes the KEY and send his parameters to ALICE
        //(compute step_1 and step_2)
        if (wsm->getStep() == 1) {
            MSG_DH* wsm2 = new MSG_DH(); //create a new message
            populateWSM(wsm2, wsm->getSenderAddress()); //populate the message with ALICE destination address
            wsm2->setSenderAddress(myId);
            wsm2->setStep(2);

            int g = wsm->getG(); //get G from message
            int p = wsm->getP(); //get P from message
            int your_q = wsm->getMyQ(); //get ALICE computed step_1 from message
            myK = K_BOB; //get my private temporary key

            myQ = DH_computeMyQ(g, p, myK); //compute step_1
            key = DH_computeKey(your_q, myK, p); //compute step_2

            wsm2->setG(g);     //set G into the message
            wsm2->setP(p);     //set P into the message
            wsm2->setMyQ(myQ); //set computed step_1 into the message
            sendDelayedDown(wsm2, uniform(0.01, 0.1)); //send the message

            findHost()->getDisplayString().setTagArg("i", 1, "green"); //change car color
            printMSG(myId, wsm2->getStep(), wsm2->getG(), wsm2->getP(), wsm2->getMyQ(), 1); //print information
            std::cout << "#" << myId << " | Computed key: " << key << endl; //print information

        }

        //ALICE receives: computes the KEY
        //(compute step_2))
        else if (wsm->getStep() == 2) {
            int your_q = wsm->getMyQ(); //get BOB step_1 from message
            int p = wsm->getP();        //get P from message
            key = DH_computeKey(your_q, myK, p); //compute the secrete KEY (step_2)
            findHost()->getDisplayString().setTagArg("i", 1, "green"); //change car color
            std::cout << "#" << myId << " | Computed key: " << key << endl; //print information
        }
    }
}


void TraCIDemo11p::handleSelfMsg(cMessage* msg) {
    //if message is a MSG_DH
    if (MSG_DH* wsm = dynamic_cast<MSG_DH*>(msg)) {
        sendDelayedDown(wsm, uniform(0.01, 0.1)); //send scheduled message
        printMSG(myId, wsm->getStep(), wsm->getG(), wsm->getP(), wsm->getMyQ(), 0); //print information
        findHost()->getDisplayString().setTagArg("i", 1, "yellow"); //change car color
    }

    else {
        DemoBaseApplLayer::handleSelfMsg(msg);
    }
}


void TraCIDemo11p::handlePositionUpdate(cObject* obj) {
    DemoBaseApplLayer::handlePositionUpdate(obj);
}

