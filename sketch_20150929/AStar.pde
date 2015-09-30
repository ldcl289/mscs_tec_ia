

class AStar implements Strategy
{
  private PriorityQueue<Tree> queue;
  private Set<String> visited;
  AStar()
  {
    Comparator<Tree> comparator = new TreeComparator();
    queue = new PriorityQueue<Tree>(10, comparator);
    visited = new HashSet<String>();
  }
  Tree get(Tree current)
  {
    visited.add(current.toString());
    for(int i = 0 ; i < current.childs.size() ; i++)
    {
      Tree child = current.childs.get(i);
      if(!visited.contains(child.toString()))
        queue.offer(child);
    }
    System.out.println("queue=>");
    for(int i = 0; i < queue.toArray().length ; i++)
      System.out.print(((Tree) queue.toArray()[i]).data.toString() +"|");
    System.out.println("");
    System.out.println("visited=>");
    System.out.println(Arrays.toString(visited.toArray()));
    if(queue.isEmpty())
      return null;
    Tree next = queue.poll();
    if(visited.contains(next.toString()))
      return get(next);
    return next;
  }
}