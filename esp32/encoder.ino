#include <MD_REncoder.h> // This library for rotary
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
#define RotaryPinA 32 //SET DT PIN
#define RotaryPinB 25 //SET CLK PIN
MD_REncoder encoder_rotary = MD_REncoder(RotaryPinA, RotaryPinB);

#include <MD_UISwitch.h> //This library for button click (on the rotary)
const uint8_t DIGITAL_SWITCH_PIN = 33;       // SET SW PIN
const uint8_t DIGITAL_SWITCH_ACTIVE = LOW;   // digital signal when switch is pressed 'on'
MD_UISwitch_Digital encoder_switch(DIGITAL_SWITCH_PIN, DIGITAL_SWITCH_ACTIVE);

#include <Ticker.h>

Ticker tick; /* timer for interrupt handler */

void encoder_init(){
	encoder_rotary.begin();
	encoder_switch.begin();
	encoder_switch.enableDoublePress(false);
	//encoder_switch.enableLongPress(false);
	//encoder_switch.enableRepeat(false);
	//encoder_switch.enableRepeatResult(true);
}

void encoder_loop(){
	MD_UISwitch::keyResult_t k=encoder_switch.read();
	switch(k){
		case MD_UISwitch::KEY_NULL:      /*Serial.print("KEY_NULL");     */break;
		case MD_UISwitch::KEY_UP:        /*Serial.print("\nKEY_UP ");    */break;
		case MD_UISwitch::KEY_DOWN:      /*Serial.print("\n\nKEY_DOWN"); */break;
		case MD_UISwitch::KEY_PRESS:     Serial.println("KEY_PRESS");      break;
		case MD_UISwitch::KEY_DPRESS:    Serial.println("KEY_DOUBLE");     break;
		case MD_UISwitch::KEY_LONGPRESS: Serial.println("KEY_LONG");       break;
		case MD_UISwitch::KEY_RPTPRESS:  /*Serial.print("\nKEY_REPEAT ");*/break;
		default:                         /*Serial.print("\nKEY_UNKNWN ");*/break;
	}
	uint8_t x=encoder_rotary.read();
	if(x){
		if(x==DIR_CW){
			Serial.println("NEXT");
		}else{
			Serial.println("PREV");
		}
	}
}
