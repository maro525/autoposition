#pragma once

#include "ofMain.h"
#include "ofxJSON.h"

using namespace std;

struct NodeElem
{
    float x;
    float y;
    float width;
    float height;
};

class Model
{
public:
    Model(){};
    ~Model(){};

    void setNodeFromJsonText(string text);
    void setNode();
    void setNodeAtIndex(int index, NodeElem n);

    ofxJSONElement json;

    vector<NodeElem> nodes;
};