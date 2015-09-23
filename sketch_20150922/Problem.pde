class Problem
{
  public Graph graph;
  public Vector<Node> endPoints;
  public Node startPoint;
  
  Problem(int size)
  {
    graph = new Graph(size);
    endPoints = new Vector<Node>();
  }
  public boolean isEndPoint(Node nodeToCheck)
  {
    for(int i = 0 ; i < endPoints.size() ; i++)
      if(endPoints.elementAt(i).x == nodeToCheck.x && endPoints.elementAt(i).y == nodeToCheck.y)
        return true;
    return false;
  }
}