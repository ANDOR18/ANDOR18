#Kevin Andor, Cole Keffel, Cole Stewart
#Final Project CSC308
#Space Raiders
import mod.LvMOD #Imports the module containing the different map layouts in the game
import pygame
import mod.GuiMOD
import random
def main():
    gui_quit = False #exit flag
    while gui_quit == False:
        game = 0
        gui = mod.GuiMOD.GUI() #Loads the GUI
        gui.getPlayers() #Allows player names to get added
        gui.closeWindow() #Closes the window
        p1 = gui.player1 #Retrieves player info from appropriate field
        p2 = gui.player2
        mapp = ' '
        lvl = 0
        mapp = gui.getMap() #Retrieves level number from appropriate field


        try:
            lvl = int(mapp) #Attempt to store int into map
            restart = True
        except:
            print("ERROR: Invalid map entry")
            restart = False
            gui_quit = True #Otherwise, quit

        if p1 == "": #If no name is entered
            p1 = "P1"
        if p2 == "":
            p2 = "P2"
        
        if lvl <= 0:
            restart = False
            gui_quit = True
        elif lvl > 3: #If an invalid selection is entered, exit
            lvl = random.randrange(1,3)
        
        while restart == True: #Enters game loop
            game = mod.LvMOD.Level(lvl, p1, p2) #Inits the game (inputs the level number and player names)
            restart = game.start() #If player want to restart current level, returns True, else returns False
            

main() #Calls the main function
