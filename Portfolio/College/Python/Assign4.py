#Kevin Andor, Cole Keffel, Cole Stewart
#Assignment 4

import random

pos_count = 1 #Counts the amount of possessions
cpu_turn = False #Flag to check for computer's turn

def main():
    global cpu_turn
    global pos_count
    player_score = 0
    computer_score = 0
    START = 20 #Number of yards to start at
    yards = START 
    
    while pos_count < 3: #While player has under 2 full possessions

        print("--------------------------------------------------------------") #Main menu
        print("Player:", player_score, "    Computer:", computer_score, "\nYards:", yards,"\nPossessions:", pos_count,"\n")
        selection = int(input("What would you like to do? (1-4)\n"+
              "1. Run\n"+
              "2. Pass\n"+
              "3. Kick\n"+
              "4. Quit\n"+
              ">>> "))
        if selection == 1: #Run
            yards = Run(yards)
        elif selection == 2: #Pass
            yards = Pass(yards)
        elif selection == 3: #Kick
            if(yards < 50): #If the player hasn't hit at least 50 yards, don't allow a kick. Otherwise, allows a kick for a field goal and resets yards to the starting amount
                print("\nYou need to be at least 50 or more yards toward the field goal.\n")
            else:
                player_score = Kick(yards)
                yards = START
        elif selection == 4: #Quit
            Quit()
        else: #If the user doesn't enter a valid number, print error message
            print("\nInvalid selection, please choose a valid option numbered 1-4.\n")

        player_score += GoalCheck(yards) #At the end of each action, check to see if number of yards is >= 80 for a touchdown
        if cpu_turn == True: #Checks to see if it's the cpu's turn and resets the yards to the starting amount
            computer_score = ComputerTurn()
            yards = START

    if pos_count == 3: #After 2 full possessions, checks to see who won
        print("--------------------------------------------------------------")
        print("Player:", player_score, "\nComputer:", computer_score,"\n")
        if player_score > computer_score:
            print("Player Wins!")
        elif player_score < computer_score:
            print("Computer Wins!")
        else:
            print("It's a tie!")

    return 0
            
    
def Run(yards): #Allows the player to gain a small amount of yards
    run_flag = True #Flag that keeps the user in the selection loop until a valid value is checked
    gained_yards = 0
    while run_flag == True: #Run Menu
        selection = int(input("\nWhat kind of run? (1-2)\n"+
                              "1. Conservative\n"+
                              "2. Risky\n"+
                              ">>> "))
        if selection == 1: #conservative play
            gained_yards = random.randrange(0,4)
            yards += gained_yards
            print("\nGained", gained_yards,"yard(s)\n")
            run_flag = False
            
        elif selection == 2: #risky play
            if random.randint(1,100) < 70: #30% chance to lose yards
                gained_yards = random.randrange(-6, -1)
                yards += gained_yards
                print("\nLost", gained_yards,"yard(s)\n")
            else: #70% chance to gain more yards
                gained_yards = random.randrange(6, 9)
                yards += gained_yards
                print("\nGained", gained_yards,"yard(s)\n")
            run_flag = False
        else:
            print("\nInvalid selection, please choose a valid option numbered 1 or 2.\n")

    return yards

def Pass(yards): #Allows the player to gain a larger amount of yards with the risk of dropping the ball
    pass_flag = True
    gained_yards = 0
    while pass_flag == True:
        selection = int(input("\nWhat kind of pass? (1-2)\n"+
                              "1. Short\n"+
                              "2. Long\n"+
                              ">>> "))
        if selection == 1: #short pass
            if random.randint(1,100) < 50: #50% chance to gain no yards
                print("\nShort pass failed, gained no yards\n")
                pass_flag = False
            else:
                gained_yards = random.randrange(9,12)
                yards += gained_yards
                print("\nShort pass successful, gained", gained_yards, "yard(s)\n")
                pass_flag = False
            
        elif selection == 2: #long pass
            if random.randint(1,100) < 70: #70% chance to gain no yards
                print("\nLong pass failed, gained no yards\n")
                pass_flag = False
            else:
                gained_yards = random.randrange(13,16)
                yards += gained_yards
                print("\nLong pass successful, gained", gained_yards, "yard(s)\n")
                pass_flag = False
        else:
            print("\nInvalid selection, please choose a valid option numbered 1 or 2.\n")

    return yards

def Kick(yards): #Allows the player to gain pints for a field goal
    global cpu_turn
    score = 0
    cpu_turn = True
    if random.randint(1, 100) > (2*(80-yards)): #If condition achieved, obtain field goal
        print("\nField goal!! Gained 3 Points!\n")
        score = 3
    else:
        print("\nField goal failed. Gained no points.\n") #Gain no points
        score = 0
    return score
    
def ComputerTurn(): #Randomizes how many points the computer scores and increments the possession counter by 1
    global pos_count
    global cpu_turn
    
    score = random.randrange(0, 7, 3)
    if score == 6:
	    score += 1
    cpu_turn = False
    pos_count += 1
    print("\nComputer gained", score, "points.\n")
    return score

def GoalCheck(yards): #Checks if the user reached 80 yards for a touchdown
    global cpu_turn 
    score = 0
    if yards >= 80:
        print("\nTouchdown!! Gained 7 Points!\n")
        cpu_turn = True
        score = 7
    return score
    
    
def Quit(): #Wishes the player goodbye and exits the program
    print("\nGoodbye")
    exit()


main() #Calls the main function
