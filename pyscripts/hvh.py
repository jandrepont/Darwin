import csv
from decimal import *
from itertools import islice
import glob

real_mean = []
localbin16Hybrid = []
globalbin16Hybrid = []
x = 30
files=[]

for index in range(x):
    if(index != 1):
        files.append(('../hybridGA/results/gbin16greal1/hybf%d.csv' % (index+1)))
# print(files)
# files = islice(glob.iglob('../realGA/results/*.csv'),x)
filecount = 0
for filename in files:
    with open(filename) as fin:
        total = 0
        mean = 0
        avg = 0
        n = 0
        for row in csv.reader(fin, delimiter=','):
            # print row[0]
            if int(row[0]) == 2000:
                n = n + 1
                # print float(row[2])
                total += Decimal(row[2])
        localbin16Hybrid.append(total / n);
        print(filename),; print("bin mean = "),; print(localbin16Hybrid[filecount])
    filecount = filecount+1
files[:] = []
for index in range(x):
    if(index != 1):
        files.append(('../hybridGA/results/lbin16greal1/hybf%d.csv' % (index+1)))
filecount = 0
for filename in files:
    with open(filename) as fin:
        total = 0
        mean = 0
        avg = 0
        n = 0;
        for row in csv.reader(fin, delimiter=','):
            if int(row[0]) == 2000:
                n = n + 1
                # print float(row[2])
                total += Decimal(row[2])
        globalbin16Hybrid.append(total / n);
        print(filename),; print("mean = "),; print(globalbin16Hybrid[filecount])
    filecount = filecount+1
result = 0


for index in range(len(globalbin16Hybrid)):
    result = max(globalbin16Hybrid[index],localbin16Hybrid[index]) / min(globalbin16Hybrid[index], localbin16Hybrid[index])
    result = abs((1-result))*100
    if localbin16Hybrid[index] == max(globalbin16Hybrid[index],localbin16Hybrid[index]):
        print("global has lowest minimum for function %d at %f" % (index+1,result)),; print("%\smaller than bin ")
    else:
        print("local has lowest minimum for function: %d at %f" % (index+1, result)),; print("%\smaller than real ")


