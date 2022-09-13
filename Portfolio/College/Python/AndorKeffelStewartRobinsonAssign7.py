#Kevin Andor, Cole Stewart, Cole Keffel, Quanel Robinson
#Assignment 7 CSC308


import random
def main():
    random.seed()
    chips = 100
    exit_flag = False
    bet_count = 0
    selection = 0
    
    SMALL_L = 3 #List size for pick1 and pick2
    BIG_L = 7 #List size for jumbo
    P1 = 1
    P2 = 2
    JMBO = 7
    
    while chips > 0: #Game will end if player's chip count is less than or equal to 0.
        exit_flag = False
        print("----------------------------")
        print("Chips:", chips, "    Bet counter:", bet_count)
        try:
            while exit_flag == False:
                selection = int(input("Choose the game you want to play (enter 1-4):\n" +
                                        "1. Pick 1\n"+
                                        "2. Pick 2\n"+
                                        "3. Jumbo\n"+
                                        "4. Quit\n"+
                                        ">>> "))
                if selection == 1:
                    chips = Game(chips, P1, SMALL_L)
                    exit_flag = True
                    bet_count+=1
                    
                elif selection == 2:
                    chips = Game(chips, P2, SMALL_L)
                    exit_flag = True
                    bet_count+=1

                elif selection == 3:
                    chips = Game(chips, JMBO, BIG_L)
                    exit_flag = True
                    bet_count+=1

                elif selection == 4:
                    print("\nGoodbye!")
                    exit()
                else:
                    print("\nERROR: Invalid selection")
        except:
            print("\nERROR: Invalid selection")

    print("\nGame Over: All out of chips.")
    return 0

#-----------------------------------------------------------------------------------------
#Pick1(): Checks to see if 1 number matched. Takes in the match counter, player's chips, and bet amount. The prize is the bet + their bet back (no matches is a loss). Returns the player's new chip count to Game().
                
def Pick1(chips, match_count, bet):

    if match_count > 0:
        chips += bet*2
        print(match_count, "numbers matched. Gained", bet, "chips!")
    else:
        print("No matches. Lost", bet, "chips.")
        
    return chips


#-----------------------------------------------------------------------------------------
#Pick2(): Checks to see if 2 numbers matched. Takes in the match counter, player's chips, and bet amount. The prize is the bet*2 + their bet back (under 2 matches is a loss). Returns the player's amount of chips to Game().

def Pick2(chips, match_count, bet):

    if match_count > 1:
        chips += bet+(bet*2)
        print(match_count, "numbers matched. Gained", bet*2, "chips!")
    else:
        print(match_count, "matches. Lost", bet, "chips.")
        
    return chips


#-----------------------------------------------------------------------------------------
#Jumbo(): Checks to see if 3+ numbers matched. Takes in the match counter, player's chips, and bet amount. The prize is the bet*matches + their bet back (under 3 matches is a loss). Returns the player's amount of chips to Game().

def Jumbo(chips, match_count, bet):
    
    if match_count > 2:
        chips += bet*match_count
        print(match_count, "numbers matched. Gained", bet*match_count, "chips!")
    else:
        print(match_count, "matches. Lost", bet, "chips.")
        
    return chips

#-----------------------------------------------------------------------------------------
#Game(): Main function where the game is played. Takes in the player's amount of chips, the game mode, and size of the list for the game mode. Returns the player's amount of chips to main().

def Game(chips, pick, listsize):
    i = 0
    match_count = 0
    numList = [0]*listsize

    
    bet = Bet(chips)
    chips = chips - bet
    
    for i in range(listsize):
        numList[i] = random.randrange(0, 9)
    
    inputList = InputNum(pick)    
    match_count = Matching(inputList, numList, pick)

    if pick == 1:
        chips = Pick1(chips, match_count, bet)
    elif pick == 2:
        chips = Pick2(chips, match_count, bet)
    elif pick == 7:
        chips = Jumbo(chips, match_count, bet)

    return chips


#-----------------------------------------------------------------------------------------
#Bet(): Universal bet recording function with error checking for all 3 game modes. Takes in the player's amount of chips and returns the bet amount.

def Bet(chips): 
    bet = 0
    exit_flag = False
    while exit_flag == False:
        try:
            bet = int(input("\nPlease enter the amount of chips you would like to bet:\n>>> "))
            if bet < 1:
                print("You need to at lease bet 1 chip")
            elif bet > chips:
                print("You don't have enough for that bet")
            else:
                exit_flag = True
        except:
            print("Please enter a valid numerical amount")
    return bet

#-----------------------------------------------------------------------------------------
#InputNum(): Universal number input function with exception handling and error checking for all 3 game modes. Takes in the number of values to be picked (as the loop counter) and returns the list of values picked.

def InputNum(pick): 
    i = 0
    inputList = [0]*pick
    exit_flag = False
    while exit_flag == False:
        for i in range(pick):
            try:
                inputList[i] = int(input("\nPlease enter a number (0-9) for pick #"+str(i+1)+":\n>>> "))
                if (inputList[i] < 0)|(inputList[i] > 9):
                    print("\nPlease enter a valid number between 0 and 9")
                else:
                    i+=1
            except:
                print("\nPlease enter a valid number between 0 and 9")
        exit_flag = True
    return inputList

#-----------------------------------------------------------------------------------------
#Matching(): Universal number matching function for all 3 game modes. Takes in the user's list of values, the generated list of values, and the number of values picked (as the loop counter) and returns the amount of values matched.

def Matching(inputList, numList, pick): 
    i = 0
    match_count = 0
    k = 0
    l = 0
    numCount=[0]*10
    
    for k in range(len(numCount)): #Generates a list of how many of each value shows up in numList
        for l in range(len(numList)):
            if numList[l] == k:
                numCount[k] += 1

    for i in range(pick): #Checks for matching numbers. 
        if inputList[i] in numList:
            if numCount[inputList[i]] > 0: #Checks to see if all of a particular value was found, and if not, it increases the match count and decreases the count for that particular value matched.  
                match_count += 1           #Ex: If two 5s were picked by the player but there was only one 5 counted in the generated list, then the second 5 is ignored.
                numCount[inputList[i]] -= 1
                
        
    #print("The number count: ", numCount)    
    print("\nYour number(s) were: ", inputList)
    print("Generated numbers were: ", numList)


    return match_count

#-----------------------------------------------------------------------------------------

main()
