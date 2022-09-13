import pygame
from tkinter import *
from PIL import ImageTk, Image


class GUI(object):
     def __init__(self):
          self.window = Tk()
          self.window.geometry("500x350")
          self.window.title("Space Raiders")

          self.player1 = " "
          self.player2 = " "
          self.mapSelectEntry = " "
          self.p1 = Label(self.window, text='Player 1: ')
          self.p1Entry = Entry(self.window)
          self.p2 = Label(self.window, text='Player 2: ')
          self.p2Entry = Entry(self.window)
          self.mapSelect = Label(self.window, text='Enter map #(1,2,or 3): ')
          self.mapSelectEntry = Entry(self.window)

          self.map = Canvas(self.window, width=175, height=100)
          self.map2 = Canvas(self.window, width=175, height=100)
          self.map3 = Canvas(self.window, width=175, height=100)
          
          width = 175
          height = 100

          img1 = Image.open("spr/map1.png")
          img2 = Image.open("spr/map2.png")
          img3 = Image.open("spr/map3.png")
          resize_image1 = img1.resize((width, height))
          resize_image2 = img2.resize((width, height))
          resize_image3 = img3.resize((width, height))

          img = ImageTk.PhotoImage(resize_image1)
          img2 = ImageTk.PhotoImage(resize_image2)
          img3 = ImageTk.PhotoImage(resize_image3)

          self.map.create_image(0, 0, image=img, anchor='nw')
          self.map2.create_image(0, 0, image=img2, anchor='nw')
          self.map3.create_image(0, 0, image=img3, anchor='nw')

          self.subButton = Button(self.window, text='Submit', width=10, command=self.submit)
          self.quitButton = Button(self.window, text='Cancel', width=10, command=self.window.destroy)

          self.getPlayers()
          self.widgetAllign()
          mainloop()

     def submit(self):
          self.player1 = str(self.p1Entry.get())[:8]  ## add selected map
          self.player2 = str(self.p2Entry.get())[:8]
          self.guiMapSelect = str(self.mapSelectEntry.get())[:1]
          self.window.destroy()
             
     def getMap(self):
          try:
               return self.guiMapSelect
          except:
               return False

     def getPlayers(self):
          return self.player1, self.player2

     def closeWindow(self):
          try:
               self.window.protocol("WM_DELETE_WINDOW")
          except:
               None

     def widgetAllign(self):
          self.window.columnconfigure(0, weight=0)
          self.window.rowconfigure(0, weight=0)
          self.window.columnconfigure(2, weight=1)
          self.p1.grid(row=0, column=0)
          self.p1Entry.grid(row=0, column=1)
          self.p2.grid(row=1, column=0)
          self.p2Entry.grid(row=1, column=1)
          self.mapSelect.grid(row=2, column=0 )
          self.mapSelectEntry.grid(row=2, column=1)
          self.map.grid(row=0, column=8, columnspan=2, rowspan=3, padx=10)
          self.map2.grid(row=5, column=8, columnspan=2, rowspan=3, padx=10, pady=10)
          self.map3.grid(row=8, column=8, columnspan=2, rowspan=3, padx=10)

          self.subButton.grid(row=10, column=0, padx=10)
          self.quitButton.grid(row=10, column=1)
