#include "ofApp.h"

#define HOST "127.0.0.1"
#define SEND_PORT 5665
#define RECV_PORT 5775
#define SEND_ADDRESS "/command"
#define RECV_ADDRESS "/positions"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(255);

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
    int fieldsize = 800;
    int nodesize = 50;
    com.send(command, nodesize);
}

void ofApp::drawData()
{
    ofPushStyle();
    ofSetColor(18);
    ofDrawRectangle(800, 0, 400, 800);
    ofPopStyle();
    view.drawData();
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