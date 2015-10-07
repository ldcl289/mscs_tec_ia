public class Tree
{
  public Vector<Tree> childs = new Vector<Tree>();
  public Tree parent;
  public Board data;
  public int distance;
  public int cost;
  public Tree(Board data)
  {
    distance = 1;
    this.data = data;
    parent = null;
  }
  public Tree(Board data, Tree parent)
  {
    distance = parent.distance + 1;
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