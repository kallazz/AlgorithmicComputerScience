#include "Philosopher.hpp"

#include <mutex>
#include <thread>
#include <vector>

constexpr int NUMBER_OF_PHILOSOPHERS = 5;
constexpr int MEAL_LIMIT = 3;

int main() {
    std::vector<std::mutex> chopsticks(NUMBER_OF_PHILOSOPHERS);
    std::vector<std::thread> philosophers(NUMBER_OF_PHILOSOPHERS);
    std::mutex printingMutex;

    for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++) {
        auto& leftChopstick = chopsticks[i];
        auto& rightChopstick = chopsticks[(i + 1) % NUMBER_OF_PHILOSOPHERS];
        Philosopher philosopher = (i % 2 == 0)
                    ? Philosopher(i, rightChopstick, leftChopstick, MEAL_LIMIT, printingMutex)
                    : Philosopher(i, leftChopstick, rightChopstick, MEAL_LIMIT, printingMutex);
        philosophers[i] = std::thread(philosopher);
    }

    for (auto &philosopherThread : philosophers) {
        philosopherThread.join();
    }

    return 0;
}
