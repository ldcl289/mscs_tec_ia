//Bryant Alvarez
//David Alfaro
//LuisDiego Chavarria Ledezma

import java.util.*;

int size = 21;
int xStart = 2;
int yStart = 2;
int xEnd = 20;
int yEnd = 20;
Problem problem;
Node startPoint;
Node endPoint;
Strategy strategy;
AgentTreeSearch treeSearch;
Vector<Node> path;
Image img;



Vector<Node> visited;
Node next;

void setup()
{  //<>//
  size(840, 840); //<>//
  img = new Image("laberinto.jpg", size);
  stroke(img.spaceLenght);
  frameRate(25);
  //noLoop();
  
  xStart = 14;
  yStart = 0;
  xEnd = 8;
  yEnd = 18;
  
  fill(100);
  rect(xEnd * img.spaceLenght, yEnd * img.spaceLenght, img.spaceLenght, img.spaceLenght);
  fill(255);
  ellipse(xStart * img.spaceLenght, yStart * img.spaceLenght, img.spaceLenght, img.spaceLenght);
  
  problem = new Problem(size, img);
  startPoint = problem.graph.matrix[xStart][yStart];
  endPoint = problem.graph.matrix[xEnd][yEnd];
  problem.setStartPoint(startPoint);
  problem.addEndPoint(endPoint);
  //strategy = new DFS(); //<>//
  //strategy = new BFS();
  strategy = new AStar();
  treeSearch = new AgentTreeSearch(problem, strategy);
  visited = new Vector<Node>();
  next = startPoint;
}

void draw()
{ 
  background(0);
  image(img.image, 0, 0);
  if(treeSearch.isSearchEnd())
  {
    for(int i = 0 ; i < visited.size() ; i++)
    {
      fill(128, 128, 128);
      rect(visited.get(i).x * img.spaceLenght, visited.get(i).y * img.spaceLenght, img.spaceLenght, img.spaceLenght);
    }
    fill(255, 255, 255);
    rect(xEnd * img.spaceLenght, yEnd * img.spaceLenght, img.spaceLenght, img.spaceLenght);
    fill(128, 0, 0);
    ellipse(xEnd * img.spaceLenght + img.spaceLenght/2, yEnd * img.spaceLenght + img.spaceLenght/2, img.spaceLenght, img.spaceLenght);
    for(int i = 1 ; i < path.size() ; i++)
    {
      fill(0, 255, 0);
      rect(path.get(i).x * img.spaceLenght, path.get(i).y * img.spaceLenght, img.spaceLenght, img.spaceLenght);
    }
  } //<>//
  else
  {
    visited.addElement(next); //<>//
    for(int i = 0 ; i < visited.size() ; i++)
    {
      fill(128, 128, 128);
      rect(visited.get(i).x * img.spaceLenght, visited.get(i).y * img.spaceLenght, img.spaceLenght, img.spaceLenght);
    }
    fill(255, 255, 255);
    rect(xEnd * img.spaceLenght, yEnd * img.spaceLenght, img.spaceLenght, img.spaceLenght);
    fill(128, 0, 0);
    ellipse(next.x * img.spaceLenght + img.spaceLenght/2, next.y * img.spaceLenght + img.spaceLenght/2, img.spaceLenght, img.spaceLenght);
    next = treeSearch.nextNode();
    path = treeSearch.getCurrentPath();
    for(int i = 1 ; i < path.size() ; i++)
    {
      fill(0, 0, 255);
      rect(path.get(i).x * img.spaceLenght, path.get(i).y * img.spaceLenght, img.spaceLenght, img.spaceLenght);
    }
  }
  for(int i = 0 ; i < size ; i++)
  {
    for(int j = 0 ; j < size ; j++)
    {
      if(problem.graph.matrix[i][j].valid)
      {
        img.printText(problem.graph.matrix[i][j]);
      }
    }
  }
}


void mousePressed() {
  redraw();
}