class Graph
{
  Graph(int size)
  {
    this.size = size;
    matrix = new Node[size][];
    for(int i = 0 ; i < size ; i++)
    {
      matrix[i] = new Node[size];
      for(int j = 0 ; j < size ; j++)
        matrix[i][j] = new Node();
    }
  }
  public Vector<Node> getAdjacentNodes(Node node)
  {
    Vector vector = new Vector();
    if(node.x + 1 < size)
    {
      if(node.y + 1 < size)
        vector.addElement(matrix[node.x+1][node.y+1]);
      if(node.y - 1 >= 0)
        vector.addElement(matrix[node.x+1][node.y-1]);
    }
    if(node.x - 1 >= 0)
    {
      if(node.y + 1 < size)
        vector.addElement(matrix[node.x-1][node.y+1]);
      if(node.y - 1 >= 0)
        vector.addElement(matrix[node.x-1][node.y-1]);
    }
    return vector;
  }
  private int size;
  private Node[][] matrix;
}