import matplotlib.pyplot as plt

def readfile(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()
    return [float(line.split()[0]) for line in lines], [float(line.split()[1]) for line in lines]


t, rms = readfile('a.txt')

plt.loglog(t, rms, marker='*', label='Random Walk Performed', color="#000")
plt.xlabel('t')
plt.ylabel('Drop Size')
plt.title('Drop Size vs time')

plt.legend()
plt.savefig('rw.pdf', format='pdf')
plt.show()
