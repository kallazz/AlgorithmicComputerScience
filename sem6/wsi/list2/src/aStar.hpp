#ifndef A_STAR_HPP
#define A_STAR_HPP

#include "State.hpp"

#include <functional>
#include <vector>

int manhattanDistanceWithLinearConflict(const State& state, const int size);
int misplacedTiles(const State& state, const int size);
std::pair<std::vector<int>, int> solveAStar(State& initialState, const int size,
                                            const std::function<int(const State&, int)> heuristic);

#endif  // A_STAR_HPP
