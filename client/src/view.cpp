#include "view.h"

void View::setupGui()
{
    gui = new ofxUISuperCanvas("GUI");
    gui->setPosition(0, 800);
    gui->addSpacer();
    gui->addLabel("COMMAND");
    gui->addSlider("NUM", 1.0, 100.0, &nodenum);
    gui->addLabelToggle("INITIALIZE", false);
    gui->addLabelToggle("CALCULATE 1 STEP", false);

    gui->addLabelToggle("AUTO CALCULATION", false);
    gui->autoSizeToFitWidgets();
    ofAddListener(gui->newGUIEvent, this, &View::guiEvent);
}

void View::draw()
{
    for (int i = 0; i < m->nodes.size(); i++)
    {
        drawNode(&m->nodes.at(i));
        drawLink(&m->nodes.at(i));
    }
}

void View::drawNode(NodeElem *n)
{
    ofSetColor(218, 222, 229);
    ofFill();
    ofDrawEllipse(n->x, n->y, n->width, n->height);
}

void View::drawLink(NodeElem *n)
{
    int linknum = n->links.size();
    if (linknum == 0)
        return;
    for (int i = 0; i < linknum; i++)
    {
        int otherindex = n->links.at(i);
        NodeElem *othernode = &m->nodes.at(otherindex);
        float px = othernode->x;
        float py = othernode->y;
        ofDrawLine(n->x, n->y, px, py);
    }
}

void View::guiEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
    int kind = e.widget->getKind();
    if (kind == 13)
        printGuiEvent(name);
    int command;
    if (name == "INITIALIZE")
    {
        command = 0;
        ofNotifyEvent(commandEvent, command);
    }
    else if (name == "CALCULATE 1 STEP")
    {
        command = 1;
        ofNotifyEvent(commandEvent, command);
    }
    else if (name == "AUTO CALCULATION")
    {
        command = 2;
        ofNotifyEvent(commandEvent, command);
    }

    if (kind == 13)
        setUIToggleToFalse(name);
}

void View::drawData()
{
    ofPushStyle();
    ofSetColor(10);
    for (int i = 0; i < m->nodes.size(); i++)
    {
        float px = m->nodes.at(i).x;
        float py = m->nodes.at(i).y;
        vector<int> links = m->nodes.at(i).links;
        string text = ofToString(i) + " link :" + ofToString(links) + " x : " + ofToString(px) + " y :" + ofToString(py);
        float tx = 810;
        float ty = 15 + i * 12;
        ofDrawBitmapString(text, tx, ty);
    }
    ofPopStyle();
}