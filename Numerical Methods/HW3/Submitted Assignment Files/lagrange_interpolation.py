"""
    Mehmet Ali Balıkçı
    150200059
    
"""
import matplotlib.pyplot as plt
import numpy as np

def plot_quadratic_equation(a, b, c):
    x = np.linspace(-10, 10, 400)  # x değerlerini oluşturuyoruz
    y = a*x**2 + b*x + c  # 2. dereceden denklemin hesaplanan y değerleri

    plt.plot(x, y)  # grafiği çizdirme

    plt.title("2. Dereceden Denklem Grafiği")
    plt.xlabel("x")
    plt.ylabel("y")

    plt.grid(True)  # ızgara çizme
    plt.ylim(-10, 10)  # y eksenini -10 ile 10 arasında ölçekleme

    plt.show()
    


def lagrange_method(x,y):
    print(x,end='\t')
    print(y)
    a = 0 #coefficient of x^2
    b = 0 #coefficient of x
    c = 0 #constant
    
    
    for i in range( len(y) ): # for calculations in sigma symbol 
        sum = 0
        product = 1
        for j in range( len(x) ): # for calculations of some part of pi symbol
            if(j==i): continue
            sum += x[j]     # To calculate the sum of x values between their own such as x1+x2, x1+x0, x0+x2
            product *= x[j] # To calculate the product of x values between their own such as x1*x2, x1*x0, x0*x2
        a = a + ( (y[i]) / ( pow(x[i],2) - ( x[i]*(sum)) + product ) ) # To calculate the coefficient of x^2
        b = b + ( (y[i]) / ( pow(x[i],2) - ( x[i]*(sum)) + product ) * (-sum) ) # To calculate the coefficient of x
        c = c + ( (y[i]) / ( pow(x[i],2) - ( x[i]*(sum)) + product ) * product ) # To calculate the constant value
    print(" P(x) = {}x^2 + {}x + {}".format(a,b,c)) 
    plot_quadratic_equation(a,b,c)
x=[-1.2,0.3,1.1]
y =[-5.76,-5.61,-3.69]

print("------Second Order Lagrange Interpolating Polynomial Calculator------")
print("\n")

# if the user wants to enter x and y values, then he/she can enter by entering number 1
control = int( input("Please type 1 if you want to enter the values or 0 if you do not want: ") )

while(True):
    # if the user entered the values, default x and y values are cleared
    if(control==1):
        x.clear()
        y.clear()
        for i in range(3):
            x_element = int( input("Please enter the {}. x value ".format(i+1) ) )
            y_element = int( input("Please enter the {}. y value ".format(i+1) ) )
            
            x.append(x_element) # a list created with x values
            y.append(y_element) # a list created with y values
        print(x,y)
        break
    elif(control==0):
        break
    print("Wrong entering please try again")
    control = int( input() )            
lagrange_method(x,y)