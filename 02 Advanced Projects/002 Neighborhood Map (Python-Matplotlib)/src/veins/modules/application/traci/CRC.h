//App: @dnat


#pragma once

#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"
#include "veins/modules/application/traci/defines.h" //header with all necessary defines
#include <zlib.h>

/**
 * CRC Demo
 */
class CRC {
public:
    unsigned long hashCRCMsg(int carAddress, std::string dataWsm);

};
