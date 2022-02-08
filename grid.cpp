#include <iostream>


class ArrayClass
{
  public:
  ArrayClass(int size)
  {
    m_length = size;
    m_array = nullptr;
    if(size > 0)
    {
      m_array = new int[m_length];
    }
  }
  
  ArrayClass(const ArrayClass & original)
  {
    // why is this bad? now original and the new class we're creating shares the same m_array
    // m_array = original.m_array;
    m_length = original.m_length;
    m_array = nullptr;
    
    if (m_length > 0)
    {
      m_array = new int[m_length];

      for (int i = 0; i < m_length; i++)
	m_array[i] = original.m_array[i];
    }
    
  }

  ArrayClass & operator = (const ArrayClass & right_side)
  {
    clear();
    m_length = right_side.m_length;
    m_array = nullptr;

    if (m_length > 0)
      {
	m_array = new int[m_length];

	for (int i = 0; i < m_length; i++)
	  m_array[i] = right_side.m_array[i];
      }
    return *this;
  }
  void clear()
  {
    delete [] m_array;
    m_array = nullptr;
  }
  int get_length() const
  {
    return m_length;
  }
  int get(int i) const
  {
    m_array[i] = 15;
    return m_array[i];
  }
  void set(int pos, int thing_to_set)
  {
    m_array[pos] = thing_to_set;
  }

  ~ArrayClass()
  {
    clear();
  }
  
  private:
  int m_length;
  int * m_array;
};

using namespace std;

int main()
{
  if (false)
    {
      
      int height = 0, width = 0;
      cin >> height;
      cin >> width;
      
      int ** my_grid = new int * [height];
      for (int row = 0; row < height; row++)
	{
	  my_grid[row] = new int [width];
	}
      
      for (int i = 0; i < height; i++)
	for (int j = 0; j < width; j++)
	  my_grid[i][j] = i * i + j;
      for (int i = 0; i < height; i++)
	{
	  for (int j = 0; j < width; j++)
	    {
	      
	      cout << my_grid[i][j] << " ";
	    }
	  cout << endl;
	}
      
      
      for (int row = 0; row < height; row++)
	{
	  delete [] my_grid[row];
	}
      delete [] my_grid;
    }

  ArrayClass myArray(10);
  for (int x = 0; x < 10; x++)
  {
    myArray.set(x, x + 1);
  }

  cout << myArray.get(7) << endl;


  ArrayClass myNotNullArray(45);

  ArrayClass left_hand(45);
  left_hand = myNotNullArray;
  
  return 0;
}
