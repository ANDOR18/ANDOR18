#Qr code scanner Alpha v0

def Notqrstuff():
    #This puts the program in an infinite loop:
    run = 1
    while run == 1:
        #This is so we can enter the next while loop:
        bad = 2
        import time
        #Placeholder for Qr value:
        x = input("Enter name here:")

        #Date and time assigned to variables:
        y = time.strftime("%m/%d/%y")
        z = time.strftime("%I:%M:%S")

        #Opens and appends name, date, and time-out to a log:
        log = open("Log_test.txt","a")
        log.write("\n{} | {} | {}".format(x,y,z))

        #Placeholder to show that x is out:
        print ("{} is out.".format(x))

        #This loop is in case of the else statement (shown below):
        while bad == 2:
            #This checks for the same value as initial input:
            same = input("Enter same name here:")

            #If it is:
            if same == x:
                #Write time-in to doc and loop to beginning:
                print("Welcome Back!!")
                z = time.strftime("%I:%M:%S")
                log.write(" | {}".format(z))
                #This will make bad == 2 false, bringing us to the beginning of the program:
                bad = 1

            #If it isn't:
            else:
                    #States that the two names don't match and will loop to bad == 2:
                    print("You are not {}".format(x))







def main():
    Notqrstuff()



if __name__=="__main__":
    main()