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


#pragma once

#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"
#include "veins/modules/application/traci/defines.h" //header with all necessary defines
#include <veins/modules/application/traci/CRC.h>

namespace veins {

/**
 * Small Cars Demo using 11p
 */
class VEINS_API Cars : public DemoBaseApplLayer {
public:
    void initialize(int stage) override;

protected:
    void onWSM(BaseFrame1609_4* wsm) override;
    void handleSelfMsg(cMessage* msg) override;

    bool msgVector(simtime_t idToCheck);

    int msgCreatedByMe = 0; //flag: message creator. Who is finding a car
    int cancelMsgReq = 0;   //flag: cancel sending find-request message
    int cancelMsgRep = 0;   //flag: cancel sending find-replay message
    int cancelSent = 0;     //flag: car found. Stop sending find-cancel message
    int coloredCar = 0;     //flag: colored car?

    std::vector<simtime_t> idVector;
};

} // namespace veins
