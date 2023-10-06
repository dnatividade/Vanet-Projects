//@dnat

import veins.base.utils.Coord;
import veins.modules.messages.BaseFrame1609_4;
import veins.base.utils.SimpleAddress;

namespace veins;

packet MsgFind extends BaseFrame1609_4 {
    int type;
    LAddress::L2Type senderAddress = -1;
    int src;
    int dst;
    int ttl = 10;
}
