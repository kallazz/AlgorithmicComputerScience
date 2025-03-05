#define LED 13

volatile char serialInput;
volatile int delayTime;
volatile int shortSignalDelayTime;
volatile int longSignalDelayTime;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  delayTime = 1000;
  shortSignalDelayTime = 1000;
  longSignalDelayTime = 3000;
}

void loop() {
  while(Serial.available())
  {
    serialInput = Serial.read();
    switch(serialInput)
    {
      case 'a' :  emitShortSignal();
                  emitLongSignal();
                  break;
      case 'b' :  emitLongSignal();
                  emitShortSignal();
                  emitShortSignal();
                  emitShortSignal();
                  break;
      case 'c' :  emitLongSignal();
                  emitShortSignal();
                  emitLongSignal();
                  emitShortSignal();
                  break;
      case 'd' :  emitLongSignal();
                  emitShortSignal();
                  emitShortSignal();
                  break;
      case 'e' :  emitShortSignal();
                  break;
      case 'f' :  emitShortSignal();
                  emitShortSignal();
                  emitLongSignal();
                  emitShortSignal();
                  break;
      case 'g' :  emitLongSignal();
                  emitLongSignal();
                  emitShortSignal();
                  break;
      case 'h' :  emitShortSignal();
                  emitShortSignal();
                  emitShortSignal();
                  emitShortSignal();
                  break;
      case 'i' :  emitShortSignal();
                  emitShortSignal();
                  break;
      case 'j' :  emitShortSignal();
                  emitLongSignal();
                  emitLongSignal();
                  emitLongSignal();
                  break;
      case 'k' :  emitLongSignal();
                  emitShortSignal();
                  emitLongSignal();
                  break;
      case 'l' :  emitShortSignal();
                  emitLongSignal();
                  emitShortSignal();
                  emitShortSignal();
                  break;
      case 'm' :  emitLongSignal();
                  emitLongSignal();
                  break;
      case 'n' :  emitLongSignal();
                  emitShortSignal();
                  break;
      case 'o' :  emitLongSignal();
                  emitLongSignal();
                  emitLongSignal();
                  break;
      case 'p' :  emitShortSignal();
                  emitLongSignal();
                  emitLongSignal();
                  emitShortSignal();
                  break;
      case 'q' :  emitLongSignal();
                  emitLongSignal();
                  emitShortSignal();
                  emitLongSignal();
                  break;
      case 'r' :  emitShortSignal();
                  emitLongSignal();
                  emitShortSignal();
                  break;
      case 's' :  emitShortSignal();
                  emitShortSignal();
                  emitShortSignal();
                  break;
      case 't' :  emitLongSignal();
                  break;
      case 'u' :  emitShortSignal();
                  emitShortSignal();
                  emitLongSignal();
                  break;
      case 'v' :  emitShortSignal();
                  emitShortSignal();
                  emitShortSignal();
                  emitLongSignal();
                  break;
      case 'w' :  emitShortSignal();
                  emitLongSignal();
                  emitLongSignal();
                  break;
      case 'x' :  emitLongSignal();
                  emitShortSignal();
                  emitShortSignal();
                  emitLongSignal();
                  break;
      case 'y' :  emitLongSignal();
                  emitShortSignal();
                  emitLongSignal();
                  emitLongSignal();
                  break;
      case 'z' :  emitLongSignal();
                  emitLongSignal();
                  emitShortSignal();
                  emitShortSignal();
                  break;
      default  : Serial.println("?");
    }
  }
}

void emitShortSignal() {
  digitalWrite(LED, HIGH);
  delay(shortSignalDelayTime);
  digitalWrite(LED, LOW);    
  delay(delayTime);
}

void emitLongSignal() {
  digitalWrite(LED, HIGH);
  delay(longSignalDelayTime);
  digitalWrite(LED, LOW);    
  delay(delayTime);
}
