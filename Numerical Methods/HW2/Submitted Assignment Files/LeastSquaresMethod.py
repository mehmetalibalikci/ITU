# Mehmet Ali Balikci
# 150200059
import matplotlib.pyplot as plt
from sympy import symbols, Eq, solve
import numpy as np
from scipy.optimize import curve_fit


def linear_fit(x_datas, y_datas):
    sumOfSquares = 0
    sumOfx = 0
    sumOfy = 0
    productOfxy = 0
    for i, x in enumerate(x_datas):
        sumOfSquares += pow(x, 2)
        sumOfx += x
        sumOfy += y_datas[i]
        productOfxy += x * y_datas[i]
    n = len(x_datas)
    A, B = symbols("A B")
    eq1 = Eq(A * sumOfSquares + B * sumOfx, productOfxy)
    eq2 = Eq(A * sumOfx + B * n, sumOfy)

    sol = solve((eq1, eq2), (A, B))
    print("y = {}x + {}".format(sol[A], sol[B]))
    # plotting the linear regression line
    x = np.linspace(min(x_datas), max(x_datas), 100)
    y = sol[A] * x + sol[B]
    plt.plot(x, y, "-r", label="Linear regression")

    # plotting the data points
    plt.plot(x_datas, y_datas, "o", label="Data points")
    plt.legend()
    
def polynomial_fit(x_datas, y_datas):
    sumOfx = 0 
    sumOfy = 0
    sumOfSquares = 0
    sumOfCubes = 0
    sumOfFourthPower = 0
    productOfxy = 0
    productOfysqrx = 0

    for i, x in enumerate(x_datas):
        sumOfx += x
        sumOfy += y_datas[i]
        sumOfSquares += pow(x, 2)
        sumOfCubes += pow(x, 3)
        sumOfFourthPower += pow(x, 4)
        productOfxy += x * y_datas[i]
        productOfysqrx += y_datas[i] * pow(x, 2)

    n = len(x_datas)
    E, D, C = symbols("E D C")
    eq1 = Eq(n * E + D * sumOfx + C * sumOfSquares, sumOfy)
    eq2 = Eq(E * sumOfx + D * sumOfSquares + C * sumOfCubes, productOfxy)
    eq3 = Eq(E * sumOfSquares + D * sumOfCubes + C * sumOfFourthPower, productOfysqrx)
    
    sol = solve((eq1, eq2, eq3), (E, D, C))
    print("y = {}x^2 + {}x + {}".format(sol[C], sol[D], sol[E]))

    # plotting the polynomial regression line
    x = np.linspace(min(x_datas), max(x_datas), 100)
    y = sol[C] * pow(x, 2) + sol[D] * x + sol[E]
    plt.plot(x, y, "-r", label="Polynomial regression")

    # plotting the data points
    plt.plot(x_datas, y_datas, "o", label="Data points")
    plt.legend()
    plt.show()

def logarithmic_fit(x_datas, y_datas):
    def func(x, a, b):
        return a + b * np.log(x)

    popt, _ = curve_fit(func, x_datas, y_datas)
    print("y = {} + {} * log(x)".format(popt[0], popt[1]))
    # plotting the logarithmic regression line
    x = np.linspace(min(x_datas), max(x_datas), 100)
    y = popt[0] + popt[1] * np.log(x)
    plt.plot(x, y, "-r", label="Logarithmic regression")
    # plotting the data points
    plt.plot(x_datas, y_datas, "o", label="Data points")
    plt.legend()
    plt.show()
Xdatas = [
    0.5,1,1.5,2,2.5,3,3.5,4,4.5,5,
    5.5,6,6.5,7,7.5,8,8.5,9,9.5,10,
]
Ydatas = [
    0.72,1.63,1.88,3.39,4.02,3.89,4.25,3.99,4.68,5.03,5.27,
    4.82,5.67,5.95,5.72,6.01,5.5,6.41,5.83,6.33,
]

linear_fit(Xdatas, Ydatas)
#polynomial_fit(Xdatas , Ydatas)
#logarithmic_fit(Xdatas, Ydatas)
