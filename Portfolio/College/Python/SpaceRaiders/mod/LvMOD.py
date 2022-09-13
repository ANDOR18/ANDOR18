import pygame
import mod.PlrMOD #Imports the module containing player-related classes
import mod.ScrMOD #Imports the module containing display-related classes
import mod.LvObjMOD #Imports the module containing Level object classes, such as hazards and walls
import mod.SprMOD #Imports the module containing sprites and their attributes
#LvMOD.py
#Where the main game loop occurs. Contains all the level layouts and inits all the objects.

class Level:
    def __init__(self, lvlnum, p1_name, p2_name): #Takes the level selection as input and selects the desired level layout. Also takes player names in.
        super().__init__()
        pygame.init()
        self.lvlnum = lvlnum
        self.screen = mod.ScrMOD.Screen(self.lvlnum) #Inits the display screen
        
        self.Player_1 = mod.PlrMOD.Player(p1_name) #Inits player 1
        self.Player_2 = mod.PlrMOD.Player(p2_name) #Inits player 2
        self.Player_1.init_player(1) #Inits player 1 specific data
        self.Player_2.init_player(2) #Inits player 2 specific data

        self.WallList = [0] * 6 #creates list for all walls based on wall amount constant
        self.TeleporterList = [0] * 8

        self.clock = pygame.time.Clock() #Used for managing how fast the screen updates
        self.done = False #Flag for closing the game (if user presses X)
        self.Player_1.send_screen(self.screen.get_size())
        self.Player_2.send_screen(self.screen.get_size())
        self.P1_list = self.Player_1.get_player() #Retrieves player sprite and rectangle positions and puts them in a list
        self.P2_list = self.Player_2.get_player()
        self.beam_info = [0]*5
        self.beam = 0
        self.smast_opened = 0

        self.i = 0 #Loop counter for big asteroids
        self.j = 0 #Loop counter for small asteroids
        self.k = 0 #Loop counter for small asteroids within big asteroid loop
        
        self.ast_list = [0]*3 #Inits the list of info for big asteroids
        self.ast = [0]*3 #Inits the list of asteroids
        self.smast_list = [0]*6 #Inits the list of info for small asteroids
        self.smast = [0]*6 #Inits the list of small asteroids
        self.smast_filled = 0 #Inits the count of filled small asteroid slots
        self.smast_empty = 0 #Inits the count of empty small asteroid slots
        self.ast_respawn_max = 150 #Max repawn time of a big asteroid
        self.ast_respawn_count = [0]*3 #Inits the list of each big asteroids respawn count
        self.winner = [0]*2
        
    def start(self): #Selects a level based on the number that was sent to the constructor.
        if self.lvlnum == 1:
            option = self.Lvl_1()
        elif self.lvlnum == 2:
            option = self.Lvl_2()
        elif self.lvlnum == 3:
            option = self.Lvl_3()
        return option #Returns the player's decision to restart the game or quit

    def Lvl_1(self): #Asteroids level

        self.Player_1.set_respawnTime(500) #Sets respawn time for the player
        self.Player_2.set_respawnTime(500)
        
        while self.i < 3: #Creates three asteroids and grabs their info
            self.ast[self.i] = mod.LvObjMOD.Asteroid(self.screen.get_size(), self.P1_list, self.P2_list)
            self.ast_list[self.i] = self.ast[self.i].get_ast()
            self.i += 1
        
    #Game Loop
        while not self.done:
            # Event loop
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.done = True #Sets flag for quitting the game
         
        #Game logic

            #Movement
            self.Player_1.movement()#Player 1 movement function
            self.Player_2.movement()#Player 2 movement function

            self.P1_Laser = self.Player_1.shoot_laser(self.TeleporterList)#Checks to see if player shoots this frame
            self.P2_Laser = self.Player_2.shoot_laser(self.TeleporterList)

            self.i = 0
            self.j = 0
            while self.i < 3: #Moves every big asteroid
                if self.ast_list[self.i] != 0:
                    self.ast[self.i].movement()
                self.i += 1
                    
            while self.j < 6: #Moves every small asteroid
                if self.smast_list[self.j] != 0:
                    self.smast[self.j].movement()
                    
                if self.smast_list[self.j+1] != 0:
                    self.smast[self.j+1].movement()
                self.j += 2
                        
                    
        #Screen wrapping
            self.Player_1.screen_wrap() #Screen Wrapping for P1
            self.Player_2.screen_wrap() #Screen wrapping for P2
            
            self.i = 0
            self.j = 0
            while self.i < 3: #Screen wrapping for each big asteroid
                if self.ast_list[self.i] != 0:
                    self.ast[self.i].screen_wrap()
                self.i += 1
                    
            while self.j < 6: #Screen wrapping for each small asteroid
                if self.smast_list[self.j] != 0 and self.smast_list[self.j] != -1:
                    self.smast[self.j].screen_wrap()
                if self.smast_list[self.j+1] != 0 and self.smast_list[self.j+1] != -1:
                    self.smast[self.j+1].screen_wrap()
                self.j += 2
            
        #Screen-clearing + Drawing
            if self.Player_1.checkHit(self.P2_Laser, False): #Checks to see if a player collided with a hazardous object
                self.P2_Laser = self.Player_2.destroy_laser() #Destroy the incoming laser if so
                
            if self.Player_2.checkHit(self.P1_Laser, False):
                self.P1_Laser = self.Player_1.destroy_laser()            
            

            self.i = 0
            self.j = 0
            self.k = 0
            self.smast_filled = 0
                
            while self.i < 3:
                  
                if self.ast_list[self.i] != 0: 
                    self.Player_1.checkHit(self.ast_list[self.i], False) #Checks to see if player got hit by an asteroid
                    self.Player_2.checkHit(self.ast_list[self.i], False)
                    
                    P1_ast = self.ast[self.i].hit(self.P1_Laser) #Checks to see if a big asteroid got hit by an enemy laser
                    P2_ast = self.ast[self.i].hit(self.P2_Laser)
                    
                    if P1_ast or P2_ast: #If a big asteroid is destroyed, create two smaller asteroids and destroy the big asteroid
                        while self.k < 6:
                            if self.smast[self.k] == 0 and self.smast_list[self.k] == 0 and self.smast_filled < 2:
                                self.smast[self.k] = mod.LvObjMOD.sm_Asteroid(self.screen.get_size(), self.ast_list[self.i][1], self.ast_list[self.i][2])
                                self.smast_list[self.k] = self.smast[self.k].get_ast()
                                self.smast_filled += 1

                            if self.smast_filled >= 2:
                                self.k = 7
                            else:
                                self.k += 1
                            
                        self.ast[self.i] = 0
                        self.ast_list[self.i] = 0
                            
                        if P1_ast: #If the asteroid is hit by a laser, destroy the laser
                            self.P1_Laser = self.Player_1.destroy_laser()
                        elif P2_ast:
                            self.P2_Laser = self.Player_2.destroy_laser()
                self.i += 1

            while self.j < 6: #Checks to see if a small asteroid got hit by a laser
                if self.smast_list[self.j] != 0:
                    self.Player_1.checkHit(self.smast_list[self.j], False)
                    self.Player_2.checkHit(self.smast_list[self.j], False)
                        
                    if self.smast[self.j].hit(self.P1_Laser): #If hit, destroy the asteroid, and count the amount of empty slots
                        self.smast[self.j] = 0 
                        self.smast_list[self.j] = 0
                        self.P1_Laser = self.Player_1.destroy_laser()
                        self.smast_empty += 1
                            
                    elif self.smast[self.j].hit(self.P2_Laser):
                        self.smast[self.j] = 0
                        self.smast_list[self.j] = 0
                        self.P2_Laser = self.Player_2.destroy_laser()
                        self.smast_empty += 1
                            
                self.j += 1


            self.i = 0
            while self.i < 3: 
                if self.smast_empty >= 2 and self.ast_list[self.i] == 0: #Checks to see if there are two missing small asteroids and 1 big asteroid 
                    self.smast_empty -= 2 #If so, count down empty slots and activate the respawn count for that asteroid
                    self.ast_respawn_count[self.i] += 1
                        
                elif self.ast_respawn_count[self.i] > 0 and self.ast_respawn_count[self.i] < self.ast_respawn_max and self.ast_list[self.i] == 0: #If the asteroid respawn count has been activated, the regen count is less then the max time,
                                                                                                                #and the current asteroid slot is empty, then increment the respawn count by 1
                    self.ast_respawn_count[self.i] += 1
                        
                elif self.ast_respawn_count[self.i] == self.ast_respawn_max and self.ast_list[self.i] == 0: #If the respan count reaches the limit and the current asteroid slot is empty, create a new asteroid and reset the count for that asteroid to 0
                    self.ast[self.i] = mod.LvObjMOD.Asteroid(self.screen.get_size(), self.P1_list, self.P2_list)
                    self.ast_list[self.i] = self.ast[self.i].get_ast()
                    self.ast_respawn_count[self.i] = 0

                self.i += 1

            self.winner[0] = self.Player_1.win_game(self.Player_2.game_over()) #Checks to see if either player loses, which then triggers either player's win function
            self.winner[1] = self.Player_2.win_game(self.Player_1.game_over())
            
            self.P1_list = self.Player_1.get_player() #Retrieves player sprite and rectangle positions and puts them in a list
            self.P2_list = self.Player_2.get_player()


            self.i = 0
            self.j = 0
            while self.i < 3: #Grabs info about the big asteroids for updating the screen 
                if self.ast_list[self.i] != 0:
                    self.ast_list[self.i] = self.ast[self.i].get_ast()
                self.i += 1
                    
            while self.j < 6: #Grabs info about the small asteroids for updating the screen
                if self.smast_list[self.j] != 0:
                    self.smast_list[self.j] = self.smast[self.j].get_ast()
                if self.smast_list[self.j+1] != 0:
                    self.smast_list[self.j+1] = self.smast[self.j+1].get_ast()
                self.j += 2
           
            self.screen.update(self.P1_list, self.P2_list, self.P1_Laser, self.P2_Laser, self.WallList, self.ast_list, self.smast_list, self.beam_info, self.winner, self.TeleporterList) #Updates each object's position on the screen
            
            if self.winner[0] or self.winner[1]: #Checks if either player wins the game or not. If so, calls a function that allows the player to hit a key to restart or quit the game
                option = self.restart_quit()
                if option != None:
                    pygame.display.quit()
                    return option
                
            self.clock.tick(60) #Limits game to 60 FPS
        pygame.quit() #Closes the window and quits the game

    def Lvl_2(self): #Teleporter level
        
        self.Player_1.set_respawnTime(150)
        self.Player_2.set_respawnTime(150)


        #This code initializes the walls
        #middle walls
        self.WallList[0] = mod.LvObjMOD.Wall(550, 0, 50, 650, True, self.screen)
        self.WallList[1] = mod.LvObjMOD.Wall(0, 300, 1200, 50, False, self.screen)
        #top and bottom
        self.WallList[2] = mod.LvObjMOD.Wall(0, 0, 1200, 50, False, self.screen)
        self.WallList[3] = mod.LvObjMOD.Wall(0, 600, 1200, 50, False, self.screen)
        #left and right
        self.WallList[4] = mod.LvObjMOD.Wall(0, 0, 50, 650, True, self.screen)
        self.WallList[5] = mod.LvObjMOD.Wall(1104, 0, 50, 650, True, self.screen)

        #This code initializes the teleporters
        self.TeleporterList[0] = mod.LvObjMOD.Teleporter(1, 1, (50, 50))
        self.TeleporterList[1] = mod.LvObjMOD.Teleporter(4, 2, (600, 350))
        self.TeleporterList[2] = mod.LvObjMOD.Teleporter(2, 3, (600, 50))
        self.TeleporterList[3] = mod.LvObjMOD.Teleporter(1, 4, (1040, 350))
        self.TeleporterList[4] = mod.LvObjMOD.Teleporter(2, 5, (486, 350))
        self.TeleporterList[5] = mod.LvObjMOD.Teleporter(4, 6, (1040, 50))
        self.TeleporterList[6] = mod.LvObjMOD.Teleporter(3, 7, (486, 50))
        self.TeleporterList[7] = mod.LvObjMOD.Teleporter(3, 8, (50, 350))
        
    #Game Loop
        while not self.done:
            # Event loop
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.done = True #Sets flag for quitting the game
         
        #Game logic
                                 
            #Movement
            self.Player_1.movement()#Player 1 movement function
            self.Player_2.movement()#Player 2 movement function

            self.P1_Laser = self.Player_1.shoot_laser(self.TeleporterList)#Checks to see if player shoots this frame. TeleporterList gets sent to see if the shot laser makes contact with a teleporter.
            self.P2_Laser =self. Player_2.shoot_laser(self.TeleporterList)

        #Screen wrapping + Teleporting
            self.Player_1.screen_wrap() #Screen Wrapping for P1
            self.Player_2.screen_wrap() #Screen wrapping for P2
            
            self.Player_1.checkTeleportCollision(self.TeleporterList) #Checks to see if player made contact with a teleporter
            self.Player_2.checkTeleportCollision(self.TeleporterList)

        #Screen-clearing + Drawing
            self.Player_1.checkCollision(self.WallList) #Checks to see if player collided with a wall
            self.Player_2.checkCollision(self.WallList)

            if self.Player_1.checkHit(self.P2_Laser, False): #Checks to see if a player collided with a hazardous object
                self.P2_Laser = self.Player_2.destroy_laser() #Destroy the incoming laser if so
                
            if self.Player_2.checkHit(self.P1_Laser, False):
                self.P1_Laser = self.Player_1.destroy_laser()

            if self.Player_1.checkLaserCollision(self.WallList): #Checks to see if a player's laser collided with a wall
                self.P1_Laser = self.Player_1.destroy_laser() #Destroy's the laser if so
                
            if self.Player_2.checkLaserCollision(self.WallList):
                self.P2_Laser = self.Player_2.destroy_laser()



            self.winner[0] = self.Player_1.win_game(self.Player_2.game_over()) #Checks to see if either player loses, which then triggers either player's win function
            self.winner[1] = self.Player_2.win_game(self.Player_1.game_over())
                
            self.P1_list = self.Player_1.get_player() #Retrieves player sprite and rectangle positions and puts them in a list
            self.P2_list = self.Player_2.get_player()
           
            self.screen.update(self.P1_list, self.P2_list, self.P1_Laser, self.P2_Laser, self.WallList, self.ast_list, self.smast_list, self.beam_info, self.winner, self.TeleporterList) #Updates each object's position on the screen
            
            if self.winner[0] or self.winner[1]:
                option = self.restart_quit()
                if option != None:
                    pygame.display.quit()
                    return option
                
            self.clock.tick(60) #Limits game to 60 FPS
        pygame.quit() #Closes the window and quits the game  

    def Lvl_3(self): #Satellite level
        
        self.Player_1.set_respawnTime(300)
        self.Player_2.set_respawnTime(300)

        self.beam = mod.LvObjMOD.Beam(self.screen.get_size()) #Initalizes the long rotating beam

   
    #Game Loop
        while not self.done:
            # Event loop
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.done = True #Sets flag for quitting the game
         
        #Game logic

            #Movement
            self.Player_1.movement()#Player 1 movement function
            self.Player_2.movement()#Player 2 movement function

            self.P1_Laser = self.Player_1.shoot_laser(self.TeleporterList)#Checks to see if player shoots this frame
            self.P2_Laser = self.Player_2.shoot_laser(self.TeleporterList)
                        
            self.beam_info = self.beam.rotate()
        #Screen wrapping
            self.Player_1.screen_wrap() #Screen Wrapping for P1
            self.Player_2.screen_wrap() #Screen wrapping for P2
            
        #Screen-clearing + Drawing
            if self.Player_1.checkHit(self.P2_Laser, False): #Checks to see if a player collided with a player/satellite's laser or an asteroid
                self.P2_Laser = self.Player_2.destroy_laser() #Destroy the incoming laser if so
                
            if self.Player_2.checkHit(self.P1_Laser, False):
                self.P1_Laser = self.Player_1.destroy_laser()            

            self.Player_1.checkHit(self.beam.get_mask(), True)
            self.Player_2.checkHit(self.beam.get_mask(), True)

            self.winner[0] = self.Player_1.win_game(self.Player_2.game_over())
            self.winner[1] = self.Player_2.win_game(self.Player_1.game_over())

            self.P1_list = self.Player_1.get_player() #Retrieves player sprite and rectangle positions and puts them in a list
            self.P2_list = self.Player_2.get_player()
           
            self.screen.update(self.P1_list, self.P2_list, self.P1_Laser, self.P2_Laser, self.WallList, self.ast_list, self.smast_list, self.beam_info, self.winner, self.TeleporterList) #Updates each object's position on the screen

            if self.winner[0] or self.winner[1]: #Checks to see if the player wants to restart or quit the game on the winner screen
                option = self.restart_quit()
                if option != None:
                    pygame.display.quit()
                    return option

            self.clock.tick(60) #Limits game to 60 FPS
        pygame.quit() #Closes the window and quits the game


    def restart_quit(self): #Checks to see which key the player presses to restart or quit
        key = pygame.key.get_pressed()
        if key[pygame.K_r]:
            return True
        if key[pygame.K_q]:
            return False
