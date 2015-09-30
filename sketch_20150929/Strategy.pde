interface Strategy
{
  Tree get(Tree current);
}

class DFS implements Strategy
{
  private Stack<Tree> stack;
  private Set<String> visited;
  DFS()
  {
    stack = new Stack<Tree>();
    visited = new HashSet<String>();
  }
  Tree get(Tree current)
  {
    visited.add(current.toString());
    for(int i = 0 ; i < current.childs.size() ; i++)
    {
      Tree child = current.childs.get(i);
      if(!visited.contains(child.toString()))
        stack.push(child);
    }
    System.out.println("Stack=>");
    for(int i = 0; i < stack.toArray().length ; i++)
      System.out.print(((Tree) stack.toArray()[i]).data.toString() +"|");
    System.out.println("");
    System.out.println("visited=>");
    System.out.println(Arrays.toString(visited.toArray()));
    if(stack.empty())
      return null;
    Tree next = stack.pop();
    if(visited.contains(next.toString()))
      return get(next);
    return next;
  }
}

class BFS implements Strategy
{
  private Queue<Tree> queue;
  private Set<String> visited;
  BFS()
  {
    queue = new LinkedList<Tree>();
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