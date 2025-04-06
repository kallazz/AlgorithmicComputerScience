package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

const (
	// Travelers moving on the board
	nrOfTravelers = 15

	minSteps = 10
	maxSteps = 100

	minDelay = 10 * time.Millisecond
	maxDelay = 50 * time.Millisecond

	// 2D Board with torus topology
	boardWidth  = 15
	boardHeight = 15
)

// positionType represents positions on the board
type positionType struct {
	x int
	y int
}

// traceType represents a trace left by a traveler
type traceType struct {
	timeStamp float64
	id        int
	position  positionType
	symbol    rune
}

// tracesSequenceType holds an array of traces
type tracesSequenceType struct {
	last       int
	traceArray []traceType
}

// travelerType represents a traveler
type travelerType struct {
	id       int
	symbol   rune
	position positionType
}

// moveDown updates position moving down with torus topology
func moveDown(position *positionType) {
	position.y = (position.y + 1) % boardHeight
}

// moveUp updates position moving up with torus topology
func moveUp(position *positionType) {
	position.y = (position.y + boardHeight - 1) % boardHeight
}

// moveRight updates position moving right with torus topology
func moveRight(position *positionType) {
	position.x = (position.x + 1) % boardWidth
}

// moveLeft updates position moving left with torus topology
func moveLeft(position *positionType) {
	position.x = (position.x + boardWidth - 1) % boardWidth
}

// printTrace prints a single trace
func printTrace(trace traceType) {
	fmt.Printf("%.9f %d %d %d %c\n", trace.timeStamp, trace.id, trace.position.x, trace.position.y, trace.symbol)
}

// printTraces prints all traces
func printTraces(traces tracesSequenceType) {
	for i := 0; i <= traces.last; i++ {
		printTrace(traces.traceArray[i])
	}
}

func main() {
	fmt.Printf("-1 %d %d %d\n", nrOfTravelers, boardWidth, boardHeight)

	startTime := time.Now()

	traceReportChannel := make(chan tracesSequenceType, nrOfTravelers)

	var travelerWg sync.WaitGroup
	var printerWg sync.WaitGroup

	travelerWg.Add(nrOfTravelers)
	printerWg.Add(1)

	for i := 0; i < nrOfTravelers; i++ {
		go travelerTask(i, rune('A'+i), startTime, traceReportChannel, &travelerWg)
	}

	go printerTask(traceReportChannel, &printerWg)

	travelerWg.Wait()
	close(traceReportChannel)
	printerWg.Wait()
}

// printerTask collects and prints reports of traces
func printerTask(traceReportChannel <-chan tracesSequenceType, wg *sync.WaitGroup) {
	defer wg.Done()
	for traces := range traceReportChannel {
		printTraces(traces)
	}
}

// travelerTask simulates a traveler moving on the board
func travelerTask(id int, symbol rune, startTime time.Time, traceReportChannel chan<- tracesSequenceType, wg *sync.WaitGroup) {
	defer wg.Done()

	// Create a new random source with a unique seed
	source := rand.NewSource(time.Now().UnixNano() + int64(id))
	rng := rand.New(source)

	traveler := travelerType{
		id:     id,
		symbol: symbol,
		position: positionType{
			x: rng.Intn(boardWidth),
			y: rng.Intn(boardHeight),
		},
	}

	// Number of steps to be made by the traveler
	nrOfSteps := minSteps + rng.Intn(maxSteps-minSteps)

	// Create traces array with capacity for all steps plus initial position
	traces := tracesSequenceType{
		last:       -1,
		traceArray: make([]traceType, maxSteps+1),
	}

	timeStamp := time.Since(startTime).Seconds()

	// Store initial position
	storeTrace(&traces, traveler, timeStamp)

	// Wait a bit to ensure all travelers are initialized
	time.Sleep(10 * time.Millisecond)

	// Start moving
	for step := 0; step <= nrOfSteps; step++ {
		// Random delay between steps
		delay := minDelay + time.Duration(rng.Float64()*float64(maxDelay-minDelay))
		time.Sleep(delay)

		// Make a step
		makeStep(&traveler, rng)

		// Update timestamp and store trace
		timeStamp = time.Since(startTime).Seconds()
		storeTrace(&traces, traveler, timeStamp)
	}

	// Report traces to printer
	traceReportChannel <- traces
}

// storeTrace adds a trace to the traces array
func storeTrace(traces *tracesSequenceType, traveler travelerType, timeStamp float64) {
	traces.last++
	traces.traceArray[traces.last] = traceType{
		timeStamp: timeStamp,
		id:        traveler.id,
		position:  traveler.position,
		symbol:    traveler.symbol,
	}
}

// makeStep moves the traveler in a random direction
func makeStep(traveler *travelerType, rng *rand.Rand) {
	n := rng.Intn(4)
	switch n {
	case 0:
		moveUp(&traveler.position)
	case 1:
		moveDown(&traveler.position)
	case 2:
		moveLeft(&traveler.position)
	case 3:
		moveRight(&traveler.position)
	default:
		fmt.Printf("?????????????? %d\n", n)
	}
}
