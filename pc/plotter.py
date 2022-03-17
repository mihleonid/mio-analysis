import threading
import os
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

import wifi_receiver as receiver

threading.Thread(target=receiver.loop, daemon=True).start()
def animate(i):
    y_values = receiver.data[-40:]
    x_values = list(range(len(y_values)))
    plt.cla()
    plt.ylim(0, 1024)
    plt.plot(x_values, y_values)
ani = FuncAnimation(plt.gcf(), animate, 1000)
plt.tight_layout()
plt.show()
