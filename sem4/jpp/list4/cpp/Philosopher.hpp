#ifndef PHILOSOPHER_HPP
#define PHILOSOPHER_HPP

#include <chrono>
#include <mutex>

class Philosopher {
public:
    Philosopher(const int index, std::mutex &leftChopstick, std::mutex &rightChopstick, const int mealsLimit, std::mutex &printingMutex);
    void operator()() const;
private:
    const int index_;
    std::mutex &leftChopstick_;
    std::mutex &rightChopstick_;
    const int mealsLimit_;
    std::mutex &printingMutex_;

    void think() const;
    void eat() const;
    void pickUpChopstick(std::mutex &chopstick) const;
    void putDownChopstick(std::mutex &chopstick) const;
    void print(const std::string &text) const;
    std::chrono::milliseconds generateRandomDuration() const;
};

#endif // PHILOSOPHER_HPP
