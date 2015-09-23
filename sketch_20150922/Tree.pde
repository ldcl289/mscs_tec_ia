public class Tree
{
  public List<Tree> childs = new LinkedList<Tree>();
  public Node data;
  public Tree(Node data)
  {
    this.data = data;
  }
}