class Graph
{
  Graph(int size, Image image)
  {
    this.image = image;
    this.size = size;
    matrix = new Node[size][];
    for(int i = 0 ; i < size ; i++) //<>// //<>//
    {
      matrix[i] = new Node[size];
      for(int j = 0 ; j < size ; j++)
      {
        if(image.isValid(i, j))
        {
          matrix[i][j] = new Node(i, j);
        }
        else
        {
          matrix[i][j] = new Node();
        }
      }
    }
  }
  public Vector<Node> getAdjacentNodes(Node node)
  {
    Vector vector = new Vector();
    if(node.y + 1 < size && matrix[node.x][node.y+1].valid)
      vector.addElement(matrix[node.x][node.y+1]);
    if(node.y - 1 >= 0 && matrix[node.x][node.y-1].valid)
      vector.addElement(matrix[node.x][node.y-1]);
    if(node.x + 1 < size && matrix[node.x+1][node.y].valid)
      vector.addElement(matrix[node.x+1][node.y]);
    if(node.x - 1 >= 0 && matrix[node.x-1][node.y].valid)
      vector.addElement(matrix[node.x-1][node.y]);
    return vector;
  }
  private int size;
  private Node[][] matrix;
  private Image image;
}