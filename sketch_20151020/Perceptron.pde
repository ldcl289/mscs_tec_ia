class Perceptron
{
  float[] weights;
  float c;
  
  Perceptron(int n, float c_) {
    weights = new float[n];
    c = c_;
    // Start with random weights
    for (int i = 0; i < weights.length; i++) {
      weights[i] = random(0, 1);
    }
  }

  PVector feedforward(PVector[] forces)
  {
    // Sum is a PVector.
    PVector sum = new PVector();
    for (int i = 0; i < weights.length; i++)
    {
      forces[i].mult(weights[i]);
      sum.add(forces[i]);
    }
    return sum;
  }
  
  void train(PVector[] forces, PVector error)
  {
    for (int i = 0; i < weights.length; i++)
    {  
      weights[i] += c*error.x*forces[i].x;         
      weights[i] += c*error.y*forces[i].y;
      weights[i] = constrain(weights[i], 0, 1);
    }
  }
}