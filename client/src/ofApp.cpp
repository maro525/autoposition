#include "ofApp.h"

#define HOST "127.0.0.1"
#define SEND_PORT 5665
#define RECV_PORT 5775
#define SEND_ADDRESS "/command"
#define RECV_ADDRESS "/positions"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(218, 222, 229);

    com.setupsend(HOST, SEND_PORT, SEND_ADDRESS);
    com.setuprecv(RECV_PORT, RECV_ADDRESS);

    view.setupGui();
    view.setModel(&model);
    ofAddListener(view.commandEvent, this, &ofApp::sendCommand);
}

//--------------------------------------------------------------
void ofApp::update()
{
    com.recv();
    model.setNodeFromJsonText(com.getMessage());
}

//--------------------------------------------------------------
void ofApp::draw()
{
    view.draw();
    drawData();
}

void ofApp::sendCommand(int &command)
{
    int nodesize = view.getNodeNum();
    if (command == 0)
        model.clear();
    com.send(command, nodesize);
}

void ofApp::drawData()
{
    ofPushStyle();
    ofSetColor(5, 21, 45);
    ofDrawRectangle(800, 0, 400, 1200);
    ofPopStyle();
    view.drawData();

    ofPushStyle();
    ofSetColor(10);
    ofDrawRectangle(0, 800, 800, 400);
    ofPopStyle();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}