#include <iostream>
#include <malloc.h>

using namespace std;

class Row
{
private:
  int *cols;
  int size;

public:
  Row(int s) : size(s)
  {
    cols = (int *)malloc(sizeof(int) * s);
  }

  int &operator[](int cIdx)
  {
    if (cIdx >= size)
    {
      throw invalid_argument("column - Index out of range");
    }

    return cols[cIdx];
  }
};

class Matrix
{
  int rows, cols;
  Row *array;

public:
  Matrix(int r, int c) : rows(r), cols(c)
  {
    array = (Row *)malloc(sizeof(Row) * rows);

    for (int r = 0; r < rows; r++)
    {
      *(array + r) = Row(cols);
      for (int c = 0; c < cols; c++)
      {
        array[r][c] = 0;
      }
    }
  }

  Matrix(initializer_list<initializer_list<int>> arr)
  {

    rows = arr.size();
    cols = 0;

    if (rows > 0)
    {
      cols = arr.begin()->size();
    }

    Matrix(rows, cols);

    for (int r = 0; r < rows; r++)
    {
      int newSize = arr.begin()[r].size();
      if (newSize != cols)
      {
        char errorString[100];
        sprintf(errorString, "Uneven row size: size extended from %d to %d columns", cols, newSize);
        throw invalid_argument(errorString);
      }
      for (int c = 0; c < cols; c++)
      {

        array[r][c] = arr.begin()[r].begin()[c];
      }
    }
  }

  friend ostream &operator<<(ostream &os, Matrix &matrix);

  Row &operator[](int rIdx)
  {
    if (rIdx >= rows)
    {
      throw invalid_argument("row - Index out of range");
    }
    return *(array + rIdx);
  }
};

ostream &operator<<(ostream &os, Matrix &matrix)
{
  for (int r = 0; r < matrix.rows; r++)
  {
    os << "|";
    for (int c = 0; c < matrix.cols; c++)
    {
      os << " " << matrix[r][c] << " ";
    }
    os << "|\n";
  }

  return os;
}

int main()
{
  Matrix m1 = {
      {1, 2, 3},
      {2, 9, 0},
      {6, 2, 3},
  };

  cout << m1;

  return 0;
}
