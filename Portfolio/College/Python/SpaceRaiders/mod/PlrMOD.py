import pygame
import mod.SprMOD
import mod.SndMOD
import os
#PlrMOD.py
#Contains all classes related to player functionality (including lasers)

class Laser:
    def __init__(self): #Constructor
        super().__init__()
        self.speed = 25 #Limits how fast the laser moves when shot
        self.Laser_RECT = pygame.Rect(0, 0, 0, 0)
        self.snd = mod.SndMOD.snd(.5)
        self.laserInfo = [0]*5
    def make_laser(self, P_num, P_RECT_x, P_RECT_y, flip): #Using the current players positional information, creates a new laser and returns information about it in a list

        self.P_num = P_num
        self.flip = flip
        if self.P_num == 1: #Checks to see which sprite index to use
            Laser_name = 'spr\P1_Laser.png'
        elif self.P_num == 2:
            Laser_name = 'spr\P2_Laser.png'

        if self.flip != True: #Checks to see which direction the laser should start at
            P_RECT_x = P_RECT_x+64

        self.L_Sprite = pygame.image.load(Laser_name).convert_alpha()
        self.L_pos = (P_RECT_x, P_RECT_y+16)
        self.Laser_RECT = pygame.Rect(self.L_pos[0], self.L_pos[1], 32, 16)
        self.laserInfo = [self.L_Sprite, self.Laser_RECT.x, self.Laser_RECT.y, self.Laser_RECT.w, self.Laser_RECT.h] #laserInfo = [Sprite index, X, Y, WIDTH, HEIGHT]
        self.snd.Laser()
        return self.laserInfo

    def laser_movement(self, Laser_RECT_in): #Using the latest positional information stored in laserInfo, checks to see which direction the laser should move in and increases/decreases the position by the speed set.
                                            #Returns the new positional value for the laser's hitbox
        if self.flip == True: #If ship is facing left when shot, move laser left
            Laser_RECT_in -= self.speed

        else: #If ship is facing right when shot, move laser right
            Laser_RECT_in += self.speed
            
        self.Laser_RECT.x = Laser_RECT_in #Update the position of the laser hitbox
        return self.Laser_RECT.x
        
    def screen_wrap(self, screen_size, Laser_RECT_in): #Screen Wrapping
        #If laser exits screen to the right, wrap around to the left
        if Laser_RECT_in > screen_size[0]:
            Laser_RECT_in = -64
            
        #If laser exits screen to the left, wrap around to the right    
        elif Laser_RECT_in < -64:
            Laser_RECT_in = screen_size[0]

        self.Laser_RECT.x = Laser_RECT_in #Update the position of the laser hitbox
        return self.Laser_RECT.x
    
    def checkCollision(self, WallList): #Checks collision between player and wall
        flag = False
        for i in WallList: #checks to see if player collides with any existing walls
            if pygame.Rect.colliderect(self.Laser_RECT, pygame.Rect(i.x-7, i.y, i.width, i.height)):
                flag = True
            elif pygame.Rect.colliderect(self.Laser_RECT, pygame.Rect((i.x-44)+i.width, i.y, i.width, i.height)):
                if(self.Laser_RECT.x <= i.x+i.width+2):
                    flag = True
            if pygame.Rect.colliderect(self.Laser_RECT, pygame.Rect(i.x, i.y, i.width, i.height)):
                if(self.Laser_RECT.y <= i.y+i.height and self.Laser_RECT.y >= i.y+i.height-10):
                    flag = True
            elif pygame.Rect.colliderect(self.Laser_RECT, pygame.Rect(i.x, i.y-7, i.width, i.height)):
                flag = True
        #print(flag)
        return flag

    def checkTeleportCollision(self, teleList): #Checks to see if a laser collided with a teleporter, then updates laserInfo
        for i in teleList:
            i.flash(False, False)
            if pygame.Rect.colliderect(self.Laser_RECT, pygame.Rect(i.x, i.y, i.width, i.height)) and self.laserInfo[0] != 0:
                if(i.T_num == 1):
                    new_pos = teleList[3].getRECT()
                elif(i.T_num == 2):
                    new_pos = teleList[5].getRECT()
                elif(i.T_num == 3):
                    new_pos = teleList[4].getRECT()                   
                elif(i.T_num == 4):
                    new_pos = teleList[0].getRECT()
                elif(i.T_num == 5):
                    new_pos = teleList[2].getRECT()
                elif(i.T_num == 6):
                    new_pos = teleList[1].getRECT()
                elif(i.T_num == 7):
                    new_pos = teleList[7].getRECT()
                elif(i.T_num == 8):
                    new_pos = teleList[6].getRECT()

                self.Laser_RECT.x = new_pos[0]
                self.Laser_RECT.y = new_pos[1]
                self.laserInfo[1] = self.Laser_RECT.x
                self.laserInfo[2] = self.Laser_RECT.y
                i.flash(True, False)
        return self.laserInfo


