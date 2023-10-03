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

#include "veins/modules/application/traci/Message_m.h"

// socket library
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
// //////////////////////////////////////////////////

// json files library: install nlohmann-json3-dev
// Debian Linux: sudo apt install nlohmann-json3-dev
#include <nlohmann/json.hpp>
#include <veins/modules/application/traci/NodeTelemetryCars.h>
using json = nlohmann::json;
// //////////////////////////////////////////////////

// IP and Port
#define IP_ADDR "192.168.20.36"
#define PORT    8080
// //////////////////////////////////////////////////

using namespace veins;

Define_Module(veins::NodeTelemetryCars);

void NodeTelemetryCars::sendTelemetry2NodeRED(int state) {
    int status, client_fd;
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port =   htons(PORT);

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "Socket creation error" << endl;
        abort();
    }
    // Convert IPv4 and IPv6 addresses from text to binary
    if (inet_pton(AF_INET, IP_ADDR, &serv_addr.sin_addr) <= 0) {
        std::cout << "Invalid address" << endl;
        abort();
    }
    if ((status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
        std::cout << "Connection Failed" << endl;
        abort();
    }

    //create json MSG
    auto telemetry = R"(
      {
        "Id": 0,
        "Speed": 0,
        "Acceleration": "0",
        "CO2": "0",
        "Fuel": "0"
      }
    )"_json;

    if (state != 0) {
        //set fields of the json to send via socket
        telemetry["Id"] =            myId;
        telemetry["Speed"] =         traciVehicle->getSpeed();
        telemetry["Acceleration"] =  traciVehicle->getAcceleration();
        telemetry["CO2"] =           traciVehicle->getCO2Emissions();
        telemetry["Fuel"] =          traciVehicle->getFuelConsumption();
    }

    ::send(client_fd, telemetry.dump().c_str(), strlen(telemetry.dump().c_str()), 0);
    std::cout << "Data sent: " << telemetry.dump().c_str() << " | SimTime: " << simTime() << endl;

    // closing the connected socket
    close(client_fd);
}

void NodeTelemetryCars::finish(void) {
    // choose a vehicle ID (myId)
    if (myId == 16) {
        sendTelemetry2NodeRED(0); //send a json with telemetry data = 0
    }
}

void NodeTelemetryCars::handlePositionUpdate(cObject* obj) {
    DemoBaseApplLayer::handlePositionUpdate(obj);

    // stopped for for at least 10s?
    if (mobility->getSpeed() < 1) {
        findHost()->getDisplayString().setTagArg("i", 1, "red");
    }

    else {
        lastDroveAt = simTime();

        // choose a vehicle ID (myId)
        if (myId == 16) {
            sendTelemetry2NodeRED(1); //send a json with telemetry data
        }
    }
}
