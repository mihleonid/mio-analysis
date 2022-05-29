#define State short
#define MENU_MONITOR	0
#define MENU_METHOD	1
#define MONITOR		2
#define METHOD_WIFI	3
#define METHOD_USB	4
#define METHOD_BLE	5
#define MENU_ECO	6
#define ECO_MODE	7

const int wheelLen=3;
State wheel[wheelLen];
int wheelCurr=0;

const int wheelMethodLen=3;
State wheelMethod[wheelMethodLen];
int wheelMethodCurr=0;

State logic_curr;
State logic_curr_method;

void wheelMethodDec(){
	--wheelMethodCurr;
	if(wheelMethodCurr==-1){
		wheelMethodCurr=wheelMethodLen-1;
	}
	updateWheelMethod();
}
void wheelMethodInc(){
	++wheelMethodCurr;
	if(wheelMethodCurr==wheelMethodLen){
		wheelMethodCurr=0;
	}
	updateWheelMethod();
}
void updateWheelMethod(){
	logic_curr=logic_curr_method=wheelMethod[wheelMethodCurr];
}

void wheelDec(){
	--wheelCurr;
	if(wheelCurr==-1){
		wheelCurr=wheelLen-1;
	}
	updateWheel();
}
void wheelInc(){
	++wheelCurr;
	if(wheelCurr==wheelLen){
		wheelCurr=0;
	}
	updateWheel();
}
void updateWheel(){
	logic_curr=wheel[wheelCurr];
}
void logic_init(){
	wheel[0]=MENU_MONITOR;
	wheel[1]=MENU_METHOD;
	wheel[1]=MENU_ECO;

	wheelMethod[0]=METHOD_USB;
	wheelMethod[1]=METHOD_WIFI;
	wheelMethod[2]=METHOD_BLE;

	wheelCurr=0;
	wheelMethodCurr=0;
	updateWheelMethod();
	updateWheel();
}
void logic_loop(){
	Event e;
	while((e=events_get())!=NONE){
#ifdef DEBUG_SERIAL
		Serial.print("Got: ");
		if(e==CLICK){
			Serial.println("Click");
		}
		if(e==WAIT){
			Serial.println("Wait");
		}
		if(e==ROT_POS){
			Serial.println("Pos");
		}
		if(e==ROT_NEG){
			Serial.println("Neg");
		}
#endif
		switch(logic_curr){
			case MONITOR:
			case MENU_MONITOR:
				switch(e){
					case WAIT:
						if(logic_curr==MONITOR){
							goto end;
						}
					case CLICK:
						toggle(logic_curr, MONITOR, MENU_MONITOR);
						goto end;
					case ROT_POS:
						wheelInc();
						goto end;
					case ROT_NEG:
						wheelDec();
						goto end;
				}
			case MENU_METHOD:
				switch(e){
					case CLICK:
					case WAIT:
						logic_curr=logic_curr_method;
						goto end;
					case ROT_POS:
						wheelInc();
						goto end;
					case ROT_NEG:
						wheelDec();
						goto end;
				}
			case ECO_MODE:
				if(e!=WAIT){
					logic_curr=MENU_ECO;
				}
				goto end;
			case MENU_ECO:
				switch(e){
					case CLICK:
					case WAIT:
						logic_curr=ECO_MODE;
						goto end;
					case ROT_POS:
						wheelInc();
						goto end;
					case ROT_NEG:
						wheelDec();
						goto end;
				}
			case METHOD_USB:
			case METHOD_WIFI:
			case METHOD_BLE:
				switch(e){
					case CLICK:
					case WAIT:
						logic_curr=MENU_METHOD;
						goto end;
					case ROT_POS:
						wheelMethodInc();
						goto end;
					case ROT_NEG:
						wheelMethodDec();
						goto end;
				}
		}
		end:;
	}
	display_set_back(1);
	switch(logic_curr){
		case MONITOR:
			if(display_ready()){
				display(String(adc_voltage(0)));
			}
			break;
		case MENU_MONITOR:
			display("Monitor of\nsignal");
			break;
		case MENU_METHOD:
			display("Select sending\nmethod");
			break;
		case MENU_ECO:
			display("Go to\neco mode");
			break;
		case ECO_MODE:
			display_set_back(0);
			break;
		case METHOD_USB:
			display("Send by\nSerial port");
			break;
		case METHOD_WIFI:
			display("Send by\nWIFI (TCP)");
			break;
		case METHOD_BLE:
			display("Work in progress\nBLE");
			break;
		default:
			display("Error UB0\nRebooting"); //TODO add reboot
	}
	switch(logic_curr_method){
		case METHOD_USB:
			Serial.println("USB");
			break;
		case METHOD_WIFI:
			Serial.println("WIFI");
			break;
		case METHOD_BLE:
			Serial.println("BLE");
			break;
		default:
			display("Error UB1\nRebooting"); //TODO add reboot
	}
}
