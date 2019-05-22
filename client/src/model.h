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
    vector<int> links;
};

class Model
{
public:
    Model(){};
    ~Model(){};

    void clear(){ nodes.clear(); };

    void setNodeFromJsonText(string text);
    void setNode();
    void setNodeAtIndex(int index, NodeElem n);

    ofxJSONElement json;

    vector<NodeElem> nodes;
};