#include "model.h"

void Model::setNodeFromJsonText(string text)
{
    if (text == "")
        return;
    bool parseSuccessful = json.parse(text);
    if (!parseSuccessful)
    {
        return;
    }
    else if (parseSuccessful)
    {
        setNode();
    }
}

void Model::setNode()
{
    const Json::Value &nodes = json["nodes"];
    if (nodes.size() == 0)
        return;

    for (Json::ArrayIndex i = 0; i < nodes.size(); ++i)
    {
        float x = json["nodes"][i]["x"].asFloat();
        float y = json["nodes"][i]["y"].asFloat();
        float w = json["nodes"][i]["w"].asFloat();
        float h = json["nodes"][i]["h"].asFloat();
        auto links = json["nodes"][i]["link"];
        vector<int> l;
        for (Json::ArrayIndex i = 0; i < links.size(); ++i)
        {
            l.push_back(links[i].asInt());
        }
        NodeElem n = {x, y, w, h, l};
        setNodeAtIndex(i, n);
    }
}

void Model::setNodeAtIndex(int index, NodeElem n)
{
    int length = nodes.size();
    bool bExist = (index < length);
    if (bExist)
        nodes.at(index) = n;
    else
        nodes.push_back(n);
}