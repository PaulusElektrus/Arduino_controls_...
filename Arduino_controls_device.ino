// Relais Pins
#define Relais_AC           6
#define Relais_AC_to_NT     7
#define Relais_NT_to_BT     8   
#define Relais_BT_to_DC     9
#define Relais_DC_to_WR     10
#define Relais_WR_to_AC     11

// ADS1115
#include<ADS1115_WE.h> 
#include<Wire.h>
#define I2C_ADDRESS 0x48
ADS1115_WE adc = ADS1115_WE(I2C_ADDRESS);

// PWM Output
#define PWM_NT 3
#define PWM_DC 5

// Variablen
float voltage = 0.0;
const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];
char commandFromESP[numChars] = {0};
float powerFromESP = 0.0;
boolean newData = false;


void setup(){
    Serial.begin(115200);
    Wire.begin();
    if(!adc.init()){
        Serial.println("ADS1115 not connected!");}
    adc.setVoltageRange_mV(ADS1115_RANGE_6144);
}


void loop(){
    recvWithStartEndMarkers();
    if (newData == true) {
        strcpy(tempChars, receivedChars);
        parseData();
        showParsedData();
        newData = false;
    }
    voltage = readChannel(ADS1115_COMP_0_GND);
    delay(1000);
}


float readChannel(ADS1115_MUX channel){
  float voltage = 0.0;
  adc.setCompareChannels(channel);
  adc.startSingleMeasurement();
  while(adc.isBusy()){}
  voltage = adc.getResult_V(); // alternative: getResult_mV for Millivolt
  return voltage;
}


void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0';
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}


void parseData() {      // split the data into its parts

    char * strtokIndx; // this is used by strtok() as an index

    strtokIndx = strtok(tempChars,",");
    strcpy(commandFromESP, strtokIndx);     

    strtokIndx = strtok(NULL, ",");
    powerFromESP = atof(strtokIndx);

}


void showParsedData() {
    Serial.print("Message: ");
    Serial.println(commandFromESP);
    Serial.print("Power: ");
    Serial.println(powerFromESP);
}