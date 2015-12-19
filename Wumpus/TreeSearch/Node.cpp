//
// Created by lchavarr on 12/19/15.
//

#include "Node.h"

Node::Node()
{
    x = -1;
    y = -1;
    valid_ = false;
}

Node::Node(int x, int y)
{
    this->x = x;
    this->y = y;
    valid_ = true;
    label = std::to_string(x) + "_" + std::to_string(y);
}

bool Node::isValid()
{
    return valid_;
}

std::string Node::to_string()
{
    return label;
}

Node::~Node()
{

}
