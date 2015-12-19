//
// Created by lchavarr on 12/19/15.
//

#include "AStar.h"

AStar::AStar()
{

}

Tree *AStar::get(Tree *current)
{
    visited_.insert(current->to_string());
    for(int i = 0 ; i < current->childs.size() ; ++i)
    {
        Tree* child = current->childs[i];
        if(visited_.cend() == visited_.find(child->to_string()))
            queue_.push(child);
    }
    if(queue_.empty())
        return nullptr;
    Tree* next = queue_.top();
    queue_.pop();
    if(visited_.cend() != visited_.find(next->to_string()))
        return get(next);
    return next;
}

AStar::~AStar()
{

}
