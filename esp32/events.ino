#define EVENTS_MAX 100
#define WAIT_SECS 3

#define Event short
#define NONE 0
//rotation
#define ROT_POS 1
#define ROT_NEG 2
#define CLICK 3
#define WAIT 4

Event event_arr[EVENTS_MAX];
int event_start=0;
int event_end=0;
long event_last_push=0;

void events_init(){
	event_last_push=clock_secs();
}
void events_loop(){
	if(event_last_push+WAIT_SECS<clock_secs()){
		events_push(WAIT);
	}
}
void events_push(Event e){
	Serial.println("Push");
	if(e==CLICK){
		Serial.println("Click");
	}
	if(e==WAIT){
		Serial.println("Wait");
		e=CLICK;
	}
	if(e==ROT_POS){
		Serial.println("Pos");
	}
	if(e==ROT_NEG){
		Serial.println("Neg");
	}
	event_last_push=clock_secs();
	event_arr[event_end]=e;
	++event_end;
	if(event_end==EVENTS_MAX){
		event_end=0;
	}
}
Event events_get(){
	if(event_start==event_end){
		return NONE;
	}else{
		Event e=event_arr[event_start];
		++event_start;
		if(event_start==EVENTS_MAX){
			event_start=0;
		}
		return e;
	}
}
