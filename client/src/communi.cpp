#include "communi.h"

void Communication::setupsend(string host, int port)
{
    sender.setup(host, port);
}

void Communication::setuprecv(int port, string address)
{
    receiver.setup(port);
    recvadress = address;
}

void Communication::parse(string text)
{
    bool parseSuccessful = json.parse(text);
}

void Communication::send(string address, int command)
{
    ofxOscMessage m;
    m.setAddress(address);
    m.addIntArg(command);
    sender.sendMessage(m);
}

void Communication::recv()
{
    while (reciver.hasWaitingMessages())
    {
        ofxOscMessage m;
        reciever.getNextMessage(&m);

        if (m.getAddress() == recvaddress)
        {
            t = m.getArgAsString(0);
        }
    }
}