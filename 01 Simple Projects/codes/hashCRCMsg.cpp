//@dnat
#include <zlib.h>


unsigned long TraCIDemo11p::hashCRCMsg(TraCIDemo11pMessage* wsm){
    unsigned long  crc = crc32(0L, Z_NULL, 0);
    //get message fields
    int serialWsm = wsm->getSerial();
    LAddress::L2Type srcWsm = wsm->getSenderAddress();
    std::string dataWsm = wsm->getDemoData();

    /*concatenate all message fields to compute hash
     * serial(int)  +  sender address(long)  +  demoData(srting)
     * if not using serial, put 0
     */
    std::string allWsmFields = std::to_string(serialWsm) + std::to_string(srcWsm) + dataWsm;
    //compute hash (for simplicity i am using CRC32 as hash function)
    //https://stackoverflow.com/a/25018742
    crc = crc32(crc, (const unsigned char*)allWsmFields.c_str(), strlen(allWsmFields.c_str()));

    return crc;
}

