#pragma once

#include "ofxJSON.h"
#include "oscOsc.h"

using namespace std;

class Communication
{
    Communication(){};
    ~Communication(){};

    void setupsend(string host, int port, string adress);
    void setuprecv(string address);

    void parse(int port, string text);

    void recv();
    void send();

    ofxJSONElement json;

    ofxOscSender sender;
    ofxOscReceiver receiver;
    string recvaddress;
};