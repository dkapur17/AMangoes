import numpy as np
import math
import matplotlib.pyplot as plt

f = lambda x: math.sqrt(
    (0.5 * 0.5) * ((0.60 * 0.60) - (x * x)) / (0.60 * 0.60)) + 0.5

X = np.linspace(-0.6, 0.6, num=21)
Y = []
for x in X:
    y = -f(x)
    Y.append(y)
    print(f"{x:.2f}, {y:.2f},")

plt.plot(X, Y)
plt.show()
