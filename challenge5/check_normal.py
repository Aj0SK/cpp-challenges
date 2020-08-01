import numpy as np
from matplotlib import pyplot as plt 

numbers = [float(line.strip()) for line in open("generated.txt", "r")]

best = np.random.normal(0.0, 1.0, len(numbers))
numbers = np.array(numbers)

print(f"Mean: {np.mean(numbers)} vs {np.mean(best)}")
print(f"Standard deviation: {np.std(numbers)} vs {np.std(best)}")

quantiles = np.arange(0.0, 1.0, 0.001)
my_quant = np.quantile(numbers, quantiles)
best_quant = np.quantile(best, quantiles)
plt.scatter(quantiles, my_quant, s = 1.0, marker = "o")
plt.scatter(quantiles, best_quant, s = 1.0, marker = "+")
plt.show()

fig, axs = plt.subplots(2)
fig.suptitle('My normal distribution vs numpy generated')
axs[0].hist(numbers, bins = np.arange(-4, 4, 0.01)) 
axs[1].hist(best, bins = np.arange(-4, 4, 0.01))
plt.show()
