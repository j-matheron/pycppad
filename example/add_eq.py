# python equivalent of the CppAD example https://coin-or.github.io/CppAD/doc/addeq.cpp.htm

from pycppad import AD, Independent, ADFun, Value

# import numpy as np

# domain space vector
n = 1
x0 = 0.5

x = AD(x0)

print(Value(x), type(x))

x = [AD(x0)]


print(" (x[0]) before Independent:", Value(x[0]), type(x[0]))

# declare independent variables and start tape recording
Independent(x)

print(" (x[0]) after Independent:", Value(x[0]), type((x[0])))


# range space vector
m = 2
y = [AD(0.0), AD(0.0)]

y[0] = x[0]
# y[0] = AD(x[0])

# initial value
y[0] += AD(2)
print("Value(y[0]):", Value(y[0]), type((y[0])))
print(" (x[0]) after Independent:", Value(x[0]), type((x[0])))


# AD<double> += int
y[0] += AD(4.0)
print("Value(y[0]):", (Value(y[0]), type((y[0]))))

# AD<double> += double
y[0] += x[0]
print("(y[0]):", (y[0]), type((y[0])))

y[1] = y[0]

print(" Value(y[0]):", Value(y[0]), type((y[0])))
print("expected:", x0 + 2.0 + 4.0 + x0)

print(" Value(y[1]):", Value(y[1]))
print(" Value(x[0]) now:", Value(x[0]))
# use the result of a compound assignment

# create f: x -> y and stop tape recording
f = ADFun(x, y)
# input("raw_input")

# f.optimize("no_compare_op")

# assert Value(y[0]) == x0 + 2.0 + 4.0 + x0
# assert Value(y[1]) == Value(y[0])

dx = [0.0]

dx[0] = 1.0
dy = f.Forward(1, dx)
print("dy from Forward(1, [1.0]):", dy)
# assert len(dy) == m
# assert dy[0] == 2.0
# assert dy[1] == 2.0

# reverse computation of derivative of y[0]
w = [0.0, 0.0]

w[0] = 1.0
w[1] = 0.0
dw = f.Reverse(1, w)
print("dw from Reverse(1, [1.0, 0.0]):", dw)
# assert len(dw) == n
# assert dw[0] == 2.0
