//@dnat
//This method sends a ACK from 'src' to 'dst'
void TraCIDemo11p::sendAck(int src, int dst) {
    TraCIDemo11pMessage* ack = new TraCIDemo11pMessage();
    populateWSM(ack, dst); //send back message to car - link layer ID get from wsm message ********
    ack->setSenderAddress(myId); //set source address
    ack->setDemoData("ack"); //set data = "ack"
    sendDelayedDown(ack, uniform(0.01, 0.2)); //send message with a random delay [between 0.01 and 0.2 seconds]
    //std::cout << "CAR " << myId << "| ack sent to RSU " << " | SimTime: " << simTime() << endl; //print information
}
