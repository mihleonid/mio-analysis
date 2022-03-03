/*
 * This code can be used for simple reading signal from A0 and writing to serial port
 */
void setup() {
	Serial.begin(9600);
}
void loop() {
	short val=analogRead(A0);
	char a=((val&0b11111)<<1)|1;
	char b=(val&0b1111100000)>>4;
	Serial.print(a);
	Serial.print(b);
	delay(20);
}
