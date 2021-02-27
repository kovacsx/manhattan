#include "manhattan.h"

using namespace std;
using namespace manhattan;

int main()
{
    const auto sampleWorld = World({{0, 0}, {2, 1}}, {{1, 2}, {3, 3}});

    cout << "Sample world: " << endl << sampleWorld;

    printDistances(closestBikesMinimumManhattan(sampleWorld));

    return 0;
}
