import serial
SERIALPORT = "/dev/ttyUSB0"
BAUDRATE = 115200
MAX = 4095

serialPort = serial.Serial(SERIALPORT, BAUDRATE)

data = []
def loop():
	while True:
		if serialPort.in_waiting > 0:
			a = int(serialPort.readline())
			data.append(b)
