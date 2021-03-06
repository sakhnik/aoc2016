#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

using namespace std;

bool IsTriangle(int a, int b, int c)
{
	return a + b > c && a + c > b && b + c > a;
}

int Solve(istream &&is)
{
	int count{0};
	int a{0}, b{0}, c{0};

	while (is >> a >> b >> c)
	{
		if (IsTriangle(a, b, c))
			++count;
	}

	return count;
}

int Solve2(istream &&is)
{
	int count{0};
	int a{0}, b{0}, c{0};
	vector<int> t1, t2, t3;

	while (is >> a >> b >> c)
	{
		t1.emplace_back(a);
		t2.emplace_back(b);
		t3.emplace_back(c);

		if (t1.size() == 3)
		{
			if (IsTriangle(t1[0], t1[1], t1[2]))
				++count;
			t1.clear();
		}

		if (t2.size() == 3)
		{
			if (IsTriangle(t2[0], t2[1], t2[2]))
				++count;
			t2.clear();
		}

		if (t3.size() == 3)
		{
			if (IsTriangle(t3[0], t3[1], t3[2]))
				++count;
			t3.clear();
		}
	}

	assert(t1.empty());
	return count;
}

int main()
{
	cout << Solve(ifstream("3.txt")) << endl;
	cout << Solve2(ifstream("3.txt")) << endl;

	return 0;
}
