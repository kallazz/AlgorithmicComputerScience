package philosopher

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

const (
	lowerDurationBound int           = 50
	upperDurationBound int           = 100
	durationUnit       time.Duration = time.Millisecond
)

var rng = rand.New(rand.NewSource(time.Now().UnixNano()))

type Philosopher struct {
	id             int
	leftChopstick  *sync.Mutex
	rightChopstick *sync.Mutex
	mealsLimit     int
	waitGroup      *sync.WaitGroup
}

func NewPhilosopher(id int, leftChopstick *sync.Mutex, rightChopstick *sync.Mutex, mealsLimit int, waitGroup *sync.WaitGroup) *Philosopher {
	return &Philosopher{id, leftChopstick, rightChopstick, mealsLimit, waitGroup}
}

func (p Philosopher) Dine() {
	for i := 0; i < p.mealsLimit; i++ {
		p.think()
		p.pickUpChopstick(p.leftChopstick)
		p.pickUpChopstick(p.rightChopstick)
		p.eat()
		p.putDownChopstick(p.leftChopstick)
		p.putDownChopstick(p.rightChopstick)
	}
	p.waitGroup.Done()
}

func (p Philosopher) think() {
	fmt.Printf("Philosopher %v is thinking.\n", p.id)
	p.sleepRandomDuration()
	fmt.Printf("Philosopher %v stopped thinking.\n", p.id)
}

func (p Philosopher) eat() {
	fmt.Printf("Philosopher %v is eating.\n", p.id)
	p.sleepRandomDuration()
	fmt.Printf("Philosopher %v stopped eating.\n", p.id)
}

func (p Philosopher) pickUpChopstick(chopstick *sync.Mutex) {
	p.sleepRandomDuration()
	chopstick.Lock()
}

func (p Philosopher) putDownChopstick(chopstick *sync.Mutex) {
	p.sleepRandomDuration()
	chopstick.Unlock()
}

func (p Philosopher) sleepRandomDuration() {
	var randomDuration = time.Duration(rng.Intn(lowerDurationBound) + upperDurationBound)
	time.Sleep(randomDuration * durationUnit)
}
