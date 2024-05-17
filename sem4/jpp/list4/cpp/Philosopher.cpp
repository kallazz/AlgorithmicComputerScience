#include "Philosopher.hpp"

#include <iostream>
#include <thread>

Philosopher::Philosopher(const int index, std::mutex &leftChopstick, std::mutex &rightChopstick, const int mealsLimit, std::mutex &printingMutex)
    : index_(index)
    , leftChopstick_(leftChopstick)
    , rightChopstick_(rightChopstick)
    , mealsLimit_(mealsLimit)
    , printingMutex_(printingMutex)
{
    std::srand(std::time(nullptr));
}

void Philosopher::operator()() const {
    for (int i = 0; i < mealsLimit_; i++) {
        think();
        pickUpChopstick(leftChopstick_);
        pickUpChopstick(rightChopstick_);
        eat();
        putDownChopstick(rightChopstick_);
        putDownChopstick(leftChopstick_);
    }
}

void Philosopher::think() const {
    print("Philosopher " + std::to_string(index_) + " is thinking.");
    std::this_thread::sleep_for(generateRandomDuration());
}

void Philosopher::eat() const {
    print("Philosopher " + std::to_string(index_) + " is eating.");
    std::this_thread::sleep_for(generateRandomDuration());
}

void Philosopher::pickUpChopstick(std::mutex &chopstick) const {
    std::this_thread::sleep_for(generateRandomDuration());
    chopstick.lock();
    print("Philosopher " + std::to_string(index_) + " picked up a chopstick.");
}

void Philosopher::putDownChopstick(std::mutex &chopstick) const {
    std::this_thread::sleep_for(generateRandomDuration());
    chopstick.unlock();
    print("Philosopher " + std::to_string(index_) + " put down a chopstick.");
}

void Philosopher::print(const std::string &text) const {
    printingMutex_.lock();
    std::cout << text << '\n';
    printingMutex_.unlock();
}

std::chrono::milliseconds Philosopher::generateRandomDuration() const {
    const int lowerLimit = 10;
    const int upperLimit = 20;
    const int randomDuration = rand() % upperLimit + lowerLimit + 1;
    return std::chrono::milliseconds{randomDuration};
}
