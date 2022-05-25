#define EVENTS_MAX 100
#define WAIT_SECS 3
enum class Event{
	NONE,
	ROT_POS,//rotation
	ROT_NEG,
	CLICK,
	WAIT,
};

Event event_arr[EVENTS_MAX];
int event_start=0;
int event_end=0;
long event_last_push=0;

void events_init(){
	event_last_push=clock_secs();
}
void events_loop(){
	if(event_last_push+WAIT_SECS<clock_secs()){
		events_push(Event::WAIT);
	}
}
void events_push(Event e){
	event_last_push=clock_secs();
	event_arr[event_end]=e;
	++event_end;
	if(event_end==EVENTS_MAX){
		event_end=0;
	}
}
Event events_get(){
	if(event_start==event_end){
		return Event::NONE;
	}else{
		Event e=event_arr[event_start];
		++event_start;
		if(event_end==EVENTS_MAX){
			event_end=0;
		}
		return e;
	}
}
