#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "model.h"

class View
{
public:
    View(){};
    ~View()
    {
        delete gui;
    };

    void setupGui();

    void setModel(Model *ref) { m = ref; };

    int getNodeNum()
    {
        int num = int(nodenum);
        return num;
    };

    void draw();
    void drawNode(NodeElem *n);
    void drawLink(NodeElem *n);
    void drawData();

    void commandFired();

    ofEvent<int> commandEvent;

private:
    Model *m;
    float nodenum = 50.0;
    ofxUISuperCanvas *gui;
    void guiEvent(ofxUIEventArgs &e);
    void printGuiEvent(string eventName)
    {
        std::cout << "----- GUI EVENT : " << eventName << " -----" << endl;
    }

    void setUIToggleToFalse(string name)
    {
        ofxUIToggle *widget = (ofxUIToggle *)gui->getWidget(name);
        widget->setValue(false);
    }
};