//@dnat

import veins.base.utils.Coord;
import veins.modules.messages.BaseFrame1609_4;
import veins.base.utils.SimpleAddress;

cplusplus {{
#include "veins/modules/application/traci/defines.h"
}}

namespace veins;

packet MsgFind extends BaseFrame1609_4 {
    LAddress::L2Type senderAddress = -1; //source address
    int type; //type of MsgFind
    string hops; //hops delimited by ';'
    int src;     //car ID of source message
    int dst;     //car ID of destination message
    simtime_t id;    
    int ttl = MAX_TTL; //max hops by msg
}
