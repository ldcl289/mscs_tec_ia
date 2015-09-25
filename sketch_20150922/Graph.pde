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
      {
        matrix[i][j] = new Node(Integer.toString(i) + "_" + Integer.toString(j));
        matrix[i][j].x = i;
        matrix[i][j].y = j;
      }
    }
  }
  public Vector<Node> getAdjacentNodes(Node node)
  {
    Vector vector = new Vector();
    if(node.y + 1 < size)
      vector.addElement(matrix[node.x][node.y+1]);
    if(node.y - 1 >= 0)
      vector.addElement(matrix[node.x][node.y-1]);
    if(node.x + 1 < size)
      vector.addElement(matrix[node.x+1][node.y]);
    if(node.x - 1 >= 0)
      vector.addElement(matrix[node.x-1][node.y]);
    return vector;
  }
  private int size;
  private Node[][] matrix;
}