//
// Created by lchavarr on 12/19/15.
//

#ifndef AGENT_NODE_H
#define AGENT_NODE_H


#include <string>

class Node
{
public:
    Node();
    Node(int x, int y);
    ~Node();
    bool isValid();
    std::string to_string();

    int x, y;
    std::string label;
private:
    bool valid_;
};


#endif //AGENT_NODE_H
