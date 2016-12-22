#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <cassert>

using namespace std;

int Solve(istream &&is)
{
	struct Data
	{
		int x, y;
		int avail, used;
	};

	vector<Data> lines;
	string line;
	while (getline(is, line))
	{
		static regex r(R"(/dev/grid/node-x(\d+)-y(\d+)\s+\d+T\s+(\d+)T\s+(\d+)T)");
		smatch m;
		if (!regex_search(line, m, r))
			continue;
		assert(m.size() == 5);

		Data d;
		d.x = stoi(m[1]);
		d.y = stoi(m[2]);
		d.used = stoi(m[3]);
		d.avail = stoi(m[4]);
		lines.push_back(d);
	}

	int count{};

	for (size_t i = 0; i != lines.size(); ++i)
		for (size_t j = 0; j != lines.size(); ++j)
			if (i != j && lines[i].used && lines[i].used <= lines[j].avail)
				++count;

	return count;
}

int main()
{
	cout << Solve(ifstream("22.txt")) << endl;
	return 0;
}
