  
 int check_duplicates(String str)
{
  int i;
  int j;

  i = 0;
  while (i < str.length)
  {
    j = i + 1;
    while (j < str.length)
    {
      if (str.codeUnitAt(i) == str.codeUnitAt(j))
        return (-1);
      j++;
    }
    i++;
  }
  return (0);
} 


void  main()
{
  String name = "Ayoub";
  print("the Length Is : ${name.length.isOdd}");


}