//
// Created by lchavarr on 12/19/15.
//

#include <algorithm>
#include "TreeSearch.h"

TreeSearch::TreeSearch(ProblemRoute *problem, AStar *strategy) : problem_(problem), strategy_(strategy)
{
    root_ = new Tree(problem_->startPoint);
    current_ = root_;
    isEnd_ = false;
}

TreeSearch::~TreeSearch()
{
    delete root_;
}

Node* TreeSearch::nextNode()
{
    previous_ = current_;
    if(problem_->isNodeEndPoint(current_->data))
    {
        isEnd_ = true;
        return current_->data;
    }
    std::vector<Node*> adjacents = problem_->getAdjacentNodes(current_->data);
    for(int i = 0 ; i < adjacents.size() ; ++i)
        current_->childs.push_back(new Tree(adjacents[i], current_));
    current_ = strategy_->get(current_);
    if(nullptr != current_)
        return current_->data;
    isEnd_ = false;
    return nullptr;
}

bool TreeSearch::isEnd()
{
    return isEnd_;
}

std::vector<Node*> TreeSearch::getCurrentPath()
{
    std::vector<Node*> path;
    Tree* current = previous_;
    while(nullptr != current->parent)
    {
        path.push_back(current->data);
        current = current->parent;
    }
    return path;
}

std::vector<Node*> TreeSearch::getFinalPath()
{
    while(!isEnd())
        nextNode();
    std::vector<Node*> path = getCurrentPath();
    std::reverse(path.begin(), path.end());
    return path;
}

