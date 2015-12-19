//
// Created by lchavarr on 12/19/15.
//

#ifndef AGENT_TREE_H
#define AGENT_TREE_H


#include <vector>
#include "Node.h"

class Tree
{
public:
    Tree(Node* data);
    Tree(Node* data, Tree* parent);
    ~Tree();
    std::string to_string();
    int weight() const;

    std::vector<Tree*> childs;
    Node* data;
    Tree*parent;

private:
    int distance_;
};

class TreeComparator
{
    bool reverse_;
public:
    TreeComparator(bool reverse = false);
    bool operator()(Tree*& lhs, Tree*& rhs);
};


#endif //AGENT_TREE_H
