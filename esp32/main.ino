int main_tick=0;
void panic(String no){
	String msg="Error UB"+no+"\nRebooting";
	Serial.println(msg);
	display(msg);
	display_loop_force();
	delay(4000);
	reboot();
}
void setup(){
	Serial.begin(115200);
	clock_init();
	events_init();
	adc_init();
	encoder_init();
	display_init();
	logic_init();
}
void reboot(){
	setup();
}
void loop(){
	clock_loop();
	encoder_loop();
	if(main_tick==3){
		events_loop();
	}
	adc_loop();
	logic_loop();
	if(main_tick==3){
		display_loop();
	}
	++main_tick;
	main_tick&=3;
}
