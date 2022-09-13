#-------------------------------------------------------------------------------
# Name:        module1
# Purpose:
#
# Author:      kandor-scutaru
#
# Created:     15/12/2016
# Copyright:   (c) kandor-scutaru 2016
# Licence:     <your licence>
#-------------------------------------------------------------------------------
from graphics import *
def squares():
    win = GraphWin("Squares",640,480)
    for i in range(200):
            p = win.getMouse()
            rectLowerLeft = Point(p.getX()-10,p.getY()-10)
            rectUpperRight = Point(p.getX()+10,p.getY()+10)

            R = Rectangle(rectLowerLeft,rectUpperRight)
            R.setOutline("Green")
            R.setFill("red")
            R.draw(win)
    Text(Point(win.getWidth()/2,win.getHeight()/2),"Click the mouse to exit").draw(win)
    win.getMouse()
    win.close()

def target():
    win = GraphWin("Target",600,460)

    center = Point(win.getWidth()/2,win.getHeight()/2)

    colors = ['yellow','red','green','blue','orange','black']
    counter = 0
    for i in [250,200,150,100,50,10]:
        C = Circle(center, i)
        C.setFill(colors[counter])
        C.draw(win)
        counter+=1

def face():
    win = GraphWin("face")
    win.setCoords(-2,-2,13,13)
    box = Rectangle(Point(0,0),Point(9,9))
    box.draw(win)

    lEye = Circle(Point(2,7),1)
    lEye.draw(win)

    rEye = lEye.clone()
    rEye.move(4,0)
    rEye.draw(win)

    nose = Point(4,4)
    nose.draw(win)

    mouth = Line(Point(2,2),Point(6,2))
    mouth.draw(win)

    x = win.getMouse()
    win.close()


def snowman():
    win = GraphWin("snowman")

    triangle = Polygon(Point(20,100),Point(40,50),Point(60,100))
    triangle.setFill("green")
    triangle.draw(win)

    t2 = triangle.clone()
    t2.move(0,-20)
    t2.draw(win)

    trunk = Rectangle(Point(35,120),Point(45,145))
    trunk.setFill("brown")
    trunk.move(0,-20)
    trunk.draw(win)

    head = Circle(Point(10,15),10)
    head.setFill("white")
    head.move(135,70)
    head.draw(win)

    middle = Circle(Point(10,15),20)
    middle.setFill("white")
    middle.move(135,100)
    middle.draw(win)

    bottom = Circle(Point(10,15),30)
    bottom.setFill("white")
    bottom.move(135,150)
    bottom.draw(win)

    lEye = Circle(Point(2,7),1)
    lEye.move(137,75)
    lEye.draw(win)

    rEye = lEye.clone()
    rEye.move(10,0)
    rEye.draw(win)

    x = win.getMouse()
    win.close()


def dice():
    win = GraphWin("dice")
    win.setCoords(-2,-2,11,11)

    dot = Circle(Point(-.25,-.25),.25)
    dot.draw(win)

    d1 = Rectangle(Point(-1,-1),Point(.5,.5))
    d1.draw(win)

    d2 = d1.clone()
    d2.move(2,0)
    d2.draw(win)

    d3 = d1.clone()
    d3.move(4,0)
    d3.draw(win)

    d4 = d1.clone()
    d4.move(6,0)
    d4.draw(win)

    d5 = d1.clone()
    d5.move(8,0)
    d5.draw(win)


    x = win.getMouse()
    win.close()

def main():
    #squares()
    #target()
    #face()
    #snowman()
    dice()

if __name__ == '__main__':
    main()
