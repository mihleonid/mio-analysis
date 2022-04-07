/*
 * This code can be used for simple reading signal from 34 and writing to serial port fast but with only 10 bits.
 */
void setup() {
	Serial.begin(115200);
	pinMode(34, INPUT);
}
short val;
void loop() {
	val=analogRead(34);
	char a=((val&0b11111)<<1)|1;
	char b=(val&0b1111100000)>>4;
	Serial.print(a);
	Serial.print(b);
}
