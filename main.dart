import 'dart:io';
  
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
  int a;
  a = -5;
  if (a.isNegative)
    print("Yes");
  else
    print("No\n");

}