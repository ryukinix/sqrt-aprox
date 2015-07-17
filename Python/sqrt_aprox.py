#!/usr/bin/env python3
# coding=utf-8
from __future__ import division
from functools import reduce
from math import sqrt


def factorial(x):
    return reduce(lambda a, b: a*b, [i for i in range(1, x + 1)] + [1])


# productory beteween odd numbers on the sequence: 1, 1, 3, 5, 7...
def p_odd(x):
    return reduce(lambda a, b: a*b, (abs(2*k + 1) for k in range(-1, x-1)))


# aproximation of the square root using the fourier serie expansion
def expr1(x, n):
    numerator = (((-1)**(n + 1))*((x - 1)**n))*p_odd(int(n))
    denominator = (2**n) * factorial(n)
    return numerator/denominator


# pices of the serie
def slices(x):
    return [expr1(x, n) for n in range(1, 7)]


# function aproximation abstraction
def _sqrt(x):
    return 1 + sum(slices(x))


def main():
    test = 2
    # print the slices
    for i in slices(test):
        print(i)

    print("my: √%d = %2.10f" % (test, sqrt_(test)))
    print("python: √%d = %2.10f" % (test, sqrt(test)))
    print("sqrt - sqrt_ = %2.10f" % (abs(sqrt(test) - sqrt_(test))))


if __name__ == '__main__':
    main()