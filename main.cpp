#include <iostream>
#include <vector>

using namespace std;

struct Position {
	int x;
	int y;
};

struct Data {
	vector<Position> users;
	vector<Position> bikes;
};

Data generateData(int totalUsers, int totalBikes) {

}

double manhattanDistance(const Position &p1, const Position &p2) {
	return abs(p1.x - p2.x) + (p1.y - p2.y);
}

int main() {

}
