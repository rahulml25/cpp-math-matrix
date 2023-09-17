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

    return *(cols + cIdx);
  }
};

class Matrix
{
  int _rows, _cols;
  Row *array;

public:
  Matrix(int r = 0, int c = 0) : _rows(r), _cols(c)
  {
    array = (Row *)malloc(sizeof(Row) * _rows);

    for (int r = 0; r < _rows; r++)
    {
      array[r] = Row(_cols);
      for (int c = 0; c < _cols; c++)
      {
        array[r][c] = 0;
      }
    }
  }

  Matrix(initializer_list<initializer_list<int>> arr)
  {
    _rows = arr.size();
    _cols = arr.begin()->size();

    array = (Row *)malloc(sizeof(Row) * _rows);

    for (int r = 0; r < _rows; r++)
    {
      int newSize = arr.begin()[r].size();
      if (newSize != _cols)
      {
        char errorString[100];
        sprintf(errorString, "Uneven row size: size extended from %d to %d columns", _cols, newSize);
        throw invalid_argument(errorString);
      }

      array[r] = Row(_cols);

      for (int c = 0; c < _cols; c++)
      {
        array[r][c] = arr.begin()[r].begin()[c];
      }
    }
  }

  int rows()
  {
    return _rows;
  }

  int cols()
  {
    return _cols;
  }

  friend ostream &operator<<(ostream &os, Matrix matrix);

  Matrix operator+(Matrix const &otherMatrix)
  {
    const int rows = this->_rows, cols = this->_cols;
    Matrix newMatrix(rows, cols);

    for (int r = 0; r < rows; r++)
    {
      for (int c = 0; c < rows; c++)
      {
        newMatrix[r][c] = this->array[r][c] + (*(otherMatrix.array + r))[c];
      }
    }

    return newMatrix;
  }

  Matrix operator-(Matrix const &otherMatrix)
  {
    const int rows = this->_rows, cols = this->_cols;
    Matrix newMatrix(rows, cols);

    for (int r = 0; r < rows; r++)
    {
      for (int c = 0; c < rows; c++)
      {
        newMatrix[r][c] = this->array[r][c] - (*(otherMatrix.array + r))[c];
      }
    }

    return newMatrix;
  }

  Row &operator[](int rIdx)
  {
    if (rIdx >= _rows)
    {
      throw invalid_argument("row - Index out of range");
    }
    return array[rIdx];
  }
};

ostream &operator<<(ostream &os, Matrix matrix)
{
  for (int r = 0; r < matrix.rows(); r++)
  {
    os << "|";
    for (int c = 0; c < matrix.cols(); c++)
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

  Matrix m2 = {
      {1, 2, 1},
      {2, 9, 0},
      {6, 2, 3},
  };

  cout << m1 + m2 << endl;
  cout << m1 - m2 << endl;

  return 0;
}
