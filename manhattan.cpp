#include "manhattan.h"

using namespace std;
using namespace manhattan;

namespace {
const bool verbose = false;

MatchedBikes buildMatch(const World &world)
{
    MatchedBikes m;

    auto bike = world.bikes.begin();
    for (const auto &user : world.users) {
        m.push_back(make_pair(user, *bike));
        bike++;
    }

    return m;
}

} // namespace

Position Position::createRandom(long maxx, long maxy)
{
    long nx = abs((rand() * rand())) % maxx;
    long ny = abs((rand() * rand())) % maxy;
    return Position{nx, ny};
}

std::ostream &manhattan::operator<<(std::ostream &os, const Position &self)
{
    os << "(" << self.x << ":" << self.y << ")";
    return os;
}

World World::generate(int totalUsers, int totalBikes, int worldWidth, int worldHeight)
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

std::ostream &manhattan::operator<<(std::ostream &os, const manhattan::World &world)
{
    os << "Users: ";
    for_each(world.users.begin(), world.users.end(), [&os](const Position &u) { os << u << ", "; });

    os << endl << "Bikes: ";
    for_each(world.bikes.begin(), world.bikes.end(), [&os](const Position &b) { os << b << ", "; });
    os << endl;

    return os;
}

long long manhattan::manhattanDistance(const Position &p1, const Position &p2)
{
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

long long manhattan::calculateTotalDistance(const World &world)
{
    long long totalDistance = 0;

    if (verbose)
        cout << "calculateTotalDistance: " << world;

    auto bike = world.bikes.begin();
    for (const auto &user : world.users) {
        totalDistance += manhattanDistance(user, *bike);
        bike++;
    }

    if (verbose)
        cout << "    distance: " << totalDistance << endl;

    return totalDistance;
}

// Will simply pair users with bikes, no matter the distance
MatchedBikes manhattan::bikesForAll(const World &world)
{
    return buildMatch(world);
}

MatchedBikes manhattan::closestBikesMinimumManhattan(const World &world)
{
    auto newWorld = world;

    newWorld.bikes.resize(world.users.size());
    auto bestDistance = calculateTotalDistance(world);

    cout << "Initial distance: " << bestDistance << endl;

    // Try all the bikes combinations
    for (size_t a = 0; a < world.bikes.size(); a++) {
        for (size_t b = a + 1; b < world.bikes.size(); b++) {
            swap(newWorld.bikes[a], newWorld.bikes[b]);
            auto newDistance = calculateTotalDistance(newWorld);
            if (newDistance >= bestDistance) {
                if (verbose)
                    cout << "    best not improved, ignoring" << endl;
                swap(newWorld.bikes[a], newWorld.bikes[b]);
            } else {
                if (verbose)
                    cout << "    best score improved: " << bestDistance << " -> " << newDistance
                         << endl;
                bestDistance = newDistance;
            }
        }
    }

    cout << "Best distance: " << bestDistance << endl;

    return buildMatch(newWorld);
}

void manhattan::printDistances(const MatchedBikes &bikes)
{
    cout << "[ ";
    for (const auto &b : bikes) {
        cout << b.second << " -> " << b.first << " : " << manhattanDistance(b.first, b.second)
             << ", ";
    }
    cout << "]" << endl;
}
