#pragma once

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <list>
#include <random>
#include <vector>

namespace manhattan {

// Forward declarations
struct Position;
struct World;

// Basic types
typedef std::vector<Position> Users;
typedef std::vector<Position> Bikes;
typedef std::list<std::pair<Position, Position>> MatchedBikes; // Users to Bikes

// API functions

/**
 * @brief manhattanDistance
 * // https://xlinux.nist.gov/dads/HTML/manhattanDistance.html
 * "Manhattan" distance between points p1 and p2
 * @return 
 */
long long manhattanDistance(const Position &p1, const Position &p2);

/**
 * @brief calculateTotalDistance - total Manhattan distance for first N users, N bikes.
 * @param world
 * @return 
 */
long long calculateTotalDistance(const World &world);

/**
 * @brief bikesForAll - returns first N bikes for first N users
 * @param world
 * @return list of matches
 */
MatchedBikes bikesForAll(const World &world);

/**
 * @brief closestBikesMinimumManhattan - returns users matched to bikes, so that the total Manhattan distance minimizes. Time complexity O(n^2 / 2).
 * @param world
 * @return list of matches
 */
MatchedBikes closestBikesMinimumManhattan(const World &world);

/**
 * @brief printDistances - prints users to bikes match list
 * @param bikes
 */
void printDistances(const MatchedBikes &bikes);

/**
 * @brief The Position struct
 */
struct Position
{
    long x = 0;
    long y = 0;

    static Position createRandom(long maxx, long maxy);
};

/**
 * @brief The World struct
 */
struct World
{
    World(int totalUsers, int totalBikes) : users(totalUsers), bikes(totalBikes) {}
    World(const Users &_users, const Bikes &_bikes) : users(_users), bikes(_bikes) {}

    std::vector<Position> users;
    std::vector<Position> bikes;

    static World generate(int totalUsers = 1000,
                          int totalBikes = 1000,
                          int worldWidth = 10000,
                          int worldHeight = 10000);
};

std::ostream &operator<<(std::ostream &os, const Position &self);
std::ostream &operator<<(std::ostream &os, const World &self);

} // namespace manhattan
