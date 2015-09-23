class Node
{
  public int x, y;
  private boolean valid;
  public String label;
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
}