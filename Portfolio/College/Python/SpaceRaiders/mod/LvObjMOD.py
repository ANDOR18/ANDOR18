import pygame
import random
import os
import mod.SprMOD
import mod.SndMOD
#LvObjMOD.py
#Contains all the classes relating to hazards and walls in in levels.

class Wall: #A wall that players can bump into
    def __init__(self, x, y, width, height, vert_flag, screen): #Constructor
        #Initializes rectangle
        pygame.sprite.Sprite.__init__(self)
        self.x = x
        self.y = y
        self.height = height
        self.width = width
        self.screen = screen
        
        if vert_flag:
            sprite_name = 'vertical_wall.png'
        else:
            sprite_name = 'horizontal_wall.png'

        #Creates rectangle
        self.image = pygame.image.load(os.path.join('spr',sprite_name)).convert_alpha()
        self.rect = self.image.get_rect()
        
class Teleporter: #Comes in pairs, moves the player from one location to another
    def __init__(self, color, T_num, T_pos): #Constructor
        super().__init__()
        pygame.sprite.Sprite.__init__(self)
        self.T_num = T_num
        self.T_pos = T_pos
        self.x = T_pos[0]
        self.y = T_pos[1]
        self.i = 0
        self.j = 0
        self.width = 64
        self.height = 250
        self.player_y = self.T_pos[1]+(self.height/2)-32
        self.snd = mod.SndMOD.snd(.5)
        if color == 1:
            sprite_name = ['b1.png', 'b2.png']
        if color == 2:
            sprite_name = ['r1.png', 'r2.png']
        if color == 3:
            sprite_name = ['w1.png', 'w2.png']
        if color == 4:
            sprite_name = ['y1.png', 'y2.png']

        self.spr = [pygame.image.load(os.path.join('spr','teleporter_'+sprite_name[0])).convert_alpha(), pygame.image.load(os.path.join('spr','teleporter_'+sprite_name[1])).convert_alpha()]
        self.image = self.spr[0]

    def getRECT(self): #Function that teleports the player
        if self.T_num == 4 or self.T_num == 7 or self.T_num == 6 or self.T_num == 5:
            new_pos = (self.T_pos[0]-80, self.player_y)
        else:
            new_pos = (self.T_pos[0]+80, self.player_y)
        return new_pos
        
    def flash(self, on, sound): #Plays the animation and sound for when the player goes through a teleporter
        if on:
            self.i = 1
            self.image = self.spr[self.i]
            if sound:
                self.snd.Teleporter()
        else:
            if self.i == 1:
                self.j += 1
            if self.j == 5:
                self.i = 0
                self.image = self.spr[self.i]
                self.j = 0
        
