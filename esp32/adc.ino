#include <inttypes.h>
#include <Adafruit_ADS1015.h>
Adafruit_ADS1115 ads(0x48);
void adc_init(){
	ads.begin();
}
double adc_voltage(int channel){
	return (adc_read(channel)*((double)0.1875))/1000;
}
int16_t adc_read(int channel){
	return ads.readADC_SingleEnded(channel);
}
void adc_loop(){
}
