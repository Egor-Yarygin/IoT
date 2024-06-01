#define PIN_L 3
#define PIN_R 5

void setup(){
  pinMode(PIN_L, OUTPUT);
  pinMode(PIN_R, OUTPUT);
  Serial.begin(9600);
  
  Serial.println("Input l or r and then speed. Ex: l40");
}

void loop(){
  if (Serial.available()) {
    String input = Serial.readString();
    Serial.println(input);
    char command = input[0];
    input.remove(0, 1); 
    int speed = input.toInt();
    
    moveMotor(command, speed);
  }
}

void moveMotor(char dir, int speed){
  
  if (speed > 255){
    speed = 255;
  }else if (speed < 0) {
    speed = 0;
  }
  
  if (dir == 'l') {
    analogWrite(PIN_L, speed); 
    analogWrite(PIN_R, 0);
    return;
  } else if (dir == 'r') {
    analogWrite(PIN_R, speed); 
    analogWrite(PIN_L, 0);
    return;
  } else {
    Serial.println("Unknown command, input l or r ");
     return;
  }
}
