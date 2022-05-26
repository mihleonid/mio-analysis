#define State short
#define MENU_MONITOR 0
#define MENU_METHOD 1
#define MONITOR 2
#define METHOD_WIFI 3
#define METHOD_USB 4
#define METHOD_BLE 5


State logic_curr;
State logic_curr_method;

void logic_init(){
	logic_curr=MENU_MONITOR;
}
void logic_loop(){
	Event e;
	while((e=events_get())!=NONE){
		if(e==WAIT){
			e=CLICK;
		}
		if(logic_curr==MENU_MONITOR){
			if(e==CLICK){
				logic_curr=MONITOR;
				continue;
			}
			if(e==ROT_POS){
				logic_curr=MENU_METHOD;
			}
			if(e==ROT_NEG){
				logic_curr=MENU_METHOD;
			}
		}
		if(logic_curr==MENU_METHOD){
			if(e==CLICK){
				logic_curr=logic_curr_method;
				continue;
			}
			if(e==ROT_POS){
				logic_curr=MENU_MONITOR;
			}
			if(e==ROT_NEG){
				logic_curr=MENU_MONITOR;
			}
		}
	}
}
