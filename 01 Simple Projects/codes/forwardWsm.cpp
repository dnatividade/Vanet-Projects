//This method changes the message fields to forward to another node
void TraCIDemo11p::forwardWsm(TraCIDemo11pMessage* wsm) {
    wsm->setRecipientAddress(myId+6); //set new destination
    wsm->setSerial(wsm->getSerial() + 1); //set a sequential number; start with 1
    wsm->setSenderAddress(myId); //set source address
    std::string data = wsm->getDemoData() + std::to_string(myId) + ";";
    wsm->setDemoData(data.c_str()); //set msg content
    sendDelayedDown(wsm->dup(), uniform(0.01, 0.2)); //send message with a random delay [between 0.01 and 0.2 seconds]
    //std::cout << "CAR " << myId << " | sent msg to CAR: " << wsm->getRecipientAddress() << " | SimTime: " << simTime() << endl; //print information
}

