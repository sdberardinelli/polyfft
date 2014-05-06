#!/usr/bin/python

import matplotlib.pyplot as plt
import csv
import numpy

f1 = open('raw', 'r')
reader1 = csv.reader(f1, delimiter=',')

coef = []

col1 = []
col2 = []
col3 = []
col4 = []

for row in reader1:
    col1.append(row[0])
    col2.append(row[1])
    col3.append(row[2])
    col4.append(row[3])
    coef.append(row[4])

plt.plot(coef, col1, marker='.', color='b', linestyle='|')
plt.plot(coef, col2, marker='.', color='g', linestyle='|')
plt.plot(coef, col3, marker='.', color='r', linestyle='|')
plt.plot(coef, col4, marker='.', color='y', linestyle='|')
plt.xlabel('number of coefficients')
plt.ylabel('time (seconds) ')

plt.show()
