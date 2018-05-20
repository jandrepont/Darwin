import csv
from decimal import *
from itertools import islice
import glob

real_mean = []
bin_mean = []
hyb_mean = []
x = 30
files=[]

for index in range(x):
    if(index != 1):
        files.append(('../realGA/results/realf%d.csv' % (index+1)))
# print(files)
# files = islice(glob.iglob('../realGA/results/*.csv'),x)
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
    filecount = filecount+1
files[:] = []
for index in range(x):
    if(index != 1):
        files.append(('../binGA/results/binf%d.csv' % (index+1)))
# print(files)
# files = islice(glob.iglob('../binGA/results/*.csv'),x)
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
    filecount = filecount+1
# print(bin_mean)
files[:] = []
for index in range(x):
    if(index != 1):
        files.append(('../hybridGA/results/hybf%d.csv' % (index+1)))
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
        hyb_mean.append(total / n);
        print(filename),; print("mean = "),; print(hyb_mean[filecount])
    filecount = filecount+1
result = 0


for index in range(len(real_mean)):
    result = max(real_mean[index],bin_mean[index]) / min(real_mean[index], bin_mean[index])
    result = abs((1-result))*100
    # if bin_mean[index] == max(real_mean[index],bin_mean[index]):
    #     print("Real has lowest minimum at %f" % (result)),; print("%\smaller than bin ")
    # else:
    #     print("Bin has lowest minimum at %f" % (result)),; print("%\smaller than real ")
    # print "including the hybrid GA: "
    result = min(real_mean[index],bin_mean[index]) / min(real_mean[index], bin_mean[index],hyb_mean[index])
    result = abs((1-result))*100
    if hyb_mean[index] == min(real_mean[index], bin_mean[index],hyb_mean[index]):
        print("Hybrid is new lowest function %d at %f" % (index+1,result)),; print("%\smaller than previous optimum")
    else:
        print("no improvement for function %d" %(index+1))
