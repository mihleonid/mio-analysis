#include "inttypes.h"
#include "time.h"

long clock_start;

void clock_init(){
	clock_start=clock();
}
void clock_loop(){
}
long clock_get(){
	return clock()-clock_start;
}
long clock_secs(){
	return clock_get()/CLOCKS_PER_SEC;
}
