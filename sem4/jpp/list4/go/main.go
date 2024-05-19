package main

import (
	"dining-philosophers/philosopher"
	"sync"
)

const numberOfPhilosophers int = 5
const mealLimit int = 3

var waitGroup = sync.WaitGroup{}

func main() {
	var chopsticks = [numberOfPhilosophers]sync.Mutex{}
	var philosophers = [numberOfPhilosophers]*philosopher.Philosopher{}

	for i := 0; i < numberOfPhilosophers; i++ {
		var leftChopstick = &chopsticks[i]
		var rightChopstick = &chopsticks[(i+1)%numberOfPhilosophers]
		var phil *philosopher.Philosopher
		if i%2 == 0 {
			phil = philosopher.NewPhilosopher(i, rightChopstick, leftChopstick, mealLimit, &waitGroup)
		} else {
			phil = philosopher.NewPhilosopher(i, leftChopstick, rightChopstick, mealLimit, &waitGroup)
		}
		philosophers[i] = phil
	}

	for _, phil := range philosophers {
		waitGroup.Add(1)
		go phil.Dine()
	}
	waitGroup.Wait()
}
