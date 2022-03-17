import requests
ADDR = "http://192.168.0.115/13"

data = []
def loop():
	while True:
		r = requests.get(ADDR)
		data.append(int(r.text))
