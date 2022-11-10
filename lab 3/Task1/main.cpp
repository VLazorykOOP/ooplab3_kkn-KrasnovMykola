#include <iostream>
#include <cmath>

using namespace std;

enum Color { RED, GREEN, BLUE };

class Triangle
{
public:
	Triangle()
	{
		setSideA(1);
		setSideB(1);
		setSideC(1);
		setColor(Color::RED);
	}

	Triangle(double a, double b, double c)
	{
		setSideA(a);
		setSideB(b);
		setSideC(c);
		setColor(Color::RED);
	}

	Triangle(double a, double b, double c, Color _color)
	{
		setSideA(a);
		setSideB(b);
		setSideC(c);
		setColor(_color);
	}

	double area()
	{
		double p = perimeter() / 2.0;
		return sqrt(p * (p - sideA) * (p - sideB) * (p - sideC));
	}

	double perimeter()
	{
		return sideA + sideB + sideC;
	}

	void setSideA(double a)
	{
		if (a > 0)
			sideA = a;
	}

	void setSideB(double b)
	{
		if (b > 0)
			sideB = b;
	}

	void setSideC(double c)
	{
		if (c > 0)
			sideC = c;
	}

	void setColor(Color _color)
	{
		color = _color;
	}

	double getSideA()
	{
		return sideA;
	}

	double getSideB()
	{
		return sideB;
	}

	double getSideC()
	{
		return sideC;
	}

	Color getColor()
	{
		return color;
	}

	void show()
	{
		switch (color)
		{
		case RED:
			std::cout << "\033[31m";
			break;
		case GREEN:
			std::cout << "\033[32m";
			break;
		case BLUE:
			std::cout << "\033[34m";
			break;
		default:
			break;
		}
		cout << "(" << sideA << ", " << sideB << ", " << sideC << ")" << "\033[0m" << endl;
	}

private:
	double sideA, sideB, sideC;
	Color color;
};

int main()
{
	Triangle t1, t2(3, 4, 5), t3(5, 6, 7, Color::GREEN);
	cout << "t1: "; t1.show();
	cout << "t2: "; t2.show();
	cout << "t3: "; t3.show();
	cout << "t1: S = " << t1.area() << "; P = " << t1.perimeter() << endl;
	cout << "t2: S = " << t2.area() << "; P = " << t2.perimeter() << endl;
	cout << "t3: S = " << t3.area() << "; P = " << t3.perimeter() << endl;
	cout << "t1: sideA = " << t1.getSideA() << "; sideB = " << t1.getSideB() << "; sideC = " << t1.getSideC() << endl;
	cout << "Try to change all sides to 0" << endl;
	t1.setSideA(0);
	t1.setSideB(0);
	t1.setSideC(0);
	cout << "t1: sideA = " << t1.getSideA() << "; sideB = " << t1.getSideB() << "; sideC = " << t1.getSideC() << endl;
}
