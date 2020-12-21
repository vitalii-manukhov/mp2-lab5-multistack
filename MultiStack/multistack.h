#ifndef _MULTISTACK_
#define _MULTISTACK_

#include <iostream>
#include "stack.h"
#include <math.h>

using namespace std;

template <class T>
class TMultiStack
{
protected:
  int size; // размер данных
  T* data; // указатель на массив элементов
  int stackCount; // количество стеков
  TStack<T>* stackSet; // набор стеков
  T** oldData; // индексы начал

  void StackRelocation(int index); // перепаковка данных

public:
  TMultiStack(int _size = 1, int _stackCount = 1); // конструктор по умолчанию
  TMultiStack(const TMultiStack<T>& _v); // конструктор копирования
  ~TMultiStack();

  TMultiStack<T>& operator =(const TMultiStack<T>& _v); // оператор сравнения

  void Put(T d, int index); // запись элемента в стек
  T Get(int index); // извлечь последний записанный элемент стека

  template <class T1>
  friend ostream& operator<< (ostream& ostr, const TMultiStack<T1> &A);
  template <class T1>
  friend istream& operator >> (istream& istr, TMultiStack<T1> &A);

  bool IsEmpty(int index) const; // контроль пустоты стека
  bool IsFull(int index) const; // контроль полноты стека
  int GetSize(); // вернуть размер стека
  void Resize(int _size = 1, int _stackCount = 1); // изменить размер
};

template <class T1>
ostream& operator<< (ostream& ostr, const TMultiStack<T1> &A) {
  for (int i = 0; i < A.stackCount; i++) {
    ostr << A.stackSet[i] << endl;
  }
  return ostr;
}

template <class T1>
istream& operator >> (istream& istr, TMultiStack<T1> &A) {
  int stCount;
  istr >> stCount;
  int _size = 0;
  istr >> _size;
  A.Resize(_size, stCount);
  for (int i = 0; i < stCount; i++) 
  {
    istr >> A.stackSet[i];
  }
  return istr;
}

template<class T>
void TMultiStack<T>::StackRelocation(int index)
{
  int freeSize = 0;
  for (int i = 0; i < stackCount; i++)
    freeSize += stackSet[i].GetSize() - stackSet[i].GetCount();

  if (freeSize == 0)
    throw - 2;

  int count = int(floor(double(freeSize) / stackCount));
  int* sizeSet = new int[this->stackCount];

  for (int i = 0; i < (stackCount - 1); i++)
    sizeSet[i] = stackSet[i].GetCount() + count;
  sizeSet[this->stackCount - 1] = stackSet[stackCount - 1].GetCount() + (freeSize - (count * (this->stackCount - 1)));

  T** newData = new T * [this->stackCount]; // новые начала

  int k = 0; // индекс стека - номер того элемента, с которого начинается конкретный стек
  for (int i = 0; i < stackCount; i++)
  {
    newData[i] = &(data[k]);
    k = k + sizeSet[i];
  }

  for (int i = 0; i < stackCount; i++)
  {// три различных поведения при разных обстоятельствах:
    if (newData[i] == oldData[i]) // начала совпадают
      stackSet[i].SetData(newData[i], sizeSet[i], stackSet[i].GetCount());
    else if (newData[i] < oldData[i]) // начала стека не совпадают - после перепаковки начало меньше
    {
      for (int j = 0; j < stackSet[i].GetCount(); j++)
        newData[i][j] = oldData[i][j];
      stackSet[i].SetData(newData[i], sizeSet[i], stackSet[i].GetCount());
    }
    else if (newData[i] > oldData[i]) // начала стека не совпадают - после перепаковки начало больше
    {
      int k = i;
      for (; k < stackCount; k++)
      {
        if (newData[k] > oldData[k])
          continue;
        else
          break;
      }
      k--;
      for (int s = k; s <= i; s--)
      {
        for (int j = stackSet[s].GetCount() - 1; j >= 0; j--)
          newData[i][j] = oldData[i][j];
        stackSet[i].SetData(newData[s], sizeSet[s], stackSet[s].GetCount());
      }
    }
  }

  T** buf = oldData;
  oldData = newData;
  delete[] buf;
  delete[] sizeSet;

}