class Player:
    def __init__(self, p_name): #Constructor
        super().__init__()
        
        self.accx = 0 #Player acceleration in the x axis
        self.accy = 0 #Player acceleration in the y axis
        self.speed = 4.5 #Max ship speed
        self.p_name = p_name
        self.laserShot = Laser() #Creates a laser class for the player to allow them to shoot
        self.laserInfo = [0]*5 #Inits a list to store information about the laser shot
        self.laserActive = False #Flag for if a player's laser is active
        self.laserEndLife = 15 #Sets the max time a laser can be out for
        self.laserCurLife = 0 #Counts the current time a laser has been active
        self.laserCoolDown = 25 #Sets the max time the player must wait before using the laser again
        self.laserCoolDownCount = self.laserCoolDown #Counts down the current time a laser hasnt been shot
        self.safeRespawnTimeCount = 0 #Counts how long player is invincible for
        self.lives = 3 #Counts how many lives the player has left
        self.screen_size = [0]*2 #Inits a list to store information about the display window
        self.dying = False #Flag to see if dying animation is playing
        self.lose = False #Flag to see if player won
        self.win = False #Flag to see if player lost
        self.snd = mod.SndMOD.snd(.5) #Initalizes the sound class and sets the volume to .5
        self.snd.Respawn() #Plays the respawn sound effect
        self.teleporting = False
        
    def set_respawnTime(self, respawn_time):
        self.safeRespawnTime = respawn_time #Sets the max time a player is invincible for when respawning
        
    def init_player(self, P_num):
        self.P_num = P_num
        #checks for the player number the class initalized with and sets the approptiate starting position and sprite
        if self.P_num == 1:
            P_pos = (288, 100)
            self.P_Sprite = mod.SprMOD.spr_Player1() #Load Player Sprite
            self.L_Sprite = [pygame.image.load(os.path.join('spr','lives1_0.png')).convert_alpha(), pygame.image.load(os.path.join('spr','lives1_1.png')).convert_alpha(), pygame.image.load(os.path.join('spr','lives1_2.png')).convert_alpha(), pygame.image.load(os.path.join('spr','lives1_3.png')).convert_alpha()]
            self.L_spr_pos = (30, 15)
            self.flip = False #Flip flag for the player's sprite

        elif self.P_num == 2:
            P_pos = (864, 100)
            self.P_Sprite = mod.SprMOD.spr_Player2() #Load Player Sprite
            self.L_Sprite = [pygame.image.load(os.path.join('spr','lives2_0.png')).convert_alpha(), pygame.image.load(os.path.join('spr','lives2_1.png')).convert_alpha(), pygame.image.load(os.path.join('spr','lives2_2.png')).convert_alpha(), pygame.image.load(os.path.join('spr','lives2_3.png')).convert_alpha()]
            self.P_Sprite.flip()
            self.L_spr_pos = (1152-69-30, 15)
            self.flip = True #Flip flag for the player's sprite

        self.RECT = pygame.Rect(P_pos[0], P_pos[1], 64, 64) #Player Hitbox (X, Y, Width, Height)
        
    def checkHit(self, P_Laser, mask_flag): #Checks if a player has been hit, returns true if so
        flag = False
        self.collide_point = 0
        if self.safeRespawnTimeCount == self.safeRespawnTime and self.dying == False and self.win == False and self.lose == False: #Checks for collisions via rectangles that are passed in; for more general hit box collisions
            self.P_Sprite.cooldown(False, self.flip)
            if mask_flag == False:
                if pygame.Rect.colliderect(self.RECT, pygame.Rect(P_Laser[1], P_Laser[2], P_Laser[3], P_Laser[4])) and self.safeRespawnTimeCount == self.safeRespawnTime:
                    if self.lives != 0:
                        self.lives -= 1 #Decrease life count by 1
                        self.dying = True
                        flag = True #Returns a true flag for player being hit
                        self.snd.Explode()
                    if self.lives == 0:
                        self.lose = True
                
            elif mask_flag == True: #Checks for collisions via sprite masks that are passed in; for more precise hit box collisions, easier for rotating objects
                self.P_Sprite.rect[0] = self.RECT.x #Update Player sprite's rect attribute with new position
                self.P_Sprite.rect[1] = self.RECT.y
                self.P_Sprite.make_mask() #Update the player's sprite mask
                self.collide_point = pygame.sprite.collide_mask(self.P_Sprite, P_Laser) #Checks to see if the player's mask attribute collides with the other object's mask attribute passed in
                if self.collide_point != None and self.safeRespawnTimeCount == self.safeRespawnTime:
                    if self.lives != 0:
                        self.lives -= 1
                        self.dying = True
                        flag = True
                        self.snd.Explode()
                    if self.lives == 0:
                        self.lose = True
                        
        elif self.safeRespawnTimeCount < self.safeRespawnTime and self.dying == False: #If cooldown time is less than the limit, increment by 1
            self.P_Sprite.cooldown(True, self.flip) #Sets the player sprite to the partially transparent one to indicate invincibility
            self.safeRespawnTimeCount += 1
            
        elif self.dying == True: #if true, plays the dying animation and plays the respawn sound at the end
            self.dying = self.P_Sprite.blow_up(self.flip, self.lose)
            if self.dying == False and self.lose == False:
                self.init_player(self.P_num) #Respawn player at starting position
                self.safeRespawnTimeCount = 0 #Resets respawn cooldown time
                flag = True
                self.snd.Respawn()
        return flag

    def checkCollision(self, WallList): #Checks collision between player and wall
        for i in WallList: #checks to see if player collides with any existing walls
            if pygame.Rect.colliderect(self.RECT, pygame.Rect(i.x-7, i.y, i.width, i.height)):
                self.accx = 0
            elif pygame.Rect.colliderect(self.RECT, pygame.Rect((i.x-44)+i.width, i.y, i.width, i.height)):
                if(self.RECT.x <= i.x+i.width+2):
                    self.accx = 0
                    self.RECT.x+=2
            if pygame.Rect.colliderect(self.RECT, pygame.Rect(i.x, i.y, i.width, i.height)):
                if(self.RECT.y <= i.y+i.height and self.RECT.y >= i.y+i.height-10):
                    self.accy = 0
                    self.RECT.y+=2
            elif pygame.Rect.colliderect(self.RECT, pygame.Rect(i.x, i.y-7, i.width, i.height)):
                    self.accy = 0


    def checkTeleportCollision(self, teleList): #Checks to see if player collided with a teleporter and updates the position accordingly
        for i in teleList:
            i.flash(False, True)
            if pygame.Rect.colliderect(self.RECT, pygame.Rect(i.x, i.y, i.width, i.height)):
                if(i.T_num == 1):
                    new_pos = teleList[3].getRECT()
                elif(i.T_num == 2):
                    new_pos = teleList[5].getRECT()
                elif(i.T_num == 3):
                    new_pos = teleList[4].getRECT()                    
                elif(i.T_num == 4):
                    new_pos = teleList[0].getRECT()
                elif(i.T_num == 5):
                    new_pos = teleList[2].getRECT()
                elif(i.T_num == 6):
                    new_pos = teleList[1].getRECT()
                elif(i.T_num == 7):
                    new_pos = teleList[7].getRECT()
                elif(i.T_num == 8):
                    new_pos = teleList[6].getRECT()
                self.RECT.x = new_pos[0]
                self.RECT.y = new_pos[1]
                i.flash(True, True)
            
   
    def checkLaserCollision(self, WallList): #Checks to see if a laser collided with a wall
        if self.laserShot.checkCollision(WallList):
            return True
        return False

    def checkLaserTPCollision(self, teleList): #calls the laser's check for teleporter collisions and returns the updated laser info
         self.laserInfo = self.laserShot.checkTeleportCollision(teleList)
         return self.laserInfo
