import csv
from decimal import *

lbin_mean = []
gbin_mean = []
x = 2
files=[]

for index in range(x):
    if(index != 1):
        files.append(('../../results/gm16/binf%d.csv' % (index+1)))
# print(files)
# files = islice(glob.iglob('../realGA/results/*.csv'),x)
filecount = 0
for filename in files:
    with open(filename) as fin:
        total = 0
        mean = 0
        avg = 0
        n = 0
        findMin = []
        for row in csv.reader(fin, delimiter=','):
            # print row[0]
            if int(row[0]) == 2000:
                # n = n + 1
                # print float(row[2])
                # total += Decimal(row[2])
                findMin.append(row[2])
            # gbin_mean.append(total / n);
        sol = min(findMin)
        print(sol)
        # print(filename),; print("bin1 mean = "),; print(gbin_mean[filecount])
    filecount = filecount+1
files[:] = []
# for index in range(x):
#     if(index != 1):
#         files.append(('../../results/lm16/binf%d.csv' % (index+1)))
# # print(files)
# # files = islice(glob.iglob('../realGA/results/*.csv'),x)
# filecount = 0
# for filename in files:
#     with open(filename) as fin:
#         total = 0
#         mean = 0
#         avg = 0
#         n = 0
#         for row in csv.reader(fin, delimiter=','):
#             # print row[0]
#             if int(row[0]) == 2000:
#                 n = n + 1
#                 # print float(row[2])
#                 total += Decimal(row[2])
#         lbin_mean.append(total / n);
#         print(filename),; print("bin1 mean = "),; print(lbin_mean[filecount])
#     filecount = filecount+1
# files[:] = []
# for index in range(x):
#     if(index != 1):
#         files.append(('../../results/mute3/binf%d.csv' % (index+1)))
# # print(files)
# # files = islice(glob.iglob('../binGA/results/*.csv'),x)
# filecount = 0
# for filename in files:
#     with open(filename) as fin:
#         total = 0
#         mean = 0
#         avg = 0
#         n = 0;
#         for row in csv.reader(fin, delimiter=','):
#             n = n + 1
#             total += Decimal(row[1])
#         bin3_mean.append(total / n);
#         print(filename),; print("mean = "),; print(bin3_mean[filecount])
#     filecount = filecount+1
# # print(bin_mean)
# for index in range(len(gbin_mean)):
#     result = max(gbin_mean[index],lbin_mean[index]) / min(gbin_mean[index], lbin_mean[index])
#     result = abs((1-result))*100
#     if gbin_mean[index] == max(gbin_mean[index],lbin_mean[index]):
#         print("local has lowest minimum at %f" % (result)),; print("%\smaller than global ")
#     else:
#         print("global has lowest minimum at %f" % (result)),; print("%\smaller than local ")
