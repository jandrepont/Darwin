import csv
from decimal import *

bin_mean = []
bin3_mean = []
x = 30
files=[]

for index in range(x):
    if(index != 1):
        files.append(('../gmem16/binf%d.csv' % (index+1)))
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
            if int(row[0]) == 2000:
                n = n + 1
                total += Decimal(row[2])
        bin_mean.append(total / n)
        # print(filename),; print("bin1 mean = "),; print(bin_mean[filecount])
    filecount = filecount+1
files[:] = []
for index in range(x):
    if(index != 1):
        files.append(('../gm16/binf%d.csv' % (index+1)))
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
                total += Decimal(row[2])
        bin3_mean.append(total / n);
        # print(filename),; print("mean = "),; print(bin3_mean[filecount])
    filecount = filecount+1
# print(bin_mean)
files[:] = []

for index in range(len(bin_mean)):
    result = max(bin_mean[index],bin3_mean[index]) / min(bin_mean[index], bin3_mean[index])
    result = abs((1-result))*100
    if bin3_mean[index] == max(bin3_mean[index],bin_mean[index]):
        print("%f," % (result)),;# print("%\smaller than gmem2 ")
    else:
        print("%f," % (result)),; #print("%\smaller than gmem ")
    # print "including the hybrid GA: "
