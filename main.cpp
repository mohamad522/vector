#include <iostream>
#include <memory>

typedef int type;

using namespace std;

// header file
class MyVector
{
public:
  MyVector(int = 1);
  MyVector(type *, int);
  MyVector(const MyVector &);
  ~MyVector();
  MyVector &operator=(MyVector);
  const type operator[](int) const;
  type &operator[](int);
  MyVector &operator+=(const MyVector &);

  void push_back(type);
  type pop_back();
  int getCapacity() const;
  int getSize() const;

private:
  int size;               // nb of elements
  int capacity;           // nb of allocated bytes
  unique_ptr<type[]> ptr; // pointer to the array base
  friend ostream &operator<<(ostream &, const MyVector &);
  friend void swap(MyVector &, MyVector &);
};

void swap(MyVector &v1, MyVector &v2);

const MyVector operator+(MyVector v1, const MyVector &v2);

// implementation

MyVector::MyVector(int c)
    : capacity(c), size(0), ptr(make_unique<type[]>(capacity))
{
  for (int i = 0; i < c; ++i)
  {
    ptr[i] = 0;
  }
}
MyVector::MyVector(type *p, int n)
    : capacity(n), size(n), ptr(make_unique<type[]>(capacity))
{

  //    for (int i = 0; i < size; ++i){
  //     ptr[i] = p[i];
  //    }
  memcpy(ptr.get(), p, size * sizeof(type));
}

MyVector::~MyVector()
{
  cout << "Bye" << endl;
}

MyVector &MyVector::operator=(MyVector v)
{
  swap(*this, v);
  return *this;
}

MyVector::MyVector(const MyVector &v)
    : capacity(v.capacity), size(v.size), ptr(make_unique<type[]>(capacity))
{
  memcpy(ptr.get(), v.ptr.get(), size * sizeof(type));
}

const type MyVector::operator[](int i) const
{
  return ptr[i];
}

type &MyVector::operator[](int i)
{
  return ptr[i];
}

ostream &operator<<(ostream &os, const MyVector &v)
{
  os << "{";
  int i;
  for (i = 0; i < v.size - 1; ++i)
  {
    os << v.ptr[i] << ",";
  }
  os << v.ptr[i] << "}";
  return os;
}

void MyVector::push_back(type a)
{
  if (size == capacity)
  {
    capacity *= 2;
    unique_ptr<type[]> newptr = make_unique<type[]>(capacity);
    for (size_t i = 0; i < size; i++)
    {
      newptr[i] = ptr[i];
    }

    newptr.swap(ptr);
    for (size_t i = size; i < capacity; i++)
    {
      ptr[i] = 0;
    }
  }

  ptr[size] = a;
  size++;
}
type MyVector::pop_back()
{
  type a = ptr[size - 1];
  size--;
  if (capacity >= size * 4)
  {
    capacity /= 2;
    unique_ptr<type[]> newptr = make_unique<type[]>(capacity);
    memcpy(newptr.get(), ptr.get(), size * sizeof(type));
    newptr.swap(ptr);
  }
  return a;
}
int MyVector::getCapacity() const
{
  return capacity;
}

int MyVector::getSize() const
{
  return size;
}
void swap(MyVector &v1, MyVector &v2)
{
  using std::swap;
  swap(v1.capacity, v2.capacity);
  swap(v1.size, v2.size);
  v2.ptr.swap(v1.ptr);
}

// driver program. must be in a separate file
int main()
{

  type tab[] = {1, 2, 3, 4, 5};
  MyVector v1(tab, 5);
  v1.push_back(6);
  cout << "v1 = " << v1 << endl;
  MyVector v2;
  v2.push_back(8);
  v2.push_back(20);
  cout << "v2 = " << v2 << endl;
  MyVector v3(v2);
  cout << "v3 = " << v3 << endl;
  v3.push_back(50);
  cout << "v2 = " << v2 << endl;
  cout << "v3 = " << v3 << endl;
  v1.pop_back();
  cout << "v1 = " << v1 << endl;
  cout << "v1[0] = " << v1[0] << endl;
  v1[0] = 9;
  cout << "v1 = " << v1 << endl;
  cout << "overloading = operator" << endl;
  v2 = v1;
  cout << "v1 = " << v1 << endl;
  cout << "v2 = " << v2 << endl;
  v2.push_back(7);
  v1.push_back(100);
  cout << "v1 = " << v1 << endl;
  cout << "v2 = " << v2 << endl;
  return 0;
}