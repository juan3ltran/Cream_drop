import pandas as pd
import matplotlib.pyplot as plt
data=pd.read_csv("./data/punto1.dat", sep="\s+",names=["x","y"])
plt.scatter(data.x,data.y)
plt.show()