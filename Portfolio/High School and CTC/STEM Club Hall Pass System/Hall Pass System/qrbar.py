#!/usr/bin/env python2
# -*- coding: utf-8 -*-
# Author : Jimmyromanticdevil
# QRbar-cv
#
# Proc of consept :
# this is just simple code from part of my work for QRcode & Barcode scanner with webcame stuff
# i am using Opencv for realtime track the image & zbar for decode the image
# 
# Dependency :
# 
#
# Some of Good Refrensi stuff :
#   https://github.com/jayrambhia/Install-OpenCV
#   http://nwlinux.com/install-qtqr-in-ubuntu-10-04-lucid-using-apt-get/
#   http://zbar.sourceforge.net/


import cv2.cv as cv #Use OpenCV-2.4.3
import zbar

def scanner_procces(frame,set_zbar):    
    set_width = 100.0 / 100
    set_height = 90.0 / 100
    
    coord_x = int(frame.width * (1 - set_width)/2)
    coord_y = int(frame.height * (1 - set_height)/2)
    width = int(frame.width * set_width)
    height = int(frame.height * set_height)
    
    get_sub = cv.GetSubRect(frame, (coord_x+1, coord_y+1, width-1, height-1))
    
    cv.Rectangle(frame, (coord_x, coord_y), (coord_x + width, coord_y + height), (255,0,0))
    
    cm_im = cv.CreateImage((get_sub.width, get_sub.height), cv.IPL_DEPTH_8U, 1)
    cv.ConvertImage(get_sub, cm_im)
    image = zbar.Image(cm_im.width, cm_im.height, 'Y800', cm_im.tostring())
    
    set_zbar.scan(image)
    for symbol in image:
            print '"%s"' % (symbol.data)
            
    cv.ShowImage("webcame", frame)
    #cv.ShowImage("webcame2", get_sub)
    cv.WaitKey(10)

    
if __name__ == "__main__":
    #set up our stuff
    cv.NamedWindow("webcame", cv.CV_WINDOW_AUTOSIZE)
    capture = cv.CaptureFromCAM(-1)
    set_zbar = zbar.ImageScanner()
    while True:
          frame = cv.QueryFrame(capture)
          scanner_procces(frame,set_zbar)
