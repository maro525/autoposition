#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

using namespace std;

class Communication
{
public:
    Communication(){};
    ~Communication(){};

    void setupsend(string host, int port, string adress);
    void setuprecv(int port, string address);

    string getMessage() { return message; };

    void parse(int port, string text);

    void recv();
    void send(int command, int num);

    ofxOscSender sender;
    ofxOscReceiver receiver;
    string sendaddress, recvaddress;

    string message;
};