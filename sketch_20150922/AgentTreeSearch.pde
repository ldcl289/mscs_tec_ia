class AgentTreeSearch
{
  AgentTreeSearch(Problem problem, Strategy strategy)
  {
    this.problem = problem;
    this.strategy = strategy;
    root = new Tree(problem.startPoint);
  }
  boolean run()
  {
    return iterate(root);
  }
  boolean iterate(Tree current)
  {
    if(problem.isEndPoint(current.data))
      return true;
    Vector<Node> adjacents = problem.graph.getAdjacentNodes(current.data);
    for(int i = 0 ; i < adjacents.size() ; i++)
      current.childs.add(new Tree(adjacents.elementAt(i)));
    Tree next = strategy.get(current);
    if(null == next)
      return iterate(next);
    return false;
  }
  private Problem problem;
  private Strategy strategy;
  private Tree root;
}