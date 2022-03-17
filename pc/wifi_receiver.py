import requests
ADDR = "http://192.168.0.115/13"
MAX = 4095

data = []
def loop():
	while True:
		r = requests.get(ADDR)
		l = map(int, r.text.strip().split())
		for x in l:
			data.append(x)
