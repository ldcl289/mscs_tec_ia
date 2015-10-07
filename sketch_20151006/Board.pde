
public class Board
{
  private int board[][];
  private int size;
  public Board(int size)
  {
    this.size = size;
    board = new int[size][];
    for(int i = 0 ; i < size ; i++)
      board[i] = new int[size];
  }
  
  public boolean setPlay(boolean isUserPlayer, int x, int y)
  {
    if(x >= 0 && x < size && y >= 0 && y < size)
    {
      if(board[x][y] == 0)
      {
        board[x][y] = (isUserPlayer) ? 1 : -1;
        return true;
      }
    }
    return false;
  }
  public Board clone()
  {
    Board cloned = new Board(size);
    for(int i = 0 ; i < size ; i++)
      for(int j = 0 ; j < size ; j++)
        cloned.board[i][j] = this.board[i][j];
    return cloned;
  }
  
  public Vector<Pair> getEmptySpaces()
  {
    Vector<Pair> empties = new Vector<Pair>();
    for(int i = 0 ; i < size ; i++)
      for(int j = 0 ; j < size ; j++)
        if(0 == this.board[i][j])
          empties.add(new Pair(i, j));
    return empties;
  }
  
  public int winner()
  {
    for(int i = 0 ; i < size ; i++)
    {
      if(board[0][i] == board[1][i] && board[1][i] == board[2][i] && 0 != board[0][i])
        return board[0][i];
      if(board[i][0] == board[i][1] && board[i][1] == board[i][2] && 0 != board[i][0])
        return board[i][0];
    }
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && 0 != board[0][0])
      return board[0][0];
    if(board[2][0] == board[1][1] && board[1][1] == board[0][2] && 0 != board[1][1])
      return board[1][1];
    return 0;
  }
}