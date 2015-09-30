public class Tree
{
  public Vector<Tree> childs = new Vector<Tree>();
  public Tree parent;
  public Node data;
  public int distance;
  public int cost;
  public Tree(Node data)
  {
    distance = 1;
    cost = data.cost;
    this.data = data;
    parent = null;
  }
  public Tree(Node data, Tree parent)
  {
    distance = parent.distance + 1;
    cost = parent.cost + data.cost;
    this.data = data;
    this.parent = parent;
  }
  public String toString()
  {
    return data.toString();
  }
  
  public int weight()
  {
    return distance + cost;
  }
}


import java.util.Comparator;

public class TreeComparator implements Comparator<Tree>
{
    @Override
    public int compare(Tree x, Tree y)
    {
        if (x.weight() < y.weight())
        {
            return 1;
        }
        if (x.weight() > y.weight())
        {
            return -1;
        }
        return 0;
    }
}