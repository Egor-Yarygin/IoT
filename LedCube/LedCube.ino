int ledpins[] = {2, 3, 4, 5}; 
int groundpins[] = {6, 7}; 
int ledMapping[8][2] = {
  {2, 7}, 
  {3, 7}, 
  {4, 7}, 
  {5, 7}, 
  {2, 6}, 
  {3, 6}, 
  {4, 6}, 
  {5, 6}  
};

const int maxSequenceLength = 8; 
int ledSequence[maxSequenceLength]; 
int sequenceLength = 0; 
int sequenceIndex = 0; 
bool validInput = false;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 4; i++) {       
    pinMode(ledpins[i], OUTPUT); 
  }                         
  for (int i = 0; i < 2; i++) {
    pinMode(groundpins[i], OUTPUT); 
  }
  Serial.println("Введите номера светодиодов от 1 до 8.");
  Serial.println("Верхний слой    Нижний слой");
  Serial.println("   3 — 4           7 — 8");
  Serial.println("   |   |           |   |");
  Serial.println("   2 — 1           6 — 5");
  Serial.println("Пример: 1 2 8 3");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    parseInput(input);
    sequenceIndex = 0; 
  }

  if (validInput && sequenceLength > 0) {
    turnOnLed(ledSequence[sequenceIndex]);
    sequenceIndex = (sequenceIndex + 1) % sequenceLength;
  }
}

void turnOnLed(int ledNumber) {
  int pin = ledMapping[ledNumber - 1][0];
  int ground = ledMapping[ledNumber - 1][1];
  digitalWrite(pin, HIGH); 
  digitalWrite(ground, HIGH);
  delay(1); 
  digitalWrite(pin, LOW); 
  digitalWrite(ground, LOW); 
}

void parseInput(String input) {
  sequenceLength = 0;
  validInput = true;
  
  input.trim(); 
  
  int numBuffer = 0; 
  bool inNumber = false; 
  
  for (int i = 0; i < input.length(); i++) {
    char c = input[i];
    
    if (isdigit(c)) {
      numBuffer = numBuffer * 10 + (c - '0'); 
      inNumber = true;
    } else if (c == ' ') {
      if (inNumber) {
        if (numBuffer >= 1 && numBuffer <= 8 && sequenceLength < maxSequenceLength) {
          ledSequence[sequenceLength++] = numBuffer;
          numBuffer = 0; 
          inNumber = false;
        } else {
          Serial.println("Ошибка: Неверный номер светодиода.");
          validInput = false;
          return;
        }
      }
    } else {
      Serial.println("Ошибка: Неверный номер светодиода.");
      validInput = false;
      return;
    }
  }
  if (inNumber) {
    if (numBuffer >= 1 && numBuffer <= 8 && sequenceLength < maxSequenceLength) {
      ledSequence[sequenceLength++] = numBuffer;
    } else {
      Serial.println("Ошибка: Чисел не может быть больше 8 штук.");
      validInput = false;
    }
  }
  if (sequenceLength == 0) {
    Serial.println("Ошибка: Введите хотя бы один номер светодиода.");
    validInput = false;
  }

}
