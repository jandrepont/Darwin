import csv
from decimal import *
from itertools import islice
import glob

real_mean = []
bin_mean = []
files = glob.iglob('../realGA/results/*.csv')
filecount = 0
for filename in files:
    with open(filename) as fin:
        total = 0
        mean = 0
        avg = 0
        n = 0;
        for row in csv.reader(fin, delimiter=','):
            n = n + 1
            total += Decimal(row[1])
        real_mean.append(total / n);
        print(filename),; print("mean = "),; print(real_mean[filecount])
    filecount = filecount + 1;

files = glob.iglob('../binGA/results/*.csv')
filecount = 0
for filename in files:
    with open(filename) as fin:
        total = 0
        mean = 0
        avg = 0
        n = 0;
        for row in csv.reader(fin, delimiter=','):
            n = n + 1
            total += Decimal(row[1])
        bin_mean.append(total / n);
        print(filename),; print("mean = "),; print(bin_mean[filecount])
    filecount = filecount + 1;
# print(bin_mean)

result = 0
for index in range(len(real_mean)):
    result = max(real_mean[index],bin_mean[index]) / min(real_mean[index], bin_mean[index])
    result = result*100
    if real_mean[index] == max(real_mean[index],bin_mean[index]):
        print("Bin has lowest minimum at %f" % (result)),; print("%\smaller than real ")
    else:
        print("Real has lowest minimum at %f" % (result)),; print("%\smaller than bin ")
