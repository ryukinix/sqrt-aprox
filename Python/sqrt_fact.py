# -*- coding:utf-8 -*-
from functools import * #caso seja python 3.x

def factors(n): #divisores de um um numero
        return sorted(set(reduce(list.__add__, [[i, n//i] for i in range(1, int(n ** 0.5) + 1) if n % i == 0])))

def factored(n): #sua forma fatorada
        f = factors(n)[1:] #sem o 1
        factored_form = []
        for i in f:
                while n % i == 0:
                        n = n // i
                        factored_form.append(i)
        return factored_form
def sqrt_fact(n): #raiz quadrada fatorada
        fact_form = factored(n) #[2, 5, 5]
        productory = lambda nums: reduce(lambda x, y: x*y, nums) 
        sqrt_nums = [x for x in fact_form if fact_form.count(x) % 2 == 0]
        not_sqrt = [x for x in fact_form if x not in sqrt_nums]

        answer = ''
        if len(sqrt_nums) >= 1:
                answer += str(int(productory(sqrt_nums) ** 0.5))
        if len(not_sqrt) >= 1:
                answer += 'V' + str(productory(not_sqrt))
        return answer

entrada = 8
print(sqrt_fact(entrada))
print(factors(entrada))
print(factored(entrada))