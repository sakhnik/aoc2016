#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

using namespace std;

bool IsAbba(const char *s)
{
	return s[0] == s[3] && s[1] == s[2] && s[0] != s[1];
}

bool IsTls(const string &addr)
{
	bool is_hyper{false};
	bool is_tls{false};

	for (size_t i = 0; i != addr.size() - 3; ++i)
	{
		switch (addr[i])
		{
		case '[':
			assert(!is_hyper);
			is_hyper = true;
			break;
		case ']':
			assert(is_hyper);
			is_hyper = false;
			break;
		default:
			if (IsAbba(addr.c_str() + i))
			{
				if (is_hyper)
					return false;
				is_tls = true;
			}
		}
	}

	return is_tls;
}

bool FindHyper(const string &addr, char a, char b)
{
	bool is_hyper{false};

	for (size_t i = 0; i != addr.size() - 2; ++i)
	{
		switch (addr[i])
		{
		case '[':
			is_hyper = true;
			break;
		case ']':
			is_hyper = false;
			break;
		default:
			if (is_hyper)
			{
				if (addr[i] == b && addr[i+1] == a && addr[i+2] == b)
					return true;
			}

		}
	}

	return false;
}

bool IsSsl(const string &addr)
{
	bool is_hyper{false};

	for (size_t i = 0; i != addr.length() - 2; ++i)
	{
		switch (addr[i])
		{
		case '[':
			assert(!is_hyper);
			is_hyper = true;
			break;
		case ']':
			assert(is_hyper);
			is_hyper = false;
			break;
		default:
			if (!is_hyper)
			{
				if (addr[i] == addr[i+2] && addr[i] != addr[i+1])
				{
					if (FindHyper(addr, addr[i], addr[i+1]))
						return true;
				}
			}
		}
	}

	return false;
}

template <typename FuncT>
int Solve(istream &&is, FuncT func)
{
	int count{0};

	string line;
	while (getline(is, line))
	{
		if (func(line))
			++count;
	}

	return count;
}

int main()
{
	assert(IsTls("abba[mnop]qrst"));
	assert(!IsTls("abcd[bddb]xyyx"));
	assert(!IsTls("aaaa[qwer]tyui"));
	assert(IsTls("ioxxoj[asdfgh]zxcvbn"));

	cout << Solve(ifstream("7.txt"), IsTls) << endl;

	assert(IsSsl("aba[bab]xyz"));
	assert(!IsSsl("xyx[xyx]xyx"));
	assert(IsSsl("aaa[kek]eke"));
	assert(IsSsl("zazbz[bzb]cdb"));

	cout << Solve(ifstream("7.txt"), IsSsl) << endl;

	return 0;
}
