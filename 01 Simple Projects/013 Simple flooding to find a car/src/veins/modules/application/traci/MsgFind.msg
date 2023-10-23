//@dnat

import veins.base.utils.Coord;
import veins.modules.messages.BaseFrame1609_4;
import veins.base.utils.SimpleAddress;

namespace veins;

packet MsgFind extends BaseFrame1609_4 {
    int type; //type of MsgFind
    LAddress::L2Type senderAddress = -1; //destination address
    int src; //car ID of source message
    int dst; //car ID of destination message
    int ttl = 6; //max hops by msg
}
