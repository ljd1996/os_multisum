# encoding=utf-8
from pylab import *
from ctypes import *
import os
import time

# load the shared object file
x = [1, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100]
# y = [471279, 4181787, 3811286, 4146658, 3203838, 3151844, 3840470, 3799859, 4074696, 4631552,
#      3313787, 4107712, 1546104, 4108037, 4114415, 1579277, 3344663, 654675, 2890119,
#      3800902, 747826],1000000
# [189723, 2537566, 2568255, 2580373, 2615454, 2404901,
#  2593582, 2522950, 2538797, 2686456, 2515385, 2692933,
#  2571020, 2677001, 2544137, 2521179, 2556274, 2555621,
#  2687415, 2659563, 2625827],10000000
# 5000-265, 402, 834, 626, 1797, 7328, 12151, 12109, 13232, 14370, 15715, 19491, 18984, 21579, 24819, 24741, 20399, 24618, 28314, 32859, 30979
# 10000-740, 1650, 1328, 1239, 6429, 7684, 9336, 9744, 11178, 12913, 15859, 16687, 16534, 20029, 21317, 22534, 24297, 24758, 29103, 27989, 30652
# 50000-1254, 9242, 12495, 14106, 11288, 13948, 11118, 9745, 6484, 5398, 9820, 7697, 3034, 21230, 22981, 24867, 27867, 29772, 29436, 28713, 35005
# 100000-2211, 25077, 16603, 24880, 17037, 16945, 24853, 16280, 20340, 24353, 11997, 16212, 15764, 18673, 23030, 20090, 15833, 16302, 20663, 17368, 19952
# 100000000-1914238, 26236694, 26862767, 32042545, 30577443, 27155919, 26315331, 26807816, 25147203, 26351129, 27457750, 26828400, 25517392, 25949226, 26275380, 29689340, 28416069, 30244449, 26832726, 25917983, 26820809

line = [[5000, 10000, 50000, 100000],
        [1000000, 10000000, 100000000, 4294967296]]

dic = {
    # "5000": [265, 402, 834, 626, 1797, 7328, 12151, 12109, 13232, 14370, 15715,
    #          19491, 18984, 21579, 24819, 24741, 20399, 24618, 28314, 32859, 30979],
    # "10000": [740, 1650, 1328, 1239, 6429, 7684, 9336, 9744, 11178, 12913, 15859,
    #           16687, 16534, 20029, 21317, 22534, 24297, 24758, 29103, 27989, 30652],
    # "50000": [1254, 9242, 12495, 14106, 11288, 13948, 11118, 9745, 6484, 5398, 9820,
    #           7697, 3034, 21230, 22981, 24867, 27867, 29772, 29436, 28713, 35005],
    # "100000": [2211, 25077, 16603, 24880, 17037, 16945, 24853, 16280, 20340, 24353, 11997,
    #            16212, 15764, 18673, 23030, 20090, 15833, 16302, 20663, 17368, 19952],
    # "1000000": [471279, 4181787, 3811286, 4146658, 3203838, 3151844, 3840470, 3799859, 4074696,
    #             4631552, 3313787, 4107712, 1546104, 4108037, 4114415, 1579277, 3344663, 654675,
    #             2890119, 3800902, 747826],
    # "10000000": [189723, 2537566, 2568255, 2580373, 2615454, 2404901,
    #              2593582, 2522950, 2538797, 2686456, 2515385, 2692933,
    #              2571020, 2677001, 2544137, 2521179, 2556274, 2555621,
    #              2687415, 2659563, 2625827],
    # "100000000": [1914238, 26236694, 26862767, 32042545, 30577443, 27155919, 26315331,
    #               26807816, 25147203, 26351129, 27457750, 26828400, 25517392, 25949226,
    #               26275380, 29689340, 28416069, 30244449, 26832726, 25917983, 26820809],
    "4294967296": [81254317, 452096827, ]
}

for key, value in dic.items():
    plt.plot(x, value, mfc='w', label=key)

plt.legend()
plt.xlabel('number of process')
plt.ylabel('time/us')
plt.title("process")
plt.show()