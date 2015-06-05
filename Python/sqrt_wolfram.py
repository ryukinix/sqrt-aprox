from __future__ import division
from functools import reduce
from math import sqrt
from sys import argv

slices = 7
fat = lambda x: reduce(lambda a, b: a*b, [x for x in range(1, x + 1)] + [1])
#gamma = lambda x: fat(x - 1)
#poch = lambda x, n: gamma(x + n)/gamma(x)

def poch(x, n):
	total = 1
	for k in range(n):
		total *= (x + k)

	return total



def sqrt_(x):
	global parcelas
	total = 0.0
	for k in range(slices):
		signal = (-1) ** k
		exp1 = (-1 + x) ** k
		exp2 = poch((-1/2), k)    #(-1/2)*k
		denominator =  fat(k)
		element = (signal*exp1*exp2)/denominator
		total += element
		print("For {k} -> ({s}*{exp1}*{exp2})/{den} = {e}".format(k = k, \
			s = signal, exp1 = exp1, exp2 = exp2, \
			den = denominator, e = element ))
		print("Total: {t}".format(t = total))
	return total


test = int(2)

aprox = sqrt_(test)
stand = sqrt(test)
error = abs(aprox - stand)
print("Total: {} | Error: {}".format(aprox, error))