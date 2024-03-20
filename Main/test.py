import pandas as pd
import matplotlib.pyplot as plt
data=pd.read_csv("./datos.dat", sep="\s+",names=["x","y"])
plt.scatter(data.x,data.y)
plt.xlim((-20,20))
plt.ylim((-20,20))
plt.show()
print(data[data.x!=data.y])
