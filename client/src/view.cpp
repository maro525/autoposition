#include "view.h"

void View::setupGui()
{
    gui = new ofxUISuperCanvas("GUI");
    gui->setPosition(0, 0);
    gui->addSpacer();
    gui->addLabel("COMMAND");
    gui->addLabelToggle("COMMAND 1", false);
    gui->addLabelToggle("COMMAND 2", false);
    gui->addLabelToggle("COMMAND 3", false);
    gui->autoSizeToFitWidgets();
    ofAddListener(gui->newGUIEvent, this, &View::guiEvent);
}

void View::draw()
{
    for (int i = 0; i < m->nodes.size(); i++)
    {
        drawNode(&m->nodes.at(i));
    }
}

void View::drawNode(NodeElem *n)
{
    ofSetColor(0);
    ofFill();
    ofDrawEllipse(n->x, n->y, n->width, n->height);
}

void View::guiEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
    printGuiEvent(name);
    int command;
    if (name == "COMMAND 1")
    {
        command = 0;
        ofNotifyEvent(commandEvent, command);
    }
    else if (name == "COMMAND 2")
    {
        command = 1;
        ofNotifyEvent(commandEvent, command);
    }
    else if (name == "COMMAND 3")
    {
        command = 2;
        ofNotifyEvent(commandEvent, command);
    }
    setUIToggleToFalse(name);
}