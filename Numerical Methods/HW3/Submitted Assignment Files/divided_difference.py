"""
    Mehmet Ali Balıkçı
    150200059
    
"""
import matplotlib.pyplot as plt
import numpy as np

def plot_quadratic_equation(coefficients):
    x = np.linspace(-10, 10, 400)  # x değerlerini oluşturuyoruz
    y = coefficients[0] + coefficients[1]*x + coefficients[2]*x*(x-1) + coefficients[3]*x*(x-1)*(x-2)  # 2. dereceden denklemin hesaplanan y değerleri

    plt.plot(x, y)  # grafiği çizdirme

    plt.title("2. Dereceden Denklem Grafiği")
    plt.xlabel("x")
    plt.ylabel("y")

    plt.grid(True)  # ızgara çizme
    plt.ylim(-10, 10)  # y eksenini -10 ile 10 arasında ölçekleme

    plt.show()

def divided_difference(x,y): # The function finding divided difference
    print(x,end='\t')
    print(y)
    if(len(x) == 2):
        difference = (y[1]-y[0]) / (x[1]-x[0])
        print("1. diveded difference ", difference)
    
    result = [] # The list in which kept every number at the end of every step

    counter_y = 1 # a counter created to be used in a for loop
    counter_x = 1 # a counter created to be used in a for loop
    counter_del = -1 # a counter created to be used in a while loop
    counter_divided =1 # a counter created to be printed step numbers
    coefficients=[]
    coefficients.append(y[0])
    
    for i in range( len(y) - counter_y ):
        new = (y[i+1] - y[i]) / (x[i+ counter_x] - x[i])
        #print(new,end = '\n                  ')
        result.append(new)

    new_result = result.copy()
    while( len(y) - counter_y > 1):
        counter_x+=1
        counter_y+=1
        
        print("{}. diveded difference ".format(counter_divided),new_result)
        coefficients.append(new_result[0])
        
        for i in range(len(y) - counter_y):
            new = (new_result[i+1] - new_result[i]) / ( x[i+counter_x] - x[i] )
            result.append(new)
        new_result = result.copy()

        if( len(y) - counter_y <2):
            counter_divided+=1
            print("{}. diveded difference ".format(counter_divided),new_result[-1])
            coefficients.append(new_result[-1])
            
        for i in range( len(y) + counter_del ):
            del new_result[0]
 
        counter_del+=3
        counter_divided+=1
    plot_quadratic_equation(coefficients)
    
    
x=[0,1,2,4,6]
y =[1,9,23,93,259]

# if the user wants to enter x and y values, then he/she can enter by entering a number different from 0 as the number of inputs
# if he does not want, then he can enter 0
number_of_points = int( input("Please type a number different from 0 if you want enter the values or 0 if you do not want: ") )

while(True):


    # if the user entered the values, default x and y values are cleared
    if(number_of_points>0):
        x.clear()
        y.clear()
        for i in range(number_of_points):
            x_element = int( input("Please enter the {}. x value ".format(i+1) ) )
            y_element = int( input("Please enter the {}. y value ".format(i+1) ) )
            
            x.append(x_element) # a list created with x values
            y.append(y_element) # a list created with y values
        print(x,y)
        break
    elif(number_of_points==0):
        break
    else:
        print("Wrong entering please try again")
        number_of_points = int( input() )       

divided_difference(x,y)

