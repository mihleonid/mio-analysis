import serial
SERIALPORT = "/dev/ttyUSB0"
BAUDRATE = 115200

serialPort = serial.Serial(SERIALPORT, BAUDRATE)

data = []
def loop():
	while True:
		if serialPort.in_waiting > 0:
			a = int.from_bytes(serialPort.read(), 'big')
			b = int.from_bytes(serialPort.read(), 'big')
			if b&1:
				[a, b] = [b, a];
			a = a // 2;
			b = b * 2**4 + a;
			data.append(b)
