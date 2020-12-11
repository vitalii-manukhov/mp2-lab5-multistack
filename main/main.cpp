#include <iostream>
#include "stack.h"
#include "multistack.h"

int main()
{
  TStack<int> a(3);
  TStack<char> b(3);
  a.Put(10);
  a.Put(10);
  a.Put(10);

  TMultiStack<int> c(9, 3);
  c.Put(11, 0);
  c.Put(12, 1);
  c.Put(13, 1);
  c.Put(14, 1);

  c.Put(15, 1);

  std::cout << c << "\n";

  a.Resize(5);
  a.Put(10);
  a.Put(10);
  
  std::cout << a << "\n";

  std::cout << a.GetSize() << "\n";

  //char temp = 'a';
  //for (int i = 0; i < b.GetSize(); i++)
  //{
  //  b.Put(temp);
  //  temp++;
  //}


  //std::cout << a << "\n";
  //std::cout << b << "\n";

  return 0;
}
