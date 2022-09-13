#10-19-17
#Kevin Andor
#Ch3


def prob1():
    import math
    r = eval(input("Enter radius here:"))
    V = 4/3*math.pi*(r**3)
    A = 4*math.pi*(r**2)
    print("The Volume is {} and the Area is {}".format(V,A))



def prob2():
    import math
    d = eval(input("Enter pizza Diameter:"))
    A = math.pi * (d/2) ** 2
    c = eval(input("Enter your pizza cost:"))
    p = c/A

    print ("The cost per square inch is {}".format(p))


def prob3():
    H = 1.0079
    C = 12.011
    O = 15.9994
    h = eval(input("Enter the amount of H:"))
    c = eval(input("Enter the amount of C:"))
    o = eval(input("Enter the amount of O:"))
    a = (H*h) + (C*c) + (O*o)
    print("The weight is {}".format(a))

def prob4():
    x = eval(input("Enter time in sec between sound and thunder:"))
    s = x*1100
    m = s/5280
    print("The distance is {}".format(m))

def prob5():
    x = eval(input("How many lbs?"))
    a = (10.50 * x) + (.86 * x) + 1.50
    print("The cost is ${}".format(a))




def prob6():
    #This program calculates slope
    x1 = eval(input("Enter x from first coordinate:"))
    y1 = eval(input("Enter y from first coordinate:"))
    x2 = eval(input("Enter x from second coordinate:"))
    y2 = eval(input("Enter y from second coordinate:"))
    s = (y2 - y1)/(x2 - x1)
    print("The slope is {}".format(s))

def prob7():
    import math
    #This program calculate distance
    x1 = eval(input("Enter x from first coordinate:"))
    y1 = eval(input("Enter y from first coordinate:"))
    x2 = eval(input("Enter x from second coordinate:"))
    y2 = eval(input("Enter y from second coordinate:"))
    d = math.sqrt((x2 + x1)**2 + (y2 + y1)**2)
    print("The distance is {}".format(d))


def prob8():
    y = eval(input("Enter a 4-digit year:"))
    C = y // 100
    e = (8+(C//4)- C + ((8*C + 13)//25) + 11*(y%19))%30
    print("The epact is {}".format(e))

def prob9():
    import math
    a, b, c = eval(input("Give me the sides of the triangle:"))
    s = (a+b+c)/2
    A = math.sqrt(s*(s-a)*(s-b)*(s-c))
    print("The area of the triangle is {}".format(A))

def prob10():
    import math
    h = eval(input("Give the height of target:"))
    a = eval(input("Give the angle of the ladder:"))
    r = (math.pi / 180) * a
    l = h / math.sin(r)
    print("The length of the ladder has to be {}".format(l))

def prob11():
    pass

def prob12():
    pass

def prob13():
    pass

def prob14():
    pass

def prob15():
    pass

def prob16():
    pass

def prob17():
    pass

def main():
    #prob1()
    #prob2()
    #prob3()
    #prob4()
    #prob5()
    #prob6()
    #prob7()
    #prob8()
    #prob9()
    prob10()


if __name__=="__main__":
    main()
