//
// Created by lchavarr on 12/19/15.
//

#include "Tree.h"

Tree::Tree(Node *data) : distance_(1), data(data), parent(nullptr)
{
}

Tree::Tree(Node *data, Tree *parent) : distance_(1), data(data), parent(parent)
{

}

Tree::~Tree()
{
    for(int i = 0 ; i < childs.size() ; ++i)
        delete childs[i];
    childs.clear();
}

std::string Tree::to_string()
{
    return data->to_string();
}

int Tree::weight() const
{
    return distance_;
}

TreeComparator::TreeComparator(bool reverse) : reverse_(reverse)
{

}

bool TreeComparator::operator()(Tree *&lhs, Tree *&rhs)
{
    if(reverse_)
        return lhs->weight() > rhs->weight();
    return lhs->weight() < rhs->weight();
}
