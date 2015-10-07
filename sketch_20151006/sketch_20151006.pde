import java.util.*;

int spaceSize = 100;
int lineWidth = 5;
int windowSize;
int backgroundColor = 0;
int lineColor = 255;
int winner = 0;
boolean isCurrentPlayerTheUser;
boolean gameOver = false;
Board board;

public class Pair
{
  public int x;
  public int y;
  public int score;
  public Pair(int x, int y)
  {
    this.x = x;
    this.y = y;
    this.score = 0;
  }
  public Pair()
  {
    this.x = -1;
    this.y = -1;
    this.score = 0;
  }
}

void drawGato()
{
  background(backgroundColor);
  stroke(lineColor);
  strokeWeight(lineWidth);
  line(spaceSize, 0, spaceSize, windowSize);
  line(spaceSize * 2, 0, spaceSize * 2, windowSize);
  line(0, spaceSize, windowSize, spaceSize);
  line(0, spaceSize * 2, windowSize, spaceSize * 2);
}

int convertGlobalLocationToTicTacToeLocation(int global)
{
  if(global >= 0 && global < spaceSize)
    return 0;
  if(global >= spaceSize + lineWidth && global < spaceSize * 2 + lineWidth)
    return 1;
  if(global >= (spaceSize + lineWidth) * 2 && global < spaceSize * 3 + lineWidth * 2)
    return 2;
  return -1;
}

Pair getMouseCoord()
{
  if(mousePressed)
  {
    Pair pair = new Pair();
    pair.x = convertGlobalLocationToTicTacToeLocation(mouseX);
    pair.y = convertGlobalLocationToTicTacToeLocation(mouseY);
    if(pair.x >= 0 && pair.y >= 0)
      return pair;
  }
  return null;
}

boolean defStartUser()
{
  return  Math.random() < 0.5;
}

void setup()
{ //<>//
  isCurrentPlayerTheUser = defStartUser();
  System.out.println("Starting the " + ((isCurrentPlayerTheUser) ? "Player" : "Computer")); 
  size(310, 310); //<>//
  windowSize = spaceSize * 3 + lineWidth * 2;
  drawGato();
  noLoop();
  board = new Board(3); //<>//
}

void drawShape(int x, int y, int shape)
{
  if (shape == 1)
  {
    ellipse((x * (spaceSize + lineWidth) + (spaceSize/2)), (y * (spaceSize + lineWidth) + (spaceSize/2)), 25, 25);   
  }
  
  if(shape==0)
  {
    star((x * (spaceSize + lineWidth) + (spaceSize/2)), (y * (spaceSize + lineWidth) + (spaceSize/2)), 15, 30, 5); 
  }
}

void draw()
{
  if(!gameOver)
  {
    if(isCurrentPlayerTheUser)
    {
      Pair pair = getMouseCoord();
      if(null != pair)
      {
        System.out.println("x=["+ Integer.toString(pair.x) + "], y=[" + Integer.toString(pair.y) + "]");
        if(board.setPlay(true, pair.x, pair.y))
        {
          drawShape(pair.x, pair.y, 0);
          isCurrentPlayerTheUser = !isCurrentPlayerTheUser;
        }
      }
    }
    else
    {
      Minimax minimax = new Minimax(new Tree(board));
      Pair nextMove = minimax.run(false);
      if(nextMove.x < 0)
      {
      }
      if(board.setPlay(false, nextMove.x, nextMove.y))
      {
        drawShape(nextMove.x, nextMove.y, 1);
        isCurrentPlayerTheUser = !isCurrentPlayerTheUser;
      }
    }
    int winner = board.winner();
    if(winner != 0)
    {
      gameOver = true;
      System.out.println("The winner is the " + ((winner == 1) ? "user" : "machine")); 
    }
    else
    {
      Vector<Pair> empties = board.getEmptySpaces();
      if(empties.isEmpty())
      {
        gameOver = true;
        System.out.println("It's a draw"); 
      }
    }
  } //<>// //<>//
}

void mousePressed() {
  redraw();
}

void star(float x, float y, float radius1, float radius2, int npoints) {
  float angle = TWO_PI / npoints;
  float halfAngle = angle/2.0;
  beginShape();
  for (float a = 0; a < TWO_PI; a += angle) {
    float sx = x + cos(a) * radius2;
    float sy = y + sin(a) * radius2;
    vertex(sx, sy);
    sx = x + cos(a+halfAngle) * radius1;
    sy = y + sin(a+halfAngle) * radius1;
    vertex(sx, sy);
  }
    endShape(CLOSE);
}