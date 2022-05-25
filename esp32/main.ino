void setup(){
	Serial.begin(115200);
	display_init();
	adc_init();
}
void loop(){
	adc_loop();
	display_loop();
}
