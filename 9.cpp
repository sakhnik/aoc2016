#include <iostream>
#include <fstream>
#include <cassert>
#include <algorithm>

using namespace std;

string Decompress(const std::string &s)
{
	string ret;

	for (size_t i = 0; i != s.size(); )
	{
		auto ch = s[i];

		if (ch == '(')
		{
			int span{0}, count{0};
			int fields = sscanf(&s[i], "(%dx%d)", &span, &count);
			if (fields != 2)
				assert(false);
			i = s.find(')', i);
			assert(i != s.npos);
			++i;

			for (int j = 0; j < count; ++j)
			{
				ret.append(s, i, span);
			}

			i += span;
		}
		else
		{
			ret.push_back(ch);
			++i;
		}
	}

	return ret;
}

int main()
{
	assert(Decompress("ADVENT") == "ADVENT");
	assert(Decompress("A(1x5)BC") == "ABBBBBC");
	assert(Decompress("(3x3)XYZ") == "XYZXYZXYZ");
	assert(Decompress("A(2x2)BCD(2x2)EFG") == "ABCBCDEFEFG");
	assert(Decompress("(6x1)(1x3)A") == "(1x3)A");
	assert(Decompress("X(8x2)(3x3)ABCY") == "X(3x3)ABC(3x3)ABCY");

	ifstream ifs("9.txt");
	string s;
	getline(ifs, s, char{-1});

	auto d = Decompress(s);
	cout << count_if(begin(d), end(d), [](char c) { return !isspace(c); }) << endl;
	return 0;
}
