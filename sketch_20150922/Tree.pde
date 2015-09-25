public class Tree
{
  public Vector<Tree> childs = new Vector<Tree>();
  public Node data;
  public Tree(Node data)
  {
    this.data = data;
  }
  public String toString()
  {
    return data.toString();
  }
}