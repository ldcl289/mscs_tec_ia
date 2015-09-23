import java.util.*;

int multiplier = 20;
int size = 25;
int xStart = 4;
int yStart = 4;
Problem problem = new Problem(size);
Node startPoint = problem.graph.matrix[xStart][yStart];


int y = 100;


void setup() {
  size(500, 500);
  stroke(multiplier);
  frameRate(15);
}

void draw() { 
  background(0);   // Clear the screen with a black background
  y = y - multiplier; 
  if (y < 0) { 
    y = height; 
  } 
  line(0, y, width, y);  
}