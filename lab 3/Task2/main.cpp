#include <iostream>

using namespace std;

class Set
{
public:
	Set()
	{
		beg = 0;
		end = 100;
		set = new unsigned int[end - beg];
		for (int i = 0; i < end - beg; i++)
			set[i] = 0;
	}

	Set(unsigned int e)
	{
		beg = 0;
		end = e;
		set = new unsigned int[end - beg];
		for (int i = 0; i < end - beg; i++)
			set[i] = 0;
	}

	Set(unsigned int b, unsigned int e, unsigned int value = 0)
	{
		if (b > e)
		{
			int t = b;
			b = e;
			e = t;
			cout << "WARNING: The beginning and the end have changed places!" << endl;
		}
		beg = b;
		end = e;
		set = new unsigned int[end - beg];
		for (int i = 0; i < end - beg; i++)
			set[i] = value;
	}

	Set(const Set& s)
	{
		beg = s.beg;
		end = s.end;
		set = new unsigned int[end - beg];
		for (int i = 0; i < end - beg; i++)
			set[i] = s.set[i];
	}

	Set operator =(Set s)
	{
		beg = s.beg;
		end = s.end;
		set = new unsigned int[end - beg];
		for (int i = 0; i < end - beg; i++)
			set[i] = s.set[i];
	}

	~Set()
	{
		if (set)
			delete[]set;
	}

	void set_value(unsigned int value)
	{
		for (int i = 0; i < end - beg; i++)
			set[i] = value;
	}

	unsigned int size()
	{
		return end - beg;
	}

private:
	unsigned int beg, end;
	unsigned int* set;
};

int main()
{
	Set s1, s2(10), s3(10, 20), s4(20, 30, 100);
	Set s5(s1);
	Set s6 = s2;
	cout << "s1 size: " << s1.size() << endl;
	cout << "s3 size: " << s3.size() << endl;
	cout << "s5 size: " << s5.size() << endl;
	s1.set_value(100);
}
