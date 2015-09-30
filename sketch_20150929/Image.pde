class Image
{
  private static final color validColor = #FFFFFF;
  public PImage image;
  public int width;
  public int spaceLenght;
  private int size;
  
  public Image(String path, int size)
  {
    this.size = size;
    image = loadImage(path);
    this.width = image.width;
    System.out.println("Width=["+Integer.toString(width) + "]");
    spaceLenght = image.width / size;
    System.out.println("spaceLenght=["+Integer.toString(spaceLenght) + "]");
  }
  public color get(int x, int y)
  {
    return image.get(x * spaceLenght + spaceLenght / 2, y * spaceLenght + spaceLenght / 2);
  }
  public boolean isValid(int x, int y)
  {
    return validColor == get(x, y);
  }
  public int[] genRandomValidPoint()
  {
    int x, y;
    do
    {
      x = new Random().nextInt(size);
      y = new Random().nextInt(size);
    }
    while(isValid(x, y));
    int[] v = new int[2];
    v[0] = x;
    v[1] = y;
    return v;
  }
  public void printText(Node node)
  {
      fill(0, 0, 0);
    text(Integer.toString(node.cost), node.x * spaceLenght + spaceLenght / 2, node.y * spaceLenght + spaceLenght / 2);
  }
}  