#--------Movement--------
    def movement(self):
        key = pygame.key.get_pressed()
        if self.P_num == 1 and self.dying == False and self.lose == False: #Player 1 controls
            if key[pygame.K_w] and not key[pygame.K_s]: #Move Up
                self.acc_up()
            if key[pygame.K_s] and not key[pygame.K_w]: #Move Down
                self.acc_down()
            if key[pygame.K_a] and not key[pygame.K_d]: #Move Left
                self.acc_left()
            if key[pygame.K_d] and not key[pygame.K_a]: #Move Right
                self.acc_right()
                
            if not key[pygame.K_w] or key[pygame.K_s]: #Decelerate Up
                self.dec_up()
            if not key[pygame.K_s] or key[pygame.K_w]: #Decelerate Down
                self.dec_down()
            if not key[pygame.K_a] or key[pygame.K_d]: #Decelerate Left
                self.dec_left()
            if not key[pygame.K_d] or key[pygame.K_a]: #Decelerate Right
                self.dec_right()
            #if not key[pygame.K_a] or not key[pygame.K_d]:


                    
        elif self.P_num == 2 and self.dying == False and self.lose == False: #Player 2 controls
            if key[pygame.K_UP] and not key[pygame.K_DOWN]: #Move Up
                self.acc_up()
            if key[pygame.K_DOWN] and not key[pygame.K_UP]: #Move Down
                self.acc_down()
            if key[pygame.K_LEFT] and not key[pygame.K_RIGHT]: #Move Left
                self.acc_left()
            if key[pygame.K_RIGHT] and not key[pygame.K_LEFT]: #Move Right
                self.acc_right()
                
            if not key[pygame.K_UP] or key[pygame.K_DOWN]: #Decelerate Up
                self.dec_up()
            if not key[pygame.K_DOWN] or key[pygame.K_UP]: #Decelerate Down
                self.dec_down()
            if not key[pygame.K_LEFT] or key[pygame.K_RIGHT]: #Decelerate Left
                self.dec_left()
            if not key[pygame.K_RIGHT] or key[pygame.K_LEFT]: #Decelerate Right
                self.dec_right()
                
        elif self.dying: 
            self.accy = 0
            self.accx = 0
              
 #-------Acceleration Functions--------
    def acc_up(self):
        if self.accy > self.speed*-1:
            self.accy -= .1
        self.RECT.y += self.accy
            
    def acc_down(self):
        if self.accy < self.speed:
            self.accy += .1
        self.RECT.y += self.accy
            
    def acc_left(self):
        if self.flip == False: #Flips the player sprite
            self.flip = True
            self.P_Sprite.flip()
                    
        if self.accx > self.speed*-1:
            self.accx -= .1
        self.RECT.x += self.accx
        
    def acc_right(self):
        if self.flip == True: #Flips the player sprite
            self.flip = False
            self.P_Sprite.flip()
                    
        if self.accx < self.speed:
            self.accx += .1
        self.RECT.x += self.accx

 #-------Deceleration Functions--------
    def dec_up(self):
        if self.accy < 0:
            self.accy += .1
        if self.accy < 0.09 and self.accy > -0.09:
            self.accy = 0
        self.RECT.y += self.accy

    def dec_down(self):
        if self.accy > 0:
            self.accy -= .1
        if self.accy < 0.09 and self.accy > -0.09:
            self.accy = 0
        self.RECT.y += self.accy
                
    def dec_left(self):
        if self.accx < 0:
            self.accx += .1
        if self.accx < 0.09 and self.accx > -0.09:
            self.accx = 0
        self.RECT.x += self.accx
        
    def dec_right(self):
        if self.accx > 0:
            self.accx -= .1
        if self.accx < 0.09 and self.accx > -0.09:
            self.accx = 0
        self.RECT.x += self.accx

