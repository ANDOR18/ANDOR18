#Qr code scanner Alpha v.9
from graphics import *


def qrstuff(frame,set_zbar):
    import cv2.cv as cv # Use OpenCV-2.4.3
    import zbar
    import time
    win = GraphWin("Hall Pass", 800, 800)
    win.setBackground("Black")
    t = Text(Point(400, 400), "Placeholder")
    t.setFill("white")
    t.setSize(35)
    t.setStyle("bold")

    #This puts the program in an infinite loop:
    run = 1
    while run == 1:

        # This is so we can enter the next while loop:
        bad = 2

        #Injected QR decryption
        set_width = 100.0 / 100
        set_height = 90.0 / 100

        coord_x = int(frame.width * (1 - set_width) / 2)
        coord_y = int(frame.height * (1 - set_height) / 2)
        width = int(frame.width * set_width)
        height = int(frame.height * set_height)

        get_sub = cv.GetSubRect(frame, (coord_x + 1, coord_y + 1, width - 1, height - 1))

        cv.Rectangle(frame, (coord_x, coord_y), (coord_x + width, coord_y + height), (255, 0, 0))

        cm_im = cv.CreateImage((get_sub.width, get_sub.height), cv.IPL_DEPTH_8U, 1)
        cv.ConvertImage(get_sub, cm_im)
        image = zbar.Image(cm_im.width, cm_im.height, 'Y800', cm_im.tostring())

        x = set_zbar.scan(image)
        
        cv.ShowImage("Webcam", frame)


        #Date and time assigned to variables:
        y = time.strftime("%m/%d/%y")
        z = time.strftime("%I:%M:%S")

        #Opens and appends name, date, and time-out to a log:
        log = open("Log_test.txt","a")
        log.write("\n{} | {} | {}".format(x,y,z))


        #Placeholder to show that x is out:
        t.undraw()
        t.setText("{} is currently out.".format(x))
        t.draw(win)

        #This loop is in case of the else statement (shown below):
        while bad == 2:
            #This checks for the same value as initial input:
            set_width = 100.0 / 100
            set_height = 90.0 / 100

            coord_x = int(frame.width * (1 - set_width) / 2)
            coord_y = int(frame.height * (1 - set_height) / 2)
            width = int(frame.width * set_width)
            height = int(frame.height * set_height)

            get_sub = cv.GetSubRect(frame, (coord_x + 1, coord_y + 1, width - 1, height - 1))

            cv.Rectangle(frame, (coord_x, coord_y), (coord_x + width, coord_y + height), (255, 0, 0))

            cm_im = cv.CreateImage((get_sub.width, get_sub.height), cv.IPL_DEPTH_8U, 1)
            cv.ConvertImage(get_sub, cm_im)
            image = zbar.Image(cm_im.width, cm_im.height, 'Y800', cm_im.tostring())

            same = set_zbar.scan(image)

            cv.ShowImage("Webcam", frame)

            
            #If it is:
            if same == x:
                #Write time-in to doc and loop to beginning:
                t.undraw()
                t.setText("Welcome Back!!")
                t.draw(win)
                z = time.strftime("%I:%M:%S")
                log.write(" | {}".format(z))
                #This will make bad == 2 false, bringing us to the beginning of the program:
                bad = 1

            #If it isn't:
            else:
                    #States that the two names don't match and will loop to bad == 2:
                    t.undraw()
                    t.setText("You are not {}.".format(x))
                    t.draw(win)

            if same == "Missing":
                t.undraw()
                t.setText("Marked Missing")
                t.draw(win)
                log.write(" | Missing")
                bad = 1



if __name__=="__main__":
    #set up our stuff
    import cv2.cv as cv
    import zbar
    cv.NamedWindow("webcame", cv.CV_WINDOW_AUTOSIZE)
    capture = cv.CaptureFromCAM(-1)
    set_zbar = zbar.ImageScanner()
    while True:
          frame = cv.QueryFrame(capture)
          qrstuff(frame,set_zbar)





