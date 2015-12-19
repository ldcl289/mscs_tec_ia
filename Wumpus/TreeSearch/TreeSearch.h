//
// Created by lchavarr on 12/19/15.
//

#ifndef AGENT_TREESEARCH_H
#define AGENT_TREESEARCH_H


#include "ProblemRoute.h"
#include "AStar.h"

class TreeSearch
{
public:
    TreeSearch(ProblemRoute* problem, AStar* strategy);
    ~TreeSearch();
    Node* nextNode();
    bool isEnd();
    std::vector<Node*> getCurrentPath();
    std::vector<Node*> getFinalPath();
private:
    ProblemRoute* problem_;
    AStar* strategy_;
    Tree* root_;
    Tree* current_;
    Tree* previous_;
    bool isEnd_;
};


#endif //AGENT_TREESEARCH_H
