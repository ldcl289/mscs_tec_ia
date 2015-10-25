//Bryant Alvarez
//David Alfaro
//LuisDiego Chavarria Ledezma


import java.util.*;

Vector<PVector> blackPoints;
Vehicle vehicle;

void drawBlackPoints()
{
  background(255);
  fill(0);
  stroke(0);
  strokeWeight(2);
  for(int i = 0 ; i < blackPoints.size() ; i++)
    ellipse(blackPoints.elementAt(i).x, blackPoints.elementAt(i).y, 10, 10);
}

void setup()
{
  background(255);
  smooth();
  size(600, 600);
  blackPoints = new Vector<PVector>();
  for(int i = 0 ; i < 50 ; i++)
    blackPoints.add(new PVector(random(width), random(height)));
  /*for(int i = 0 ; i < width / 10 ; i++)
  {
    blackPoints.add(new PVector(i*10, 0));
    blackPoints.add(new PVector(i*10, width));
  }
  for(int i = 0 ; i < height / 10 ; i++)
  {
    blackPoints.add(new PVector(0, i*10));
    blackPoints.add(new PVector(height, i*10));
  }*/
  vehicle = new Vehicle(blackPoints.size(), random(width), random(height));
}


void draw()
{
  drawBlackPoints();
  vehicle.steer(blackPoints);
  vehicle.update();
  vehicle.display();
}