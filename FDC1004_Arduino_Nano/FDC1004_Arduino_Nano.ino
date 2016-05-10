#include <SPI.h>
#include <Wire.h>
#include <FDC1004_differential.h> // Available on GitHub
#include <EEPROM.h>

// Serial commands
#define SET_BASE_CAP ('a')
#define GET_LVL ('b')
#define MEAS_C_LEVEL ('c')
#define MEAS_C_RL ('d')
#define MEAS_C_RE ('e')
#define SET_OFFSET_C_LEVEL ('f') // Requires valid float value after command, e.g. 'f-13.44'
#define SET_OFFSET_C_RL ('g') // Requires valid float value after command, e.g. 'g2.17'
#define SET_OFFSET_C_RE ('h') // Requires valid float value after command, e.g. h-4.94'

// Offset calibration registers
#define FDC1004_IS_OFFSET_CAL(x) (x >= 0x0D && x <= 0x0F)
#define OFFSET_CAL1 (0x0D) // Offset register for C_level
#define OFFSET_CAL2 (0x0E) // Offset register for C_rl
#define OFFSET_CAL3 (0x0F) // Offset register for C_re
#define OFFSET_INT 11 // Amount to bit-shift for placing the integer value in offset calibration registers

// EEPROM address for the base capacitance 
#define eeAddress 0
/***** Old defines for setting the base capacitance based on measurements ******
// Uncomment and comment based on what sensor you are programing
#define BASE_CAP 4.98 // Applies for water-level sensor #1
#define BASE_CAP 4.73 // Applies for water-level sensor #1
*/
FDC1004 fdc;
char command = 'x'; // Variable to handle commands from UART
float baseCapFloat = 0.00f; // Variable to handle base capacitanse

float measure(); // Function for measuring the water-level
int setCapOffset(uint8_t offsetRegister, float value); // Function to set offset registers

void setup() {
  Wire.begin();
  Serial.begin(9600);

  uint16_t offset = 0;
  uint16_t address = OFFSET_CAL1;
  EEPROM.get(address * 2, offset);
  fdc.write16(OFFSET_CAL1, offset); // Adds offset to MEAS1 from EEPROM
  address++;
  EEPROM.get(address * 2, offset);
  fdc.write16(OFFSET_CAL2, offset); // Adds offset to MEAS2 from EEPROM
  address++;
  EEPROM.get(address * 2, offset);
  fdc.write16(OFFSET_CAL3, offset); // Adds offset to MEAS3 from EEPROM
  
  EEPROM.get(eeAddress, baseCapFloat); // Retrieves base capacitance from EEPROM
  delay(100);
}

void loop() {
    if (Serial.available() > 0){
      Serial.readBytes(&command, 1);
      switch (command){
        case SET_BASE_CAP:
        baseCapFloat = fdc.getCapacitance(FDC1004_MEAS1, FDC1004_CIN1, FDC1004_CIN4);
        EEPROM.put(eeAddress, baseCapFloat);
        break;
        case GET_LVL:
        Serial.print(measure()); // Measures water level
        break;
        case SET_OFFSET_C_LEVEL:
        setCapOffset(OFFSET_CAL1, Serial.parseFloat());
        break;
        case SET_OFFSET_C_RL:
        setCapOffset(OFFSET_CAL2, Serial.parseFloat());
        break;
        case SET_OFFSET_C_RE:
        setCapOffset(OFFSET_CAL3, Serial.parseFloat());
        break;
        case MEAS_C_LEVEL:
        Serial.print((float)fdc.getCapacitance(FDC1004_MEAS1, FDC1004_CIN1, FDC1004_CIN4));
        break;
        case MEAS_C_RL:
        Serial.print((float)fdc.getCapacitance(FDC1004_MEAS2, FDC1004_CIN2, FDC1004_CIN4));
        break;
        case MEAS_C_RE:
        Serial.print((float)fdc.getCapacitance(FDC1004_MEAS3, FDC1004_CIN3, FDC1004_CIN4));
        break;
        default:
        break;
      }
    }
}

// Work-around function for using hardcoded base capacitance levels
float measure(){
  float c_level = fdc.getCapacitance(FDC1004_MEAS1, FDC1004_CIN1, FDC1004_CIN4);
  float c_rl = fdc.getCapacitance(FDC1004_MEAS2, FDC1004_CIN2, FDC1004_CIN4);
  float c_re = fdc.getCapacitance(FDC1004_MEAS3, FDC1004_CIN3, FDC1004_CIN4);

  return (c_level - baseCapFloat) / (c_rl - c_re);
}

// Function to set the offset registers
int setCapOffset(uint8_t offsetRegister, float value){
  if ((abs(value) < 16) && (FDC1004_IS_OFFSET_CAL(offsetRegister))){
    int integer = (int)value;
    int decimal = (int)(abs(value) * 100) % 100;
    uint16_t offset = 0;
    offset |= ((integer << OFFSET_INT) | decimal);
    EEPROM.put(offsetRegister * 2, offset); 
    fdc.write16(offsetRegister, offset);
    return 0;
  }
  else return 1;
}
