import threading
import os
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

import wifi_time_receiver as receiver

threading.Thread(target=receiver.loop, daemon=True).start()
def animate(i):
	y_values = receiver.data[-40:]
	x_values = list(range(len(y_values)))
	if receiver.has_time():
		x_values=receiver.data_time[-40:]
	plt.cla()
	plt.ylim(0, receiver.MAX)
	plt.xlabel('Time');
	plt.ylabel("Volts ({:0.5f})".format(1/receiver.MAX));
	plt.plot(x_values, y_values)
ani = FuncAnimation(plt.gcf(), animate, 1000)
plt.tight_layout()
plt.show()
