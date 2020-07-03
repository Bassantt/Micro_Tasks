#include <Keypad.h>
unsigned long previousMillis = 0;
unsigned long previousMilliswitch = 0;
int currentfloor;
int targetfloor;
char requestkeypad[1000];
int i = 0;
int j = 0;
int numloop = 0;
int numnextloop = 0;
bool canmove = true;
const byte ROWS = 4; //four rows
const byte COLS = 2; //two columns
char keys[ROWS][COLS] = {
  {'7', '6'},
  {'5', '4'},
  {'3', '2'},
  {'1', '0'}
};
byte rowPins[ROWS] = {5, 6, 7, 8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {10, 9}; //connect to the column pinouts of the keypad
bool switchRise = false;
bool haveacall = false;
char floorcall;

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 2; i++) {
    pinMode(i, INPUT);
  }
  for (int i = 11; i < 14; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(A5, INPUT);
  pinMode(A4, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  currentfloor = 0;
  attachInterrupt(digitalPinToInterrupt(3), isaswitchcall, RISING);
}

void loop() {
  unsigned long currentMillis = millis();


  if (switchRise && (unsigned)(currentMillis - previousMilliswitch) >= 2000) {
    Serial.print("pass");
    haveacall = true;
    floorcall = (digitalRead(2) * 4 + digitalRead(1) * 2 + digitalRead(0) * 1) + 48;
    Serial.print(floorcall);
    switchRise = false;
  } else {
    haveacall = false;
  }

  int weieght = analogRead(A5);
  int acual = map(weieght, 0, 1023, 0, 100);
  if (acual > 70) {
    digitalWrite(A4, HIGH);
    canmove = false;
  } else {
    digitalWrite(A4, LOW);
    canmove = true;
  }
  // Serial.println(acual);

  char key = keypad.getKey();
  if (key || haveacall ) {
    if (key) {
      Serial.println("key press");
      Serial.println(key);
      if (i == j) {
        requestkeypad[j] = key ;
        j += 1;
      }
     if (requestkeypad[j - 1] != key) {
      if(requestkeypad[j - 1]>key){
      requestkeypad[j]= requestkeypad[j - 1];
      requestkeypad[j-1] = key ;}
      else{
         requestkeypad[j]=key;
        }
      j += 1;
    }
    } else {
      if (i == j) {
        requestkeypad[j] = floorcall ;
        j += 1;
      }
      if (requestkeypad[j - 1] != floorcall) {
      if(requestkeypad[j - 1]>floorcall){
      requestkeypad[j]= requestkeypad[j - 1];
      requestkeypad[j-1] = floorcall ;}
      else{
         requestkeypad[j]=floorcall;
        }
      j += 1;
    }
    }
    Serial.println("request");
    Serial.println(requestkeypad);
  }
  if (canmove) {
    if ((unsigned)(currentMillis - previousMillis) >= 1000) {
      if (j > i) {
        Serial.println("current request");
        Serial.println(requestkeypad[i]);
        if (requestkeypad[i] - 48 >= currentfloor) {
          numloop = (requestkeypad[i] - 48) - currentfloor;
          
          for (int i = 0; i < numloop; i++) {
            displayonsevwnsegment(currentfloor); //should display the current floor before move
            for (int i = 0; i < 2; i++) {
              moveup(0);
              moveup(1);
              moveup(2);
              moveup(3);
            }
            currentfloor += 1;
            // Serial.println(currentfloor);
          }
        }
        else {
          numloop = currentfloor - (requestkeypad[i] - 48);
          for (int i = 0; i < numloop; i++) {
            displayonsevwnsegment(currentfloor); //should display the current floor before move
            for (int i = 0; i < 2; i++) {
              movedown(0);
              movedown(1);
              movedown(2);
              movedown(3);
            }
            currentfloor -= 1;
          }
        }
        i++;
      }
      previousMillis = millis();
    }
  }
  displayonsevwnsegment(currentfloor); //should display the current floor before move
}
void displayonsevwnsegment(int num)
{
  //Serial.println(num);
  digitalWrite(11, num % 2);
  num /= 2;
  digitalWrite(12, num % 2);
  num /= 2;
  digitalWrite(13, num % 2); //Send the right most digit
}

void moveup(int nummove) {
  if (nummove == 0) {
    digitalWrite(A3, HIGH);
    digitalWrite(A2, LOW);
    digitalWrite(A1, LOW);
    digitalWrite(A0, HIGH);
  }
  if (nummove == 1) {
    digitalWrite(A3, HIGH);
    digitalWrite(A2, HIGH);
    digitalWrite(A1, LOW);
    digitalWrite(A0, LOW);
  }
  if (nummove == 2) {
    digitalWrite(A3, LOW);
    digitalWrite(A2, HIGH);
    digitalWrite(A1, HIGH );
    digitalWrite(A0, LOW);
  }
  if (nummove == 3) {
    digitalWrite(A3, LOW);
    digitalWrite(A2, LOW);
    digitalWrite(A1, HIGH);
    digitalWrite(A0, HIGH);
  }
  delay(30);
}

void movedown(int nummove) {
  if (nummove == 0) {
    digitalWrite(A3, HIGH);
    digitalWrite(A2, LOW);
    digitalWrite(A1, HIGH);
    digitalWrite(A0, LOW);
  }
  // 0110
  if (nummove == 1) {
    digitalWrite(A3, LOW);
    digitalWrite(A2, HIGH);
    digitalWrite(A1, HIGH);
    digitalWrite(A0, LOW);
  }
  //0101
  if (nummove == 2) {
    digitalWrite(A3, LOW);
    digitalWrite(A2, HIGH);
    digitalWrite(A1, LOW);
    digitalWrite(A0, HIGH);
  }
  //1001
  if (nummove == 3) {
    digitalWrite(A3, HIGH);
    digitalWrite(A2, LOW);
    digitalWrite(A1, LOW);
    digitalWrite(A0, HIGH);
  }
  delay(30);
}
void isaswitchcall() {
  previousMilliswitch = millis();
  switchRise = true;
}