class Asteroid: #Moves randomly and kills the player upon impact, can be split into two smaller asteroids (see child class sm_Asteroid)
    def __init__(self, screen_size, P1_list, P2_list): #Constructor, takes screen size and info about P1 and P2 to spawn asteroids
        super().__init__()
        self.screen_size = screen_size #Stores screen size
        self.spawn_flag = False #Controlls when an asteroid can spawn
        while self.spawn_flag == False: #Loops until asteroids do not spawn on top of player
            P1_RECT = pygame.Rect(P1_list[1],P1_list[2],P1_list[3],P1_list[4])
            P2_RECT = pygame.Rect(P2_list[1],P2_list[2],P2_list[3],P2_list[4])
            self.Ast_RECT = pygame.Rect(random.randrange(screen_size[0]), random.randrange(screen_size[1]), 256, 256)
            if not pygame.Rect.colliderect(self.Ast_RECT, P1_RECT) and not pygame.Rect.colliderect(self.Ast_RECT, P2_RECT):
                self.spawn_flag = True
        name_select = random.randrange(1, 3)
        if name_select == 1:
            sprite_name = 'ast.png'
        elif name_select == 2:
            sprite_name = 'ast2.png'
        elif name_select == 3:
            sprite_name = 'ast3.png'
        self.astr_sprite = pygame.image.load(os.path.join('spr',sprite_name)).convert_alpha() #Grabs the location of the sprite
        rand_max = 3 #Max possible movement speed of the asteroids
        self.move_x = random.randrange(rand_max*-1, rand_max)
        while self.move_x == 0:
            self.move_x = random.randrange(rand_max*-1, rand_max)

        self.move_y = random.randrange(rand_max*-1, rand_max)
        while self.move_y == 0:
            self.move_y = random.randrange(rand_max*-1, rand_max)
            
        self.scw_dist = -256
        self.ast_info = [0] * 5
        self.snd = mod.SndMOD.snd(.5)
    def movement(self):
        self.Ast_RECT.x += self.move_x #Move at generated speed
        self.Ast_RECT.y += self.move_y #Move at generated speed

    def get_ast(self): #Grab info about the asteroid for the update function 
        ast_info = [self.astr_sprite, self.Ast_RECT.x, self.Ast_RECT.y, self.Ast_RECT.w, self.Ast_RECT.h]
        return ast_info
        
    def hit(self, P_laser): #Checks to see if a laser hit the asteroid, returns a boolean
        flag = False
        P_LRECT = pygame.Rect(P_laser[1],P_laser[2],P_laser[3],P_laser[4])
        if pygame.Rect.colliderect(self.Ast_RECT, P_LRECT):
            flag = True
            self.snd.AstExplode()
        return flag
        
    def screen_wrap(self): #Screen Wrapping
        #If object exits screen to the right, wrap around to the left
        if self.Ast_RECT.x > self.screen_size[0]:
            self.Ast_RECT.x = self.scw_dist
            
        #If object exits screen to the left, wrap around to the right    
        if self.Ast_RECT.x < self.scw_dist:
            self.Ast_RECT.x = self.screen_size[0]

        #If object exits screen downward, wrap around to the top
        if self.Ast_RECT.y > self.screen_size[1]:
            self.Ast_RECT.y = self.scw_dist
            
        #If object exits screen upward, wrap around to the bottom
        if self.Ast_RECT.y < self.scw_dist:
            self.Ast_RECT.y = self.screen_size[1]
            
class sm_Asteroid(Asteroid): #Inherits classes from Asteroid, constructor takes the screen size and the 
    def __init__(self, screen_size, ast_x, ast_y): #current position of the destroyed asteroid to spawn new small asteroids
        self.screen_size = screen_size
        self.Ast_RECT = pygame.Rect(ast_x, ast_y, 128, 128)
        self.scw_dist = -128
        rand_max = 3
        self.move_x = random.randrange(rand_max*-1, rand_max)
        while self.move_x == 0:
            self.move_x = random.randrange(rand_max*-1, rand_max)

        self.move_y = random.randrange(rand_max*-1, rand_max)
        while self.move_y == 0:
            self.move_y = random.randrange(rand_max*-1, rand_max)

        name_select = random.randrange(1, 3)
        if name_select == 1:
            sprite_name = 'sm_ast.png'
        elif name_select == 2:
            sprite_name = 'sm_ast2.png'
        elif name_select == 3:
            sprite_name = 'sm_ast3.png'  
        self.astr_sprite = pygame.image.load(os.path.join('spr',sprite_name)).convert_alpha()
        self.snd = mod.SndMOD.snd(.5)        

class Beam: #A long rotating beam that rotates accross the whole screen and kills the player upon impact. It slows down, speeds up, and changes direction periodically. 

    def __init__(self, screen_size): #Inits the beam
        self.Beam_spr = mod.SprMOD.spr_BEAM(screen_size)
        self.beam_info = [0]*5
        self.snd = mod.SndMOD.snd(.5)
        
    def rotate(self): #Rotates the beam
        self.beam_info = self.Beam_spr.rotate()    
        return self.beam_info
        
    def get_info(self): #Returns info about the beam
        return self.beam_info

    def get_mask(self): #Generates a mask for the beam (to check for player collisions)
        return self.Beam_spr
