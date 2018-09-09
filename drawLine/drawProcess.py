# encoding=utf-8
from pylab import *
from ctypes import *
import os
import time

# load the shared object file
x = [1, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100]
# x = [1, 10, 20, 30]
y = []
# line = [[1, 10, 100, 1000],
#         [5000, 10000, 50000, 100000],
#         [500000, 1000000, 5000000, 10000000],
#         [50000000, 100000000, 500000000, 1000000000],
#         [1500000000, 2000000000, 3000000000, 4294967296]]

main = "./multisum"

line = [[1, 10, 100, 1000]]

for ll in line:
    for l in ll:
        for v in x:
            f = os.popen(main + " " + str(v) + " " + str(l))
            data = f.readlines()
            f.close()
            print(data)
            y.append(int(data[0]))
            time.sleep(2)

        plt.plot(x, y, mfc='w', label=str(l))
        y.clear()
    plt.legend()
    plt.xlabel('number of process')
    plt.ylabel('time/us')
    plt.title("process")
    plt.show()
