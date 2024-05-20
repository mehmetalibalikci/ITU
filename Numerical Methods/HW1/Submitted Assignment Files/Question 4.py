#Mehmet Ali Balıkçı 150200059

def get_input(): #we are getting values from user
    c=float ( input("Please enter the value for a: ") )
    d=float ( input("Please enter the value for e: ") )
    
    # let's define a function to approximate a^1/5 
    # our function will be like that f(x)=x^1/5-a
    
    #And our first closed interval will be one 1 minus integer form of a^0,2
    #and 1 plus integer form of a^0,2 
    
    lower_lim=int( (c**(1/5)-1) )
    upper_lim=int( (c**(1/5)+1) )
    return c,d,lower_lim,upper_lim

def f_function(appValue,aValue): # the f function we defined orally before
    f=pow(appValue,5)-aValue
    return f

def bisection_method(aValue,err,lower,upper): #the function applying bisection method
    print("\nFirst lower and upper limits are [{} , {}]".format(lower,upper))
    while True:
        if( f_function( (lower+upper)/2,aValue ) < 0 ):
            lower=(lower+upper)/2
            print("new lower and upper limits are [ {}, {}]".format(lower,upper))
        else:
            upper=(lower+upper)/2
            print("new lower and upper limits are [ {}, {}]".format(lower,upper))
        if( (upper-lower)/2 <=e):
            print("\nX was found")
            print("lower and upper limits are: [ {}, {}] ".format(lower,upper))
            break
    return (upper+lower)/2

a,e,lower_limit,upper_limit=get_input()

x=bisection_method(a,e,lower_limit,upper_limit)

print("x = ",x)



