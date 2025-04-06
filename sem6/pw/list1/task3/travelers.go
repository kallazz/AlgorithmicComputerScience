package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

const (
	// Travelers moving on the board
	nrOfTravelers = 25

	minSteps = 10
	maxSteps = 100

	minDelay = 10 * time.Millisecond
	maxDelay = 50 * time.Millisecond

	// Timeout for deadlock detection
	deadlockTimeout = 5 * maxDelay

	// 2D Board with torus topology
	boardWidth  = 6
	boardHeight = 6
)

type positionType struct {
	x int
	y int
}

type traceType struct {
	timeStamp float64
	id        int
	position  positionType
	symbol    rune
}

type tracesSequenceType struct {
	last       int
	traceArray []traceType
}

type travelerType struct {
	id       int
	symbol   rune
	position positionType
}

// Field represents a board position with occupancy management
type Field struct {
	mu         sync.Mutex
	occupied   bool
	occupierID int
}

func (f *Field) acquire(id int) bool {
	if f.mu.TryLock() {
		f.occupied = true
		f.occupierID = id
		return true
	}
	return false
}

func (f *Field) release() {
	f.occupied = false
	f.occupierID = -1
	f.mu.Unlock()
}

func moveDown(position *positionType) {
	position.y = (position.y + 1) % boardHeight
}

func moveUp(position *positionType) {
	position.y = (position.y + boardHeight - 1) % boardHeight
}

func moveRight(position *positionType) {
	position.x = (position.x + 1) % boardWidth
}

func moveLeft(position *positionType) {
	position.x = (position.x + boardWidth - 1) % boardWidth
}

func printTrace(trace traceType) {
	fmt.Printf("%.9f %d %d %d %c\n", trace.timeStamp, trace.id, trace.position.x, trace.position.y, trace.symbol)
}

func printTraces(traces tracesSequenceType) {
	for i := 0; i <= traces.last; i++ {
		printTrace(traces.traceArray[i])
	}
}

var board [boardWidth][boardHeight]Field

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

func printerTask(traceReportChannel <-chan tracesSequenceType, wg *sync.WaitGroup) {
	defer wg.Done()
	for traces := range traceReportChannel {
		printTraces(traces)
	}
}

func travelerTask(id int, symbol rune, startTime time.Time, traceReportChannel chan<- tracesSequenceType, wg *sync.WaitGroup) {
	defer wg.Done()

	source := rand.NewSource(time.Now().UnixNano() + int64(id))
	rng := rand.New(source)

	var traveler travelerType
	traveler.id = id
	traveler.symbol = symbol

	// Find initial position
	for {
		x := rng.Intn(boardWidth)
		y := rng.Intn(boardHeight)
		if board[x][y].acquire(id) {
			traveler.position = positionType{x: x, y: y}
			break
		}
	}

	nrOfSteps := minSteps + rng.Intn(maxSteps-minSteps)
	traces := tracesSequenceType{
		last:       -1,
		traceArray: make([]traceType, maxSteps+1),
	}

	timeStamp := time.Since(startTime).Seconds()
	storeTrace(&traces, traveler, timeStamp)

	// Wait for other travelers to initialize
	time.Sleep(10 * time.Millisecond)

	isDeadlocked := false
	for step := 0; step < nrOfSteps && !isDeadlocked; step++ {
		delay := minDelay + time.Duration(rng.Float64()*float64(maxDelay-minDelay))
		time.Sleep(delay)

		success := makeStep(&traveler, rng)
		if !success {
			// Mark as deadlocked (convert to lowercase)
			traveler.symbol = rune(traveler.symbol + 32)
			isDeadlocked = true
		}

		timeStamp = time.Since(startTime).Seconds()
		storeTrace(&traces, traveler, timeStamp)
	}

	traceReportChannel <- traces
}

func storeTrace(traces *tracesSequenceType, traveler travelerType, timeStamp float64) {
	traces.last++
	traces.traceArray[traces.last] = traceType{
		timeStamp: timeStamp,
		id:        traveler.id,
		position:  traveler.position,
		symbol:    traveler.symbol,
	}
}

func tryDirection(traveler *travelerType, direction int) (positionType, bool) {
	newPosition := traveler.position
	switch direction {
	case 0:
		moveUp(&newPosition)
	case 1:
		moveDown(&newPosition)
	case 2:
		moveLeft(&newPosition)
	case 3:
		moveRight(&newPosition)
	default:
		return newPosition, false
	}

	if board[newPosition.x][newPosition.y].acquire(traveler.id) {
		return newPosition, true
	}
	return newPosition, false
}

func makeStep(traveler *travelerType, rng *rand.Rand) bool {
	moveStart := time.Now()
	for {
		direction := rng.Intn(4)
		newPosition, success := tryDirection(traveler, direction)

		if success {
			board[traveler.position.x][traveler.position.y].release()
			traveler.position = newPosition
			return true
		}

		if time.Since(moveStart) > deadlockTimeout {
			return false
		}

		time.Sleep(minDelay + time.Duration(rng.Float64()*float64(maxDelay-minDelay)))
	}
}
