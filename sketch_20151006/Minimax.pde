public class Minimax
{
  public Tree root;
  public Minimax(Tree root)
  {
    this.root = root;
  }
  public Pair run(boolean player)
  {
    return genMinimax(root, player);
  }
  public Pair genMinimax(Tree current, boolean player)
  {
    int bestScore = (player) ? Integer.MIN_VALUE : Integer.MAX_VALUE;
    Pair bestMove = new Pair();
    Vector<Pair> empties = current.data.getEmptySpaces();
    int isWinner = current.data.winner();
    if(0 != isWinner)
    {
      bestScore = isWinner;
    }
    else if(empties.isEmpty())
    {
      bestScore = 0;
    }
    else
    {
      for(int i = 0 ; i < empties.size() ; i++)
      {
        Board childBoard = current.data.clone();
        childBoard.setPlay(player, empties.elementAt(i).x, empties.elementAt(i).y);
        Tree child = new Tree(childBoard, current);
        current.childs.add(child);
        Pair currentScore = genMinimax(child, !player);
        if(player)
        {
          if(currentScore.score > bestScore)
          {
            bestScore = currentScore.score;
            bestMove = empties.elementAt(i);
          }
        }
        else
        {
          if(currentScore.score < bestScore)
          {
            bestScore = currentScore.score;
            bestMove = empties.elementAt(i);
          }
        }
      }
    }
    bestMove.score = bestScore;
    return bestMove;
  }
}