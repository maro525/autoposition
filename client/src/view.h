#pragma once

#include "ofxUI.h"
#include "model.h"

class View
{
public:
    View(){};
    ~View(){
        delete gui;
    };

    void setupGui();

    void setModel(Model *ref) { m = ref; };

    void draw();
    void drawNode(NodeElem *n);

    void commandFired();

    ofEvent<int> commandEvent;
private:
    Model *m;
    ofxUISuperCanvas *gui;
    void guiEvent(ofxUIEventArgs &e);
    void printGuiEvent(string eventName)
    {
        std::cout << "----- GUI EVENT : " << eventName << " -----" << endl;
    }
    
    void setUIToggleToFalse(string name)
    {
        ofxUIToggle * widget = (ofxUIToggle *) gui->getWidget(name);
        widget->setValue(false);
    }
};