//@dnat
.h:
protected:
    //Message record
    struct msgRecord {
       int serial;
       LAddress::L2Type srcId;
       std::string data;
    };

    //Message Table
    std::map<unsigned long, msgRecord> msgRec;


.cc:
void TraCIDemo11p::storeMsg(TraCIDemo11pMessage* wsm, unsigned long crc) {
    //get message fields
    int serialWsm = wsm->getSerial();
    LAddress::L2Type srcWsm = wsm->getSenderAddress();
    std::string dataWsm = wsm->getDemoData();

    msgRecord wsm1 = { serialWsm, srcWsm, dataWsm };
    msgRec[crc] = wsm1;
}

