# Mehmet Ali Balikci
# 150200059

import math

def function(x):
    return 4 * math.log(x) - x

def derivative_of_function(x):
    return 4 / x - 1

def newton_method(max_iteration, x_0):

    for i in range (max_iteration):
        x_1 =  x_0 - function(x_0) / derivative_of_function(x_0)
        print("X{} = {}, f(X{}) = {}, f'(X{}) = {} ".format(i+1, x_1, i, function(x_0), i, derivative_of_function(x_0)))
        x_0 = x_1
        print("iteration : ",i+1) 
    return x_1

def secant_method(max_iteration,x_0,x_1):

    for i in range (max_iteration):
        x_2 = x_1 - function(x_1) * (x_1 - x_0) / ( function(x_1) - function(x_0) )
        print("X{} = {}, f(X{}) = {}, f'(X{}) = {} ".format(i+2, x_2, i, function(x_0), i+1, function(x_1)))
        print("iteration : ",i+1)
        x_0 = x_1
        x_1 = x_2

    return x_2


control = 1
while(control):
    
    option = input("Please choose which one do you want to do\n1-Newton Method\n2-Secant Method\nIf you want to exit please enter 'E' or 'e' ")
    
    if(option == '1'):
        max_iteration = int(input("Please enter the maximum number of iterations "))
        initial_value_0 = float(input("Enter the initial value for newton method "))
        
        if(not initial_value_0):
            print("initial value cannot be zero. Enter again.")
            
            while(not initial_value_0):
                initial_value_0 = float(input())
        print( newton_method(max_iteration, initial_value_0) )
    
    elif(option == '2'):
        max_iteration = int(input("Please enter the maximum number of iterations "))
        initial_value_0 = float(input("Enter the first initial value for secant method "))
        initial_value_1 = float(input("Enter the second initial value for secant method "))
        
        if(not initial_value_0 or initial_value_1):
            print("initial value cannot be zero. Enter again.")
            
            while(not initial_value_0 or not initial_value_1):
                initial_value_0 = float(input("first initial value : "))
                initial_value_1 = float(input("second initial value : "))
        print( secant_method(max_iteration, initial_value_0, initial_value_1) )
    
    elif(option == 'E' or option == 'e'):
        control = 0
        print("Program was ended")
    
    else:
        print("Wrong input. Please try again.")
        