#-------------------------------------
        
    def screen_wrap(self): #Screen Wrapping
        #If player exits screen to the right, wrap around to the left
        if self.RECT.x > self.screen_size[0]:
            self.RECT.x = -64
            
        #If player exits screen to the left, wrap around to the right    
        if self.RECT.x < -64:
            self.RECT.x = self.screen_size[0]

        #If player exits screen downward, wrap around to the top
        if self.RECT.y > self.screen_size[1]:
            self.RECT.y = -64
            
        #If player exits screen upward, wrap around to the bottom
        if self.RECT.y < -64:
            self.RECT.y = self.screen_size[1]
            
        
    def get_player(self): #Returns a list containing the player sprite to be used and the position of the hitbox (RECT) 
        P_list = [self.P_Sprite.image, self.RECT.x, self.RECT.y, self.RECT.w, self.RECT.h, self.L_Sprite[self.lives], self.lives, self.L_spr_pos, self.p_name]
        return P_list
    
    def send_screen(self, screen_size):
        self.screen_size = screen_size

    def shoot_laser(self, tp_list): #Checks to see if either player shot a laser and activates the appropriate creation and movement functions of the laser
                            #Returns information about the laser
        key = pygame.key.get_pressed()
        if self.laserCoolDownCount < self.laserCoolDown:
            self.laserCoolDownCount += 1


        elif self.laserCoolDownCount >= self.laserCoolDown and self.lose == False and self.dying == False:
            if self.laserActive == False: #If the player has not shot a laser
                if self.P_num == 1 and key[pygame.K_LSHIFT]: #If player 1 and left shift is pressed
                    self.laserInfo = self.laserShot.make_laser(self.P_num, self.RECT.x, self.RECT.y, self.flip) #Creates a new laser
                    self.laserActive = True #Sets the active laser flag to true

                if self.P_num == 2 and key[pygame.K_KP0]: #If player 2 and Num0 is pressed
                    self.laserInfo = self.laserShot.make_laser(self.P_num, self.RECT.x, self.RECT.y, self.flip) #Creates a new laser
                    self.laserActive = True #Sets the active laser flag to true

            if self.laserActive == True: #If the laser is active
                if self.laserCurLife < self.laserEndLife: #If the laser has not reached it's end of life yet
                    self.laserInfo[1] = self.laserShot.laser_movement(self.laserInfo[1])#Move the laser
                    self.laserInfo[1] = self.laserShot.screen_wrap(self.screen_size, self.laserInfo[1])
                    if tp_list[0] != 0:
                        self.laserInfo = self.laserShot.checkTeleportCollision(tp_list)
                    self.laserCurLife += 1 #Increase life count by 1

                else: #If the laser has reached it's end of life
                    self.laserCurLife = 0 #Reset the lasers current life to 0
                    self.laserInfo = [0]*5 #Clear any information about the laser
                    self.laserShot.Laser_RECT = pygame.Rect(0,0,0,0)
                    self.laserActive = False #Sets the laser to inactive
                    self.laserCoolDownCount = 0 #Activates cool down
                    
                    
        return self.laserInfo
    
    def destroy_laser(self):
        self.laserCurLife = 0 #Reset the lasers current life to 0
        self.laserInfo = [0]*5 #Clear any information about the laser
        self.laserActive = False #Sets the laser to inactive
        self.laserCoolDownCount = 0 #Activates cool down
        self.laserShot.Laser_RECT = pygame.Rect(0,0,0,0)
        return self.laserInfo
    
    
    def game_over(self): #Checks to see if either player lost all of their lives
        return self.lose

    def win_game(self, lose): #Checks to see if either player won using the lose flag from the other player
        if lose == True and self.lose == False:
            self.win = True
            self.dying = False
            self.P_Sprite.win(self.flip)
            return True
        else:
            return False
            
