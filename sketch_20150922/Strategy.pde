interface Strategy
{
  Tree get(Tree current);
}

class DFS implements Strategy
{
  private Stack<Tree> stack;
  Tree get(Tree current)
  {
    for(int i = 0 ; i < current.childs.size() ; i++)
      stack.push(current.childs.get(i));
    if(stack.empty())
      return null;
    return stack.pop();
  }
}