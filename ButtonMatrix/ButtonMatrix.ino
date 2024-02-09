#define UP 2
#define DOWN 3
#define LEFT 4
#define RIGHT 5

void setup()
{
  pinMode(UP, OUTPUT);
  pinMode(DOWN, OUTPUT);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);
  
  Serial.begin(9600);
}

String buttons = "";

void loop()
{
  digitalWrite(UP, LOW);
  digitalWrite(DOWN, HIGH);
  if(digitalRead(LEFT) == LOW){
    buttons += "1 ";
  }
  if(digitalRead(RIGHT) == LOW){
    buttons += "2 ";
  }
  delay(200);
  digitalWrite(UP, HIGH);
  digitalWrite(DOWN, LOW);
  if(digitalRead(LEFT) == LOW){
    buttons += "3 ";
  }
  if(digitalRead(RIGHT) == LOW){
    buttons += "4 ";
  }
  if(buttons != ""){
    Serial.println(buttons);
    buttons = "";
  }
  delay(200);
}

