int pin_out = 3;
int dutyCycle = 0; // 0-255
String inInt;

void setup() {
  Serial.begin(9600);
}

void loop() {
  while (Serial.available() > 0) {
    char inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inInt += (char)inChar;
    }
    // if you get a newline, print the string, then the string's value:
    if (inChar == '>') {
      Serial.print("Value: ");
      Serial.println(inInt.toInt());
      // clear the string for new input:
      inInt = "";
    }
  }
/*
    if (incomingString.equals("u")){
        if (dutyCycle <= 245){
        dutyCycle += 10;}
        analogWrite(pin_out, dutyCycle);
        Serial.print("Duty Cycle: ");
        Serial.println(dutyCycle);
    }
    if (incomingString.equals("d")){
        if (dutyCycle >= 10){
        dutyCycle -= 10;}
        analogWrite(pin_out, dutyCycle);
        Serial.print("Duty Cycle: ");
        Serial.println(dutyCycle);
    }
    if (incomingString.equals("z")){
        dutyCycle = 0;
        analogWrite(pin_out, dutyCycle);
        Serial.print("Duty Cycle: ");
        Serial.println(dutyCycle);
    }
    if (incomingString.equals("m")){
        dutyCycle = 125;
        analogWrite(pin_out, dutyCycle);
        Serial.print("Duty Cycle: ");
        Serial.println(dutyCycle);
    }
    if (incomingString.equals("f")){
        dutyCycle = 255;
        analogWrite(pin_out, dutyCycle);
        Serial.print("Duty Cycle: ");
        Serial.println(dutyCycle);
    
    }
*/
}