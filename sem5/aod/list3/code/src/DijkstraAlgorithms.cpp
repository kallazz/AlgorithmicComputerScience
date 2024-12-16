#include "DijkstraAlgorithms.hpp"
#include "Graph.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <queue>

constexpr long long INF = std::numeric_limits<long long>::max();

std::vector<long long> basicDijkstra(const Graph &graph, const int sourceVertex) {
    const int numberOfVertices = graph.getNumberOfVertices();

    std::vector<long long> distances(numberOfVertices, INF);
    std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<>> priorityQueue;

    distances[sourceVertex] = 0;
    priorityQueue.push({0, sourceVertex});

    while (!priorityQueue.empty()) {
        const auto [currentdistances, currentVertex] = priorityQueue.top();
        priorityQueue.pop();

        if (currentdistances > distances[currentVertex]) {
            continue;
        }

        for (const auto [adjacentVertex, weight] : graph.getAdjacencyList()[currentVertex]) {
            if (distances[adjacentVertex] > distances[currentVertex] + weight) {
                distances[adjacentVertex] = distances[currentVertex] + weight;
                priorityQueue.push({distances[adjacentVertex], adjacentVertex});
            }
        }
    }

    return distances;
}

std::vector<long long> dialDijkstra(const Graph &graph, const int sourceVertex) {
    const int numberOfVertices = graph.getNumberOfVertices();
    const int amountOfBuckets = graph.getMaxWeight() + 1;

    std::vector<long long> distances(numberOfVertices, INF);
    std::vector<std::deque<long long>> buckets(amountOfBuckets);

    distances[sourceVertex] = 0;
    buckets[0].push_back(sourceVertex);

    long long currentBucketIndex = 0;
    long long amountOfCalculatedShortestDistances = 0;

    while (amountOfCalculatedShortestDistances != graph.getNumberOfVertices()) {
        while (!buckets[currentBucketIndex % amountOfBuckets].empty()) {
            const long long currentVertex = buckets[currentBucketIndex % amountOfBuckets].front();
            buckets[currentBucketIndex % amountOfBuckets].pop_front();

            if (currentBucketIndex > distances[currentVertex]) {
                continue;
            }

            amountOfCalculatedShortestDistances++;

            for (const auto [adjacentVertex, weight] : graph.getAdjacencyList()[currentVertex]) {
                if (distances[adjacentVertex] > distances[currentVertex] + weight) {
                    distances[adjacentVertex] = distances[currentVertex] + weight;
                    buckets[distances[adjacentVertex] % amountOfBuckets].push_back(adjacentVertex);
                }
            }
        }

        currentBucketIndex++;
    }

    return distances;
}

int findBucketIndex(const std::vector<long long> &ranges, const long long distance) {
    for (int i = ranges.size() - 1; i >= 0; i--) {
        if (distance >= ranges[i]) {
            return i;
        }
    }

    return -1;
}

void moveVertexToBucket(std::vector<std::vector<int>> &buckets, const std::vector<long long> &ranges, const int vertex, const long long distance) {
    const int bucketIndex = findBucketIndex(ranges, distance);
    buckets[bucketIndex].push_back(vertex);
}

void updateRanges(std::vector<long long> &ranges, const int bucketIndex, const long long minDistance) {
    ranges[0] = minDistance;
    ranges[1] = minDistance + 1;
    ranges[bucketIndex] = INF;
    for (int i = 2; i < bucketIndex; i++) {
        ranges[i] = pow(2, i - 1) + minDistance;
    }
}


std::vector<long long> radixHeapDijkstra(const Graph &graph, const int sourceVertex) {
    const int amountOfBuckets = ceil(log2(graph.getNumberOfVertices()) + log2(graph.getMaxWeight())) + 1;
    std::vector<long long> distances(graph.getNumberOfVertices(), INF);
    std::vector<long long> ranges = std::vector<long long>(amountOfBuckets, 0);
    std::vector<std::vector<int>> buckets(amountOfBuckets);

    ranges[0] = 0;
    ranges[1] = 1;
    for (int currentBucketIndex = 2; currentBucketIndex < amountOfBuckets; currentBucketIndex++)
    {
        ranges[currentBucketIndex] = pow(2, currentBucketIndex - 1);
    }

    distances[sourceVertex] = 0;
    buckets[0].push_back(sourceVertex);

    int currentBucketIndex = 0;

    while (currentBucketIndex < amountOfBuckets) {
        if (buckets[currentBucketIndex].size() == 1 || currentBucketIndex <= 1) {
            while (!buckets[currentBucketIndex].empty()) {
                const int currentVertex = buckets[currentBucketIndex].back();
                buckets[currentBucketIndex].pop_back();

                for (const auto& [adjacentVertex, weight] : graph.getAdjacencyList()[currentVertex]) {
                    const long long newDistance = distances[currentVertex] + weight;
                    if (distances[adjacentVertex] > newDistance) {
                        const long long oldDistance = distances[adjacentVertex];

                        if (oldDistance != INF) {
                            const int oldBucketIndex = findBucketIndex(ranges, oldDistance);
                            buckets[oldBucketIndex].erase(std::remove(buckets[oldBucketIndex].begin(), buckets[oldBucketIndex].end(), adjacentVertex), buckets[oldBucketIndex].end());
                        }

                        distances[adjacentVertex] = newDistance;
                        moveVertexToBucket(buckets, ranges, adjacentVertex, newDistance);
                    }
                }
            }
        }
        else if (buckets[currentBucketIndex].size() > 1) {
            long long minDistance = INF;
            for (int i = 0; i < buckets[currentBucketIndex].size(); i++) {
                if (distances[buckets[currentBucketIndex][i]] < minDistance) {
                    minDistance = distances[buckets[currentBucketIndex][i]];
                }
            }
            
            updateRanges(ranges, currentBucketIndex, minDistance);

            while (!buckets[currentBucketIndex].empty()) {
                const int currentVertex = buckets[currentBucketIndex].back();
                buckets[currentBucketIndex].pop_back();

                moveVertexToBucket(buckets, ranges, currentVertex, distances[currentVertex]);
            }
            currentBucketIndex = -1;
        }

        currentBucketIndex++;
    }

    return distances;
}
