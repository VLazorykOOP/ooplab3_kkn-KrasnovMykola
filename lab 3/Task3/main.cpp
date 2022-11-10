#include <iostream>
#include <iomanip>
#include <cfloat>

using namespace std;

class Matrix
{
public:
	static int matrix_count;

	string error_state = "";

	Matrix(unsigned int _n = 2)
	{
		matrix_count++;
		n = _n;
		m = _n;
		matrix = new float* [n];
		if (matrix == nullptr)
		{
			error_state = "Not enough memory!";
			return;
		}
		for (int i = 0; i < n; i++)
		{
			matrix[i] = new float[m];
			if (matrix[i] == nullptr)
			{
				error_state = "Not enough memory!";
				return;
			}
			for (int j = 0; j < m; j++)
			{
				matrix[i][j] = 0;
			}
		}
	}

	Matrix(unsigned int _n, unsigned int _m, float value)
	{
		matrix_count++;
		n = _n;
		m = _m;
		matrix = new float* [n];
		if (matrix == nullptr)
		{
			error_state = "Not enough memory!";
			return;
		}
		for (int i = 0; i < n; i++)
		{
			matrix[i] = new float[m];
			if (matrix[i] == nullptr)
			{
				error_state = "Not enough memory!";
				return;
			}
			for (int j = 0; j < m; j++)
			{
				matrix[i][j] = value;
			}
		}
	}

	Matrix(const Matrix& other)
	{
		matrix_count++;
		n = other.n;
		m = other.m;
		matrix = new float* [n];
		if (matrix == nullptr)
		{
			error_state = "Not enough memory!";
			return;
		}
		for (int i = 0; i < n; i++)
		{
			matrix[i] = new float[m];
			if (matrix[i] == nullptr)
			{
				error_state = "Not enough memory!";
				return;
			}
			for (int j = 0; j < m; j++)
			{
				matrix[i][j] = other.matrix[i][j];
			}
		}
	}

	Matrix operator=(const Matrix& other)
	{
		n = other.n;
		m = other.m;
		if (matrix)
		{
			for (int i = 0; i < n; i++)
				delete[]matrix[i];
			delete[]matrix;
		}
		matrix = new float* [n];
		if (matrix == nullptr)
		{
			error_state = "Not enough memory!";
			return Matrix();
		}
		for (int i = 0; i < n; i++)
		{
			matrix[i] = new float[m];
			if (matrix[i] == nullptr)
			{
				error_state = "Not enough memory!";
				return Matrix();
			}
			for (int j = 0; j < m; j++)
			{
				matrix[i][j] = other.matrix[i][j];
			}
		}
	}

	~Matrix()
	{
		matrix_count--;
		for (int i = 0; i < n; i++)
		{
			delete[]matrix[i];
		}
		delete[]matrix;
	}

	void set(unsigned int i, unsigned int j, float value)
	{
		if (i >= n || j >= m)
		{
			error_state = "Index out of range!";
			return;
		}
		matrix[i][j] = value;
	}

	float get(unsigned int i, unsigned int j)
	{
		if (i >= n || j >= m)
		{
			error_state = "Index out of range!";
			return FLT_MIN;
		}
		return matrix[i][j];
	}

	unsigned int rows()
	{
		return n;
	}

	unsigned int columns()
	{
		return m;
	}

	void randomize(int a, int b)
	{
		a *= 100; b *= 100;
		for (unsigned int i = 0; i < n; i++)
		{
			for (unsigned int j = 0; j < m; j++)
			{
				matrix[i][j] = ((rand() * rand()) % (b - a) + a) / 100.0;
			}
		}
	}

	Matrix operator+(Matrix other)
	{
		Matrix result(n, m, 0);
		if (n != other.n || m != other.m)
		{
			result.error_state = "Matrix size is not valid!";
			return result;
		}
		for (unsigned int i = 0; i < n; i++)
		{
			for (unsigned int j = 0; j < m; j++)
			{
				result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
			}
		}
		return result;
	}

	Matrix operator-(Matrix other)
	{
		Matrix result(n, m, 0);
		if (n != other.n || m != other.m)
		{
			result.error_state = "Matrix size is not valid!";
			return result;
		}
		for (unsigned int i = 0; i < n; i++)
		{
			for (unsigned int j = 0; j < m; j++)
			{
				result.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
			}
		}
		return result;
	}

	Matrix operator*(float x)
	{
		Matrix result(n, m, 0);
		for (unsigned int i = 0; i < n; i++)
		{
			for (unsigned int j = 0; j < m; j++)
			{
				result.matrix[i][j] = matrix[i][j] * x;
			}
		}
		return result;
	}

	bool operator==(Matrix other)
	{
		if (n != other.n || m != other.m)
			return false;

		for (unsigned int i = 0; i < n; i++)
		{
			for (unsigned int j = 0; j < m; j++)
			{
				if (matrix[i][j] != other.matrix[i][j])
					return false;
			}
		}
		return true;
	}

	bool operator!=(Matrix other)
	{
		return !(*this == other);
	}

	bool operator>(Matrix other)
	{
		if (n != other.n || m != other.m)
			return false;
		int count = 0;
		for (unsigned int i = 0; i < n; i++)
		{
			for (unsigned int j = 0; j < m; j++)
			{
				if (matrix[i][j] > other.matrix[i][j])
					count++;
			}
		}
		return (count == n * m);
	}

	bool operator<(Matrix other)
	{
		if (n != other.n || m != other.m)
			return false;
		int count = 0;
		for (unsigned int i = 0; i < n; i++)
		{
			for (unsigned int j = 0; j < m; j++)
			{
				if (matrix[i][j] < other.matrix[i][j])
					count++;
			}
		}
		return (count == n * m);
	}

	friend ostream& operator<<(ostream& out, Matrix other)
	{
		for (int i = 0; i < other.n; i++)
		{
			for (int j = 0; j < other.m; j++)
			{
				out << fixed;
				out << setprecision(2) << setw(8) << other.matrix[i][j];
			}
			out << endl;
		}
		return out;
	}

private:
	unsigned int n, m;
	float** matrix;
};

int Matrix::matrix_count = 0;

int main()
{
	srand(time(nullptr));
	Matrix m1(3), m2(3);
	Matrix* m3 = new Matrix();
	m1.randomize(1, 10);
	m2.randomize(1, 10);
	m3->randomize(1, 10);
	cout << "m1:\n" << m1 << endl;
	cout << "m2:\n" << m2 << endl;
	cout << "m3:\n" << *m3 << endl;
	cout << "Sum of matrices m1 and m2:\n" << m1 + m2 << endl;
	cout << "Diff of matrices m1 and m2:\n" << m1 - m2 << endl;
	cout << "m1 * 2:\n" << m1 * 2 << endl;
	cout << "m1 < (m1 * 2): " << boolalpha << (m1 < (m1 * 2)) << endl;
	cout << "m1 > (m1 * 2): " << boolalpha << (m1 > (m1 * 2)) << endl;
	cout << "m1 == m1: " << boolalpha << (m1 == m1) << endl;
	cout << "m1 == m2: " << boolalpha << (m1 == m2) << endl;
	cout << "m1 != m1: " << boolalpha << (m1 != m1) << endl;
	cout << "m1 != m2: " << boolalpha << (m1 != m2) << endl;
	m1.set(0, 0, 100);
	cout << "Set m1[0][0] as 100 and get it: " << m1.get(0, 0) << endl;
	cout << "The number of matrices created: " << Matrix::matrix_count << endl;
	cout << "Matrix m3 removal" << endl;
	delete m3;
	cout << "The number of matrices created: " << Matrix::matrix_count << endl;
}