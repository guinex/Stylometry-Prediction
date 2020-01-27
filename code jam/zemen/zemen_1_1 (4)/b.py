#!/usr/bin/env python3
from fractions import Fraction as F

INF = 10**9

def solve(test):
    s, n = map(int, input().split())
    pos = 0
    neg = 0
    mul = 1
    neg_max = -INF
    div = 1
    was_zero = False

    for i in range(n):
        op, x = input().split()
        x = int(x)
        if op == '+' and x < 0:
            x *= -1
            op = '-'
        elif op == '-' and x < 0:
            x *= -1
            op = '+'

        if op == '+':
            pos += x
        elif op == '-':
            neg += x
        elif op == '*':
            if x == 0:
                was_zero = True
            else:
                mul *= x
                if x < 0 and x > neg_max:
                    neg_max = x
        elif op == '/':
            div *= x
            if x < 0 and x > neg_max:
                neg_max = x

    res = F(s * mul, div)
    if was_zero:
        res = 0

    if was_zero or neg_max > -INF:
        if mul > 0:
            res += mul * pos
            if neg_max > -INF:
                res += F(mul * -neg, neg_max)
        else:
            res += mul * -neg
            if neg_max > -INF:
                res += F(mul * pos, neg_max)
    else:
        res1 = mul * (pos + F(-neg, div))
        res2 = F(mul * pos + -neg, div)
        res += max(res1, res2)

    print("Case #%d: %d %d" %(test, res.numerator, res.denominator))

tn = int(input())
for i in range(tn):
    solve(i + 1)
