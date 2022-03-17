/*
 * This code can be used for simple reading signal from 34 and writing to serial port
 */
void setup() {
	Serial.begin(115200);
	pinMode(34, INPUT);
}
int val;
void loop() {
	val=analogRead(34);
	Sreial.prinln(val);
	/*
	char a=((val&0b11111)<<1)|1;
	char b=(val&0b1111100000)>>4;
	Serial.print(a);
	Serial.print(b);
	*/
	delay(20);
}
