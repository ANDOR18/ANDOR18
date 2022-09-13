#Kevin Andor, Cole Keffel, Cole Stewart
#Assignment 6

add = 0
average = 0
counter = 0

try:
    file = open('numbers.txt', 'r') #opens the file


    for i in file: #loop until end of file
        try:
            counter += 1 
            add += (int)(i)
            print(i)
        
        except:
            print("Invalid number, skipping line\n") #if not a number, skip line

    if counter == 0: #to prevent division by 0
        print("No numbers were found in file")
    else: #computes the average and displays the sum and average
        average = add/counter
        print("Sum is: ",add)
        print("Average is: ", average)

    file.close() #closes the file
except: #displays an error message if no file was found
    print("\"numbers.txt\" not found")