#define ROW1 8
#define ROW2 9
#define COL1 10
#define COL2 11

void setup()
{
  pinMode(ROW1, OUTPUT);
  pinMode(ROW2, OUTPUT);
  pinMode(COL1, INPUT_PULLUP);
  pinMode(COL2, INPUT_PULLUP);
  
  Serial.begin(9600);
}

String buttons = "";

void loop()
{
  for (int row = 0; row < 2; row++) {
    int currentRowPin = (row == 0) ? ROW1 : ROW2;
    int otherRowPin = (row == 0) ? ROW2 : ROW1;
    digitalWrite(currentRowPin, LOW);
    digitalWrite(otherRowPin, HIGH);

    if(digitalRead(COL1) == LOW){
      buttons += (row == 0) ? "1 " : "3 ";
    }
    if(digitalRead(COL2) == LOW){
      buttons += (row == 0) ? "2 " : "4 ";
    }
  }

  if(buttons != ""){
    Serial.println(buttons);
    buttons = "";
  }
  
  delay(200);
}
