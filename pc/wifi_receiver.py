import requests
ADDR = "http://192.168.43.24/13"
MAX = 4095

data = []
def has_time():
	return False
def loop():
	while True:
		r = requests.get(ADDR)
		l = map(int, r.text.strip().split())
		for x in l:
			data.append(x)
