#Mehmet Ali Balıkçı 150200059

def convert_float_to_binary(x):
        
    def convert_numerator_to_binary(b):
        a=int(b)
        if(a==0):
            print(a,end="")
        num_part=[]
        while a>0:
            num_part.append( a%2 )
            a//=2
        num_part.reverse()
        return num_part
    
    def fractional_part(e):
        f=e-int(e)
        return f
        
    def print_number(c):
        for i in c:
            print(i,end="")
            
    def convert_denominator_to_binary(numfraction):
        denom_part=[]
        while numfraction>0:
            numfraction=fractional_part(numfraction)
            numfraction*=2
            denom_part.append(int(numfraction))
        return denom_part
    
    part1=convert_numerator_to_binary(x)
    part2=convert_denominator_to_binary(x)
    
    print_number(part1)
    print(".",end="")
    print_number(part2)
    print("")
    
inputValue=1
while inputValue!=0:
    inputValue=float(input("Enter a value to convert to binary  "))
    convert_float_to_binary(inputValue)
            
            
    
        
            
