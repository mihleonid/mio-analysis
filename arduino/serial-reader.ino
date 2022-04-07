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
	//delay(20);
}
