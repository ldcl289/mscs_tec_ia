

class Bayes
{
  Map<String, Integer> variables;
  Map<Vector<String>, Float> table;
  Bayes()
  {
    variables = new HashMap<String, Integer>();
    table = new HashMap<Vector<String>, Float>();
  }
  //P(X=x|Y=y)
  public float getConditionalProbability(String causeVariable, String causeOcurrence, String effectVariable, String effectOcurrence)
  {
    float total = 0;
    Map<String, String> tmp = new HashMap<String, String>();
    tmp.put(causeVariable, causeOcurrence);
    tmp.put(effectVariable, effectOcurrence);
    total = getProbability(tmp);
    total /= getProbability(effectVariable, effectOcurrence);
    return total;
  }
  //P(X=x|Y=y,Z=z,...)
  public float getConditionalProbability(String causeVariable, String causeOcurrence, Map<String, String> effects)
  {
    float total = 0;
    float divisor = getProbability(effects);
    effects.put(causeVariable, causeOcurrence);
    total = getProbability(effects);
    total /= divisor;
    return total;
  }
  //P(X=x) = P(x)
  public float getProbability(String variable, String occurrence)
  {
    Map<Vector<String>, Float> current = filterTable(table, variable, occurrence);
    return sumTable(current);
  }
  //P(X=x,Y=y,...) = P(x,y,...)
  public float getProbability(Map<String, String> values)
  {
    Map<Vector<String>, Float> current = filterTable(values);
    return sumTable(current);
  }
  private float sumTable(Map<Vector<String>, Float> current)
  {
    float total = 0;
    for(Vector<String> entryKey : current.keySet())
    {
      total += current.get(entryKey);
    }
    return total;
  }
  private Map<Vector<String>, Float> filterTable(Map<String, String> values)
  {
    Map<Vector<String>, Float> current = table;
    for(String variable : values.keySet())
    {
      current = filterTable(current, variable, values.get(variable));
    }
    return current;
  }
  private Map<Vector<String>, Float> filterTable(Map<Vector<String>, Float> current, String variable, String occurrence)
  {
    Map<Vector<String>, Float> filtered = new HashMap<Vector<String>, Float>();
    for(Vector<String> keys : current.keySet())
    {
      int variableIndex = variables.get(variable);
      if(keys.elementAt(variableIndex) == occurrence)
      {
        filtered.put(keys, current.get(keys));
      }
    }
    return filtered;
  }
}