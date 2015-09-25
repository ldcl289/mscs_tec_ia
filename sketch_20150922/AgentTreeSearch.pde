class AgentTreeSearch
{
  AgentTreeSearch(Problem problem, Strategy strategy)
  {
    this.problem = problem;
    this.strategy = strategy;
    root = new Tree(problem.startPoint);
    current = root;
    isEnd = false;
  }
  public Node nextNode()
  {
    System.out.println("\nCurrent Node=["+current.data.toString()+"]");
    if(problem.isEndPoint(current.data))
    {
      isEnd = true;
      return current.data;
    }
    Vector<Node> adjacents = problem.graph.getAdjacentNodes(current.data);
    for(int i = 0 ; i < adjacents.size() ; i++)
      current.childs.add(new Tree(adjacents.elementAt(i)));
    current = strategy.get(current);
    if(null != current)
      return current.data;
    isEnd = false;
    return null;
  }
  public boolean isSearchEnd()
  {
    return isEnd;
  }
  private Problem problem;
  private Strategy strategy;
  private Tree root;
  private Tree current;
  private boolean isEnd;
}