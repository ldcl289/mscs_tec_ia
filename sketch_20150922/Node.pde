class Node
{
  public int x, y;
  private boolean valid;
  public String label;
  public boolean visited;
  Node()
  {
    valid = false;
  }
  Node(String label)
  {
    valid = true;
    this.label = label;
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