#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <list>
#include <random>
#include <vector>

using namespace std;

struct Position
{
    long x;
    long y;

    static Position createRandom(long maxx, long maxy)
    {
        long nx = abs((rand() * rand())) % maxx;
        long ny = abs((rand() * rand())) % maxy;
        return Position{nx, ny};
    }

    friend ostream &operator<<(ostream &os, const Position &self)
    {
        os << "(" << self.x << ":" << self.y << ")";
        return os;
    }
};

struct World
{
    World(int totalUsers, int totalBikes) : users(totalUsers), bikes(totalBikes) {}

    vector<Position> users;
    vector<Position> bikes;

    static World generate(int totalUsers = 1000,
                          int totalBikes = 1000,
                          int worldWidth = 10000,
                          int worldHeight = 10000)
    {
        World w(totalUsers, totalBikes);

        for_each(w.users.begin(), w.users.end(), [worldWidth, worldHeight](Position &p) {
            p = Position::createRandom(worldWidth, worldHeight);
        });

        w.bikes.reserve(totalBikes);
        for_each(w.bikes.begin(), w.bikes.end(), [worldWidth, worldHeight](Position &p) {
            p = Position::createRandom(worldWidth, worldHeight);
        });

        return w;
    }

    friend ostream &operator<<(ostream &os, const World &self)
    {
        os << "Users: ";
        for_each(self.users.begin(), self.users.end(), [&](const auto &u) { os << u; });

        os << endl << "Bikes: ";
        for_each(self.bikes.begin(), self.bikes.end(), [&](const auto &b) { os << b; });
        os << endl;

        return os;
    }
};

typedef list<pair<Position, Position>> MatchedBikes;

// https://xlinux.nist.gov/dads/HTML/manhattanDistance.html
long long manhattanDistance(const Position &p1, const Position &p2)
{
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

MatchedBikes findInitialBikes(const World &world)
{
    auto bikeIter = world.bikes.begin();

    MatchedBikes matchedBikes;

    for (const auto &user : world.users) {
        matchedBikes.push_back(make_pair(user, *bikeIter));
        bikeIter++;
    }

    return matchedBikes;
}

void printDistances(const MatchedBikes &bikes)
{
    cout << "[ ";
    for (const auto &b : bikes) {
        cout << b.first << " -> " << b.second << " : " << manhattanDistance(b.first, b.second)
             << ", ";
    }
    cout << "]" << endl;
}

int main()
{
    //srand(time(nullptr));
    srand(0);

    const auto smallWorld = World::generate(2, 3, 10, 10);

    cout << smallWorld;

    auto matchedBikes = findInitialBikes(smallWorld);

    printDistances(matchedBikes);

    return 0;
}
