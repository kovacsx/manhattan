#include "manhattan.h"

using namespace std;
using namespace manhattan;

int main()
{
    srand(0);

    const auto smallWorld = World::generate(3, 3, 10, 10);
    cout << "Small world: " << smallWorld;

    printDistances(closestBikesMinimumManhattan(smallWorld));

    cout << endl;
    cout << "Max world..." << endl;

    const auto normalWorld = World::generate();
    closestBikesMinimumManhattan(normalWorld);

    return 0;
}
