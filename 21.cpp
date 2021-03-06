#include <iostream>
#include <sstream>
#include <fstream>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

void Swap(string &s, int X, int Y)
{
	swap(s[X], s[Y]);
}

void Swap(string &s, char A, char B)
{
	swap(s[s.find(A)], s[s.find(B)]);
}

void RoL(string &s, int X)
{
	rotate(begin(s), begin(s) + X % s.size(), end(s));
}

void RoR(string &s, int X)
{
	int idx = ((int)s.size() - X) % (int)s.size();
	if (idx < 0)
		idx += s.size();
	rotate(begin(s), begin(s) + idx, end(s));
}

void RoB(string &s, char A)
{
	int idx = s.find(A);
	if (idx >= 4)
		++idx;
	++idx;

	idx = ((int)s.size() - idx) % (int)s.size();
	if (idx < 0)
		idx += s.size();

	rotate(begin(s), begin(s) + idx, end(s));
}

void Reverse(string &s, int X, int Y)
{
	reverse(begin(s) + X, begin(s) + Y + 1);
}

void Move(string &s, int X, int Y)
{
	char c = s[X];
	s.erase(s.begin() + X);
	if (Y >= (int)s.size())
		s.push_back(c);
	else
		s.insert(begin(s) + Y, c);
}

string Scramble(istream &&is, string s)
{
	string line;
	while (getline(is, line))
	{
		int X{}, Y{};
		char A{}, B{};
		if (2 == sscanf(line.c_str(), "swap position %d with position %d", &X, &Y))
			Swap(s, X, Y);
		else if (2 == sscanf(line.c_str(), "swap letter %c with letter %c", &A, &B))
			Swap(s, A, B);
		else if (1 == sscanf(line.c_str(), "rotate left %d steps", &X))
			RoL(s, X);
		else if (1 == sscanf(line.c_str(), "rotate right %d steps", &X))
			RoR(s, X);
		else if (1 == sscanf(line.c_str(), "rotate based on position of letter %c", &A))
			RoB(s, A);
		else if (2 == sscanf(line.c_str(), "reverse positions %d through %d", &X, &Y))
			Reverse(s, X, Y);
		else if (2 == sscanf(line.c_str(), "move position %d to position %d", &X, &Y))
			Move(s, X, Y);
	}

	return s;
}

string Unscramble(istream &&is, string s)
{
	vector<string> lines;

	string line;
	while (getline(is, line))
	{
		lines.push_back(line);
	}

	for (; !lines.empty(); lines.pop_back())
	{
		const auto &line = lines.back();

		int X{}, Y{};
		char A{}, B{};
		if (2 == sscanf(line.c_str(), "swap position %d with position %d", &X, &Y))
			Swap(s, X, Y);
		else if (2 == sscanf(line.c_str(), "swap letter %c with letter %c", &A, &B))
			Swap(s, A, B);
		else if (1 == sscanf(line.c_str(), "rotate right %d steps", &X))
			RoL(s, X);
		else if (1 == sscanf(line.c_str(), "rotate left %d steps", &X))
			RoR(s, X);
		else if (1 == sscanf(line.c_str(), "rotate based on position of letter %c", &A))
		{
			// Brute force initial position
			for (int i = 0, n = s.size(); i != n; ++i)
			{
				string s1(s);
				RoL(s1, i);
				RoB(s1, A);
				if (s1 == s)
				{
					RoL(s, i);
					break;
				}
			}
		}
		else if (2 == sscanf(line.c_str(), "reverse positions %d through %d", &X, &Y))
			Reverse(s, X, Y);
		else if (2 == sscanf(line.c_str(), "move position %d to position %d", &Y, &X))
			Move(s, X, Y);
	}

	return s;
}

int main()
{
	assert("ebcda" == Scramble(istringstream("swap position 4 with position 0"), "abcde"));
	assert("edcba" == Scramble(istringstream("swap letter d with letter b"), "ebcda"));
	assert("dabc" == Scramble(istringstream("rotate right 1 steps"), "abcd"));
	assert("bcdea" == Scramble(istringstream("rotate left 1 steps"), "abcde"));
	assert("ecabd" == Scramble(istringstream("rotate based on position of letter b"), "abdec"));
	assert("decab" == Scramble(istringstream("rotate based on position of letter d"), "ecabd"));
	assert("abcde" == Scramble(istringstream("reverse positions 0 through 4"), "edcba"));
	assert("bdeac" == Scramble(istringstream("move position 1 to position 4"), "bcdea"));
	assert("abdec" == Scramble(istringstream("move position 3 to position 0"), "bdeac"));

	cout << Scramble(ifstream("21.txt"), "abcdefgh") << endl;

	assert("abcde" == Unscramble(istringstream("swap position 4 with position 0"), "ebcda"));
	assert("ebcda" == Unscramble(istringstream("swap letter d with letter b"), "edcba"));
	assert("abcd" == Unscramble(istringstream("rotate right 1 steps"), "dabc"));
	assert("abcde" == Unscramble(istringstream("rotate left 1 steps"), "bcdea"));
	assert("abdec" == Unscramble(istringstream("rotate based on position of letter b"), "ecabd"));
	assert("ecabd" == Unscramble(istringstream("rotate based on position of letter d"), "decab"));
	assert("edcba" == Unscramble(istringstream("reverse positions 0 through 4"), "abcde"));
	assert("bcdea" == Unscramble(istringstream("move position 1 to position 4"), "bdeac"));
	assert("bdeac" == Unscramble(istringstream("move position 3 to position 0"), "abdec"));

	cout << Unscramble(ifstream("21.txt"), "fbgdceah") << endl;
	return 0;
}
