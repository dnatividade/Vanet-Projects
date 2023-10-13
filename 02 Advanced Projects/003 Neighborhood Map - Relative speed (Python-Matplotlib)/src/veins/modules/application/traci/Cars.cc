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
 * Ajuste de origem para o Eixo Y:
 *
 * No OMNeT++, a origem esta localizada no canto superior esquerdo.
 * Na plotagem do gráfico usando o Matplotlib, a origem está no canto inferior esquerdo.
 *
 * Desta forma, faz-se um ajuste do Eixo -Y, multiplicando seus valores por -1 para que
 * o gráfico fique correto.
 */

#include <veins/modules/application/traci/Cars.h>
#include "veins/modules/application/traci/Message_m.h"

using namespace veins;

Define_Module(veins::Cars);

std::ofstream arquivo;

void Cars::initialize(int stage) {
    DemoBaseApplLayer::initialize(stage);
    if (stage == 1) {

        // Create a message
        Message* wsm = new Message();
        populateWSM(wsm, -1); //send to broadcast
        wsm->setSenderAddress(myId); //set source address
        scheduleAt(simTime() +1, wsm); //schedule the message

        if (myId == CAR1) {
            findHost()->getDisplayString().setTagArg("i", 1, "green");
            findHost()->getDisplayString().updateWith("r=200,white");
        }
    }
}


void Cars::onWSM(BaseFrame1609_4* frame) {
    if (Message* wsm = check_and_cast<Message*>(frame)) {

        // IF selected car...
        if (myId == CAR1) {
            msgCount++; //increment message counter

            // Get my coordinates
            double myX, myY = 0;
            myX = mobility->getPositionAt(simTime()).x;
            myY = mobility->getPositionAt(simTime()).y ;

            // IF this is the first received message, log my coordinates
            if (firstMsg == 1) {
                firstMsg = 0;
                std::stringstream ss;
                ss << myX << " -" << myY;
                CarsCoordStruct coord;
                coord.id = myId;
                coord.time = simTime();
                coord.coordinates = ss.str();
                coord.speed = mobility->getSpeed();
                coord.angleRad = mobility->getHeading().getRad();
                coordMap.push_back(coord);

                //std::cout << "ME(x,y) " << myX  << "," << myY << endl; //DEBUG ONLY
            }

            // Função para adicionar ou atualizar elementos //////////////////////////////
            auto adicionarOuAtualizar = [&](const CarsCoordStruct& novoElemento) {
                for (CarsCoordStruct& coord : coordMap) {
                    if (coord.id == novoElemento.id) {
                        // Elemento com o mesmo ID encontrado, atualize os valores
                        coord.time = novoElemento.time;
                        coord.coordinates = novoElemento.coordinates;
                        coord.speed = novoElemento.speed;
                        coord.angleRad = novoElemento.angleRad;
                        return;
                    }
                }
                // Se nenhum elemento com o mesmo ID for encontrado, adicione-o ao vetor
                coordMap.push_back(novoElemento);
            };// /////////////////////////////////////////////////////////////////////////


            // Get received coordinates
            std::string recvCoordinates = wsm->getCoordinates();
            CarsCoordStruct coord;
            coord.id = wsm->getSenderAddress();
            coord.time = simTime();
            coord.coordinates = recvCoordinates;
            coord.speed = wsm->getSpeed();
            coord.angleRad = wsm->getAngleRad();
            /*coordMap.push_back(coord); */
            adicionarOuAtualizar(coord);

            // DEBUG ONLY //////////////////////////////////////////////////////////////////////
            // Computes distance between vehicles
            std::stringstream ss(recvCoordinates);
            double x, y;
            (ss >> x);
            (ss >> y);

            double p, distance;
            myY = myY*(-1); //makes an origin adjustment for the Y axis
            p = pow((x-myX), 2) + pow((y-myY), 2);
            distance = sqrt(p);
            // Print information
            //std::cout << "ID: " << wsm->getSenderAddress() << " | Coord: " << recvCoordinates << " | Distance: " << distance << " | SimTime:" << simTime() << endl; //DEBUG ONLY
            // /////////////////////////////////////////////////////////////////////////////////
        }
    }
}


void Cars::handleSelfMsg(cMessage* msg) {
    if (Message* wsm = dynamic_cast<Message*>(msg)) {

        // Get current coordinates (x,y)
        double x,y = 0;
        std::string coordinates;
        x = mobility->getPositionAt(simTime()).x;
        y = mobility->getPositionAt(simTime()).y;

        // Convert coordinates to double and makes an origin adjustment for the Y axis
        std::stringstream ss;
        ss << x << " -" << y;

        wsm->setCoordinates(ss.str().c_str()); //set coordinates
        wsm->setSpeed(mobility->getSpeed());
        wsm->setAngleRad(mobility->getHeading().getRad());

        sendDelayedDown(wsm, uniform(0.01, 0.2)); //send message
        scheduleAt(simTime() +1, wsm->dup());
    }

    else {
        DemoBaseApplLayer::handleSelfMsg(msg);
    }
}

void Cars::handlePositionUpdate(cObject* obj) {
    DemoBaseApplLayer::handlePositionUpdate(obj);

    if (myId == CAR1) {
        // Open log file
        arquivo.open("coordinates.txt");

        // Leia e imprima todos os elementos do vetor
        for (const CarsCoordStruct& coord : coordMap) {
            arquivo << coord.coordinates << " " << coord.speed << " " << coord.angleRad << " " << coord.id << std::endl;
            //std::cout << "ID: " << coord.id << ", Time: " << coord.time << ", Coordinates: " << coord.coordinates << std::endl; //DEBUG ONLY
        }
        // Close log file
        arquivo.close();
        coordMap.clear();
        firstMsg = 1;
    }
}

void Cars::finish() {

    if (myId == CAR1) {

        // Print statistics
        //std::cout << endl << "STATISTICS:" << endl;
        //std::cout << "CAR: " << myId << "| Messages received: " << msgCount << endl << endl;

        // Show Graphic -- [ DISABLED ]
        //std::stringstream commandLineSS;
        //commandLineSS << "python3 plot.py";
        //system(commandLineSS.str().c_str());

        // Open log file
        arquivo.open("coordinates.txt");
        arquivo.clear();
        arquivo.close();
    }
}
