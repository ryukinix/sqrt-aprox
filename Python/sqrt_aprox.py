#!/usr/bin/env python3
#coding=utf-8
#fatorial
from functools import reduce
from math import sqrt

f = lambda x: reduce(lambda a,b:a*b, [i for i in range(1, x + 1)] + [1])
#produtorio entre impars na sequencia 1, 1, 3, 5, 7...
p_impar = lambda x: reduce(lambda a, b: a*b, (abs(2*k + 1) for k in range(-1, x-1)))
#aproximação da raiz quadrada usando expansão da série de taylor
expr1 = lambda x, n: float((((-1)**(int(n)+1))*((x - 1)**n)*p_impar(int(n)))/((2.0**n)*f(int(n))))  #preciso revisar, alguma expressão estar errada

sqrt_ = lambda x: 1 + sum([expr1(float(x), float(n)) for n in range(1, 7)]) #funciona que é uma maravilha para o número 2.
i = 2
print("my: √%d = %2.10f" %(i, sqrt_(i)))
print("python: √%d = %2.10f" %(i, sqrt(i)))
print("sqrt - sqrt_ = %2.10f" %(abs(sqrt(i) - sqrt_(i))))