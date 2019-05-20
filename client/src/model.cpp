#include "model.h"

void Model::setNodeFromJsonText(string text)
{
    bool parseSuccessful = json.parse(text);
    std::cout << "parse : " << parseSuccessful << endl;
    if(!parseSuccessful)
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
        NodeElem n = {x, y, w, h};
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