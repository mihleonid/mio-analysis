int main_tick=0;
void setup(){
	Serial.begin(115200);
	display_init();
	adc_init();
	encoder_init();
}
void loop(){
	if(main_tick&1==1){
		encoder_loop();
	}
	adc_loop();
	if(main_tick==3){
		display_loop();
	}
	++main_tick;
	main_tick&=3;
}
