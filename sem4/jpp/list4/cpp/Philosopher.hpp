#ifndef PHILOSOPHER_HPP
#define PHILOSOPHER_HPP

#include <chrono>
#include <mutex>

class Philosopher {
public:
    Philosopher(const int id, std::mutex &leftChopstick, std::mutex &rightChopstick, const int mealLimit, std::mutex &printingMutex);
    void operator()() const;
private:
    const int id_;
    std::mutex &leftChopstick_;
    std::mutex &rightChopstick_;
    const int mealLimit_;
    std::mutex &printingMutex_;

    static constexpr int lowerDurationBoundMilliseconds_ = 50;
    static constexpr int upperDurationBoundMilliseconds_ = 100;

    void think() const;
    void eat() const;
    void pickUpChopstick(std::mutex &chopstick) const;
    void putDownChopstick(std::mutex &chopstick) const;
    void print(const std::string &text) const;
    void sleepRandomDuration() const;
};

#endif // PHILOSOPHER_HPP
