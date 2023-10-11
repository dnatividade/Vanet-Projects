/*
 * @brief
 * Include file to use in "014 Project"
 * This file contain all necessary defines to use in Cars,RSU and CA
 */
//@dnat

#define RSU1 11 //not used in this project
#define CA1  16 //not used in this project
#define CAR1 478//190//400 //source car
#define CAR2 28  //destination car
#define TIME 235 //time to start the search

// Type of MsgFind
#define FIND_REQUEST 0
#define FIND_REPLAY  1
#define FIND_CANCEL  2

#define MAX_TTL      10   //message MAX TTL
#define DELAY_1      0.01 //sendDelayedDown first interval
#define DELAY_2      0.2  //sendDelayedDown second interval
#define DELAY_FW     0.5  //delay to forward request and reply message

#define PAYLOAD      "I have a important message to you\n"

