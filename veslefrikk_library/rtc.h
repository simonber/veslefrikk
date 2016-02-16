#include <Wire.h>
#include "RTClib.h"

void initRTC ();
uint32_t get_Time();
uint8_t dec2bcd(uint8_t num);
uint8_t bcd2dec(uint8_t num);
