int Door_Led_Pin = 13; // выбрать контакт для светодиода
int Door_Sensor_Pin = 6; // контакт для датчика
int val = 0; // переменная для хранения состояния датчика

void setup() {
  pinMode(Door_Led_Pin, OUTPUT); // установить Door_Led_Pin как выход
  pinMode(Door_Sensor_Pin, INPUT); // установить Door_Sensor_Pin как вход
}

void loop(){
  val = digitalRead(Door_Sensor_Pin); // читать Door_Sensor_Pin
  if (val == HIGH) { // Если Door_Sensor N.C. (без магнита) -> HIGH : Дверь открыта / LOW : Дверь закрыта
    // Если Door_Sensor N.0. (nc с магнитом) -> HIGH : Дверь открыта / LOW : Дверь закрыта
    digitalWrite(Door_Led_Pin, LOW); //выключить светодиод Door_Led
  } else {
    digitalWrite(Door_Led_Pin, HIGH); //включить светодиод Door_Led
  }
}
