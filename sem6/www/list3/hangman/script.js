const words = [
    "komputer", "programowanie", "wisielec", "informatyka", "rozwój", 
    "aplikacja", "klawiatura", "internet", "algorytm", "strona",
    "zmienna", "funkcja", "przeglądarka", "baza", "sieć",
    "kraków", "warszawa", "poznań", "gdańsk", "łódź",
    "książka", "szkoła", "język", "żółw", "pająk",
    "zając", "śnieg", "góra", "rzeka", "morze"
];

let selectedWord = "";
let guessedLetters = [];
let incorrectGuesses = 0;
let gameOver = false;

const wordDisplay = document.getElementById("word-display");
const keyboard = document.getElementById("keyboard");
const resultMessage = document.getElementById("result-message");
const newGameBtn = document.getElementById("new-game-btn");
const cancelBtn = document.getElementById("cancel-btn");

const hangmanParts = ["part1", "part2", "part3", "part4", "part5", "part6"];

const STORAGE_KEY = "hangman_game_state";

function initializeKeyboard() {
    keyboard.innerHTML = "";
    const polishAlphabet = "aąbcćdeęfghijklłmnńoópqrsśtuvwxyzźż";
    
    for (const letter of polishAlphabet) {
        const keyElement = document.createElement("button");
        keyElement.textContent = letter;
        keyElement.classList.add("key");
        keyElement.addEventListener("click", () => handleLetterClick(letter, keyElement));
        
        if (guessedLetters.includes(letter)) {
            keyElement.classList.add("used");
        }
        
        keyboard.appendChild(keyElement);
    }
}

function initializeWordDisplay() {
    wordDisplay.innerHTML = "";
    
    for (let i = 0; i < selectedWord.length; i++) {
        const letterBox = document.createElement("div");
        letterBox.classList.add("letter-box");
        
        const letter = selectedWord[i];
        if (guessedLetters.includes(letter)) {
            letterBox.textContent = letter;
        }
        
        wordDisplay.appendChild(letterBox);
    }
}

function updateWordDisplay() {
    const letterBoxes = document.querySelectorAll(".letter-box");
    
    for (let i = 0; i < selectedWord.length; i++) {
        const letter = selectedWord[i];
        if (guessedLetters.includes(letter)) {
            letterBoxes[i].textContent = letter;
        }
    }
}

function handleLetterClick(letter, keyElement) {
    if (gameOver || keyElement.classList.contains("used")) {
        return;
    }
    
    keyElement.classList.add("used");
    guessedLetters.push(letter);
    
    if (selectedWord.includes(letter)) {
        updateWordDisplay();
        checkWin();
    } else {
        showNextHangmanPart();
        checkLose();
    }
    
    saveGameState();
}

function showNextHangmanPart() {
    if (incorrectGuesses < hangmanParts.length) {
        document.getElementById(hangmanParts[incorrectGuesses]).style.display = "block";
        incorrectGuesses++;
    }
}

function updateHangmanDrawing() {
    resetHangmanDrawing();
    for (let i = 0; i < incorrectGuesses; i++) {
        if (i < hangmanParts.length) {
            document.getElementById(hangmanParts[i]).style.display = "block";
        }
    }
}

function checkWin() {
    const isWin = [...selectedWord].every(letter => guessedLetters.includes(letter));
    
    if (isWin) {
        gameOver = true;
        resultMessage.textContent = "Wygrałeś! Słowo to: " + selectedWord;
        resultMessage.classList.add("win");
        clearGameState();
    }
}

function checkLose() {
    if (incorrectGuesses >= hangmanParts.length) {
        gameOver = true;
        resultMessage.textContent = "Przegrałeś! Słowo to: " + selectedWord;
        resultMessage.classList.add("lose");
        clearGameState();
    }
}

function resetHangmanDrawing() {
    hangmanParts.forEach(part => {
        document.getElementById(part).style.display = "none";
    });
}

function startNewGame() {
    selectedWord = words[Math.floor(Math.random() * words.length)];
    guessedLetters = [];
    incorrectGuesses = 0;
    gameOver = false;
    
    resetHangmanDrawing();
    initializeWordDisplay();
    initializeKeyboard();
    resultMessage.textContent = "";
    resultMessage.classList.remove("win", "lose");
    
    saveGameState();
}

function cancelGame() {
    gameOver = true;
    resultMessage.textContent = "Gra anulowana. Słowo to: " + selectedWord;
    resultMessage.classList.add("lose");
    
    document.querySelectorAll(".key").forEach(key => {
        key.classList.add("used");
    });
    
    const letterBoxes = document.querySelectorAll(".letter-box");
    for (let i = 0; i < selectedWord.length; i++) {
        letterBoxes[i].textContent = selectedWord[i];
    }
    
    clearGameState();
}

function saveGameState() {
    if (gameOver) return;
    
    const gameState = {
        selectedWord,
        guessedLetters,
        incorrectGuesses,
        gameOver,
        timestamp: new Date().getTime()
    };
    
    localStorage.setItem(STORAGE_KEY, JSON.stringify(gameState));
}

function loadGameState() {
    const savedState = localStorage.getItem(STORAGE_KEY);
    
    if (savedState) {
        try {
            const gameState = JSON.parse(savedState);
            const savedTime = new Date(gameState.timestamp);
            const currentTime = new Date();
            const hoursDiff = (currentTime - savedTime) / (1000 * 60 * 60);
            
            if (hoursDiff <= 24) {
                selectedWord = gameState.selectedWord;
                guessedLetters = gameState.guessedLetters;
                incorrectGuesses = gameState.incorrectGuesses;
                gameOver = gameState.gameOver;
                
                updateHangmanDrawing();
                initializeWordDisplay();
                initializeKeyboard();
                
                if (gameOver) {
                    checkWin();
                    checkLose();
                }

                return true;
            }
        } catch (error) {
            console.error("Błąd wczytywania stanu gry:", error);
        }
    }
    
    return false;
}

function clearGameState() {
    localStorage.removeItem(STORAGE_KEY);
}

newGameBtn.addEventListener("click", startNewGame);
cancelBtn.addEventListener("click", cancelGame);

document.addEventListener("keydown", (event) => {
    if (gameOver) return;
    
    const key = event.key.toLowerCase();
    const polishAlphabet = "aąbcćdeęfghijklłmnńoópqrsśtuvwxyzźż";
    
    if (polishAlphabet.includes(key)) {
        const keyElement = document.querySelector(`.key[data-letter="${key}"]`);
        if (keyElement && !keyElement.classList.contains("used")) {
            handleLetterClick(key, keyElement);
        }
    }
});

window.addEventListener("DOMContentLoaded", () => {
    if (!loadGameState()) {
        startNewGame();
    }
});

window.addEventListener("beforeunload", () => {
    if (!gameOver) {
        saveGameState();
    }
});
