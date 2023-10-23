//App: @dnat


#include <veins/modules/application/traci/CRC.h>


unsigned long CRC::hashCRCMsg(std::string carAddress, std::string dataWsm){
    //https://stackoverflow.com/a/25018742
    unsigned long  crc = crc32(0L, Z_NULL, 0);
    std::string allWsmFields = carAddress +  dataWsm;
    crc = crc32(crc, (const unsigned char*)allWsmFields.c_str(), strlen(allWsmFields.c_str()));

    return crc;
}

