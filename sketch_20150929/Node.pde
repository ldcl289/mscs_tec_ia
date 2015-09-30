class Node
{
  public int x, y;
  private boolean valid;
  public String label;
  public boolean visited;
  public int cost;
  public boolean coin;
  Node()
  {
    valid = false;
  }
  Node(int x, int y) 
  {
    this.x = x;
    this.y = y;
    valid = true; 
    this.coin = Math.random() < 0.5;
    cost  = this.coin ? 1 : 0;
    this.label = Integer.toString(x) + "_" + Integer.toString(y) + "_" + Boolean.toString(coin);    
  }
  public boolean isValid()
  {
    return valid;
  }
  @Override public String toString()
  {
    return label;
  }
}