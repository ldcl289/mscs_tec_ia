class Problem
{
  public Graph graph;
  private Vector<Node> endPoints;
  private Node startPoint;
  
  Problem(int size)
  {
    graph = new Graph(size);
    endPoints = new Vector<Node>();
    //startPoint = graph.matrix[2][2];
    //endPoints.add(graph.matrix[20][20]);
  }
  public boolean isEndPoint(Node nodeToCheck)
  {
    for(int i = 0 ; i < endPoints.size() ; i++)
      if(endPoints.elementAt(i).x == nodeToCheck.x && endPoints.elementAt(i).y == nodeToCheck.y)
        return true;
    return false;
  }
  public void addEndPoint(Node endPoint)
  {
    endPoints.add(endPoint);
  }
  public void setStartPoint(Node startPoint)
  {
    this.startPoint = startPoint;
  }
}