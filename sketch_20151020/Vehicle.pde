class Vehicle 
{  
  Perceptron brain; 
  PVector location;
  PVector velocity;
  PVector acceleration;
  float r;
  float maxforce;
  float maxspeed;
  

  
  Vehicle(int n, float x, float y) 
  {
    brain = new Perceptron(n, 0.01); 
    acceleration = new PVector(0,0);
    velocity = new PVector(0,0);
    location = new PVector(x,y);
    maxspeed = 4;
    maxforce = 0.1;
    r = 5.0;
  }

  
  void update() 
  {
    velocity.add(acceleration);
    velocity.limit(maxspeed);
    location.add(velocity);
    if(location.x > width || location.x < 0 || location.y > height || location.y < 0)
      location.mult(-1);
    acceleration.mult(0);
    color currentColor = get((int)location.x, (int)location.y);
    println(currentColor);
  }
  
  void applyForce(PVector force) 
  {
    acceleration.add(force);
  }
  
  void steer(Vector<PVector> targets) 
  {
    PVector[] forces = new PVector[targets.size()];
    for (int i = 0; i < forces.length; i++) 
    {
      forces[i] = seek(targets.get(i));
    }    
    PVector result = brain.feedforward(forces); 
    applyForce(result);
    PVector desired = new PVector(width/2, height/2); 
    PVector error = PVector.sub(desired, location); 
    brain.train(forces,error);
  }
  
  PVector seek(PVector target) 
  {
    //PVector desired = PVector.sub(target, location);
    PVector desired = PVector.sub(location, target);
    desired.normalize();
    desired.mult(maxspeed);
    PVector steer = PVector.sub(desired,velocity);
    steer.limit(maxforce);
    return steer;
  }
  
  void display()
  {
    float theta = velocity.heading2D() + PI/2;
    fill(175);
    stroke(0);
    strokeWeight(1);
    pushMatrix();
    translate(location.x,location.y);
    rotate(theta);
    beginShape();
    vertex(0, -r*2);
    vertex(-r, r*2);
    vertex(r, r*2);
    endShape(CLOSE);
    popMatrix();
  }
}