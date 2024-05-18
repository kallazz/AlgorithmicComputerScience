#include "Philosopher.hpp"

#include <iostream>
#include <thread>

Philosopher::Philosopher(const int id, std::mutex &leftChopstick, std::mutex &rightChopstick, const int mealLimit, std::mutex &printingMutex)
    : id_(id)
    , leftChopstick_(leftChopstick)
    , rightChopstick_(rightChopstick)
    , mealLimit_(mealLimit)
    , printingMutex_(printingMutex)
{
    std::srand(std::time(nullptr));
}

void Philosopher::operator()() const {
    for (int i = 0; i < mealLimit_; i++) {
        think();
        pickUpChopstick(leftChopstick_);
        pickUpChopstick(rightChopstick_);
        eat();
        putDownChopstick(leftChopstick_);
        putDownChopstick(rightChopstick_);
    }
}

void Philosopher::think() const {
    print("Philosopher " + std::to_string(id_) + " is thinking.");
    sleepRandomDuration();
    print("Philosopher " + std::to_string(id_) + " stopped thinking.");
}

void Philosopher::eat() const {
    print("Philosopher " + std::to_string(id_) + " is eating.");
    sleepRandomDuration();
    print("Philosopher " + std::to_string(id_) + " stopped eating.");
}

void Philosopher::pickUpChopstick(std::mutex &chopstick) const {
    sleepRandomDuration();
    chopstick.lock();
}

void Philosopher::putDownChopstick(std::mutex &chopstick) const {
    sleepRandomDuration();
    chopstick.unlock();
}

void Philosopher::print(const std::string &text) const {
    printingMutex_.lock();
    std::cout << text << '\n';
    printingMutex_.unlock();
}

void Philosopher::sleepRandomDuration() const {
    const auto randomDuration = std::chrono::milliseconds(
        rand() % lowerDurationBoundMilliseconds_ + upperDurationBoundMilliseconds_ + 1
    );
    std::this_thread::sleep_for(randomDuration);
}