template<class T>
TMultiStack<T>::TMultiStack(int _size, int _stackCount)
{
  if ((_size > 0) && (_stackCount > 0))
  {
    this->size = _size;
    this->stackCount = _stackCount;

    data = new T[size];
    for (int i = 0; i < size; i++)
      data[i] = 0;

    int count = int(floor(double(size)/stackCount));
    int* sizeSet = new int[this->stackCount]; // массив с размерами стеков
    
    for (int i = 0; i < (stackCount - 1); i++)
      sizeSet[i] = count;

    sizeSet[stackCount - 1] = size - (count * (stackCount - 1)); // размер последнего стека (остаток)
    oldData = new T * [stackCount];
    this->stackSet = new TStack<T>[stackCount];
    int k = 0; // индекс стека - номер того элемента, с которого начинается конкретный стек
    
    for (int i = 0; i < stackCount; i++)
    {
      this->stackSet[i].SetData(&(data[k]), sizeSet[i], 0);
      this->oldData[i] = &(data[k]);
      k = k + sizeSet[i];
    }
  }
  else
    throw "negative size";
}

template <class T>
TMultiStack<T>::TMultiStack(const TMultiStack<T>& _v)
{
  size = _v.size;
  stackCount = _v.stackCount;
  data = new T[size];
  for (int i = 0; i < size; i++)
    data[i] = _v.data[i];
  stackSet = new TStack<T>[stackCount];
  for (int i = 0; i < stackCount; i++)
    stackSet[i] = _v.stackSet[i];
}

template <class T>
TMultiStack<T>::~TMultiStack()
{
  size = 0;
  stackCount = 0;
    if (data != nullptr && stackSet != nullptr)
    {
      delete[] data;
      delete[] stackSet;
      data = nullptr;
    }
    else
      throw "error";
}

template <class T>
TMultiStack<T>& TMultiStack<T>::operator =(const TMultiStack<T>& _v)
{
  if (this == &_v)
    return *this;

  this->size = _v.size;

  if (this->data != nullptr)
    delete[] data;
  if (stackSet != nullptr)
    delete[] stackSet;

  data = new T[size];
  for (int i = 0; i < size; i++)
    data[i] = _v.data[i];
  stackSet = new TStack<T>[stackCount];
  for (int i = 0; i < stackCount; i++)
    stackSet[i] = _v.stackSet[i];

  return *this;
}

template<class T>
void TMultiStack<T>::Put(T d, int index)
{
  if ((index < 0) || (index >= stackCount))
    throw "stack overflow";
  if (stackSet[index].IsFull())
    StackRelocation(index);
  stackSet[index].Put(d);
}

template<class T>
T TMultiStack<T>::Get(int index)
{
  if ((index < 0) || (index > stackCount))
    throw "stack overflow";
  if (stackSet[index].IsEmpty())
    throw - 2;
  T d = stackSet[index].Get();
  return d;
}

template<class T>
bool TMultiStack<T>::IsEmpty(int index) const
{
  if (index < 0 || index > stackCount)
    throw - 1;

  return stackSet[index].IsEmpty();
}

template<class T>
bool TMultiStack<T>::IsFull(int index) const
{
  if (index < 0 || index > stackCount)
    throw - 1;

  return stackSet[index].IsFull();
}

template <class T>
int TMultiStack<T>::GetSize()
{
  return size;
}

template<class T>
void TMultiStack<T>::Resize(int _size, int _stackCount)
{
  stackSet[_stackCount].Resize(_size);
}

#endif // ! _MULTISTACK_