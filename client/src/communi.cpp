#include "communi.h"

void Communication::setupsend(string host, int port, string address)
{
    sender.setup(host, port);
    sendaddress = address;
}

void Communication::setuprecv(int port, string address)
{
    receiver.setup(port);
    recvaddress = address;
}

void Communication::send(int command, int num)
{
    ofxOscMessage m;
    m.setAddress(sendaddress);
    m.addIntArg(command);
    m.addIntArg(num);
    sender.sendMessage(m);
}

void Communication::recv()
{
    while (receiver.hasWaitingMessages())
    {
        ofxOscMessage m;
        receiver.getNextMessage(&m);

        if (m.getAddress() == recvaddress)
        {
            message = m.getArgAsString(0);
        }
    }
}