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
    previous = current;
    if(problem.isEndPoint(current.data))
    {
      isEnd = true;
      return current.data;
    }
    Vector<Node> adjacents = problem.graph.getAdjacentNodes(current.data);
    for(int i = 0 ; i < adjacents.size() ; i++)
      current.childs.add(new Tree(adjacents.elementAt(i), current));
    current = strategy.get(current);
    System.out.println("Current weight=[" + current.weight() + "]");
    if(null != current)
      return current.data;
    isEnd = false;
    return null;
  }
  public boolean isSearchEnd()
  {
    return isEnd;
  }
  public Vector<Node> getCurrentPath()
  {
    Vector<Node> path = new Vector<Node>();
    Tree curr = this.previous;
    while(curr != null)
    {
      path.addElement(curr.data);
      curr = curr.parent;
    }
    return path;
  }
  private Problem problem;
  private Strategy strategy;
  private Tree root;
  private Tree current;
  private Tree previous;
  private boolean isEnd;
}