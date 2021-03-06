#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include <set>

using namespace std;

int walk(istream &&is)
{
	enum Direction
	{
		North = 0,
		East,
		South,
		West,

		DirectionCount
	};

	pair<int, int> coords{0, 0};
	set<decltype(coords)> visited;
	visited.insert(coords);

	auto direction = North;

	auto turn_right = [](Direction d)
	{
		return Direction((d + 1) % DirectionCount);
	};

	auto turn_left = [](Direction d)
	{
		return Direction((d + DirectionCount - 1) % DirectionCount);
	};

	auto move = [](auto coords, Direction d, int steps)
	{
		switch (d)
		{
		case North:
			return make_pair(coords.first, coords.second + steps);
		case East:
			return make_pair(coords.first + steps, coords.second);
		case South:
			return make_pair(coords.first, coords.second - steps);
		case West:
			return make_pair(coords.first - steps, coords.second);
		default:
			assert(false);
		}
	};


	string s;
	while (is >> s)
	{
		char turn = s[0];
		unsigned steps{0};
		sscanf(&s[1], "%d", &steps);

		switch (turn)
		{
		case 'R':
			direction = turn_right(direction);
			break;
		case 'L':
			direction = turn_left(direction);
			break;
		}

		for (; steps; --steps)
		{
			coords = move(coords, direction, 1);
			if (visited.find(coords) != visited.end())
			{
				return abs(coords.first) + abs(coords.second);
			}
			visited.insert(coords);
		}
	}

	return -1;
}

int main()
{
	assert(4 == walk(istringstream("R8, R4, R4, R8")));

	cout << walk(ifstream("1.txt"));
	return 0;
}
