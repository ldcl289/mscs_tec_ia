import java.util.*;

int multiplier = 20;
int size = 25;
int xStart = 2;
int yStart = 2;
int xEnd = 20;
int yEnd = 20;
Problem problem;
Node startPoint;
Node endPoint;
Strategy strategy;
AgentTreeSearch treeSearch;



Vector<Node> visited;
Node next;

void setup()
{
  xStart = new Random().nextInt(size);
  yStart = new Random().nextInt(size);
  xEnd = new Random().nextInt(size);
  yEnd = new Random().nextInt(size);
  
  problem = new Problem(size);
  startPoint = problem.graph.matrix[xStart][yStart];
  endPoint = problem.graph.matrix[xEnd][yEnd];
  problem.setStartPoint(startPoint);
  problem.addEndPoint(endPoint);
  strategy = new DFS();
  //strategy = new BFS();
  treeSearch = new AgentTreeSearch(problem, strategy);
  visited = new Vector<Node>();
  next = startPoint;
  
  size(500, 500);
  stroke(multiplier);
  frameRate(15);
  //noLoop();
  
  fill(100);
  rect(xEnd * multiplier, yEnd * multiplier, multiplier, multiplier);
  fill(255);
  ellipse(xStart * multiplier, yStart * multiplier, multiplier, multiplier);
}

void draw()
{ 
  background(0);
  if(treeSearch.isSearchEnd())
  {
    for(int i = 0 ; i < visited.size() ; i++)
    {
      fill(128, 128, 128);
      rect(visited.get(i).x * multiplier, visited.get(i).y * multiplier, multiplier, multiplier);
    }
    fill(255, 255, 255);
    rect(xEnd * multiplier, yEnd * multiplier, multiplier, multiplier);
    fill(128, 0, 0);
    ellipse(xEnd * multiplier + multiplier/2, yEnd * multiplier + multiplier/2, multiplier, multiplier);
  }
  else
  {
    visited.addElement(next); //<>//
    for(int i = 0 ; i < visited.size() ; i++)
    {
      fill(128, 128, 128);
      rect(visited.get(i).x * multiplier, visited.get(i).y * multiplier, multiplier, multiplier);
    }
    fill(255, 255, 255);
    rect(xEnd * multiplier, yEnd * multiplier, multiplier, multiplier);
    fill(128, 0, 0);
    ellipse(next.x * multiplier + multiplier/2, next.y * multiplier + multiplier/2, multiplier, multiplier);
    next = treeSearch.nextNode();
  }
}


void mousePressed() {
  redraw();
}