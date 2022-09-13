#Kevin Andor, Cole Stewart, Cole Keffel
#Assignment 8



def main():
    exit_flag = False #Flag for controlled loop
    CS101 = ("3004", "Haynes", "8:00 a.m.") #All course information is stored in tuplets
    CS102 = ("4501", "Alvarado", "9:00 a.m.")
    CS103 = ("6755", "Rich", "10:00 a.m.")
    NT110 = ("1244","Burke", "11:00 a.m.")
    CM241 = ("1411","Lee", "1:00 p.m.")
    SEP = "-----------------------------------------"
    HEADER = ("ID:", "Room:", "Instructor:", "Meeting Time:")
    classes = {"CS101":CS101, "CS102":CS102, "CS103":CS103, "NT110":NT110, "CM241":CM241} #Dictionary with each course id set as a key and a corresponding tuplet as an entry

    while exit_flag == False:
        try:
            key = input("\nPlease enter a Course ID to see it's room number, instructor, and meeting time.\nEnter 'ALL' to see the entire course list.\nEnter 'QUIT' to close the program.\n>>> ")
            if key == "QUIT": #Quits the program
                exit_flag = True

            else: #If 'ALL' is entered, prints all key's and their respective entries. Else, it searches for and prints the entry with the key provided
                print("\n"+HEADER[0], HEADER[1], HEADER[2], HEADER[3], sep="   ")
                print(SEP)
                if key == "ALL":
                    for key in classes:
                        print(key, classes[key])
                    
                else:
                    print(key, classes[key])
                print(SEP)
            
        except: #If an invalid entry is provided, program prints an error message letting the user know
            print("\n**Error: Course ID/Option does not exist**\n")
    return 0

main() #Calls the main function 
