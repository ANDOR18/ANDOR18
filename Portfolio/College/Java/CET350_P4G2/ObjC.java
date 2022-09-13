import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.lang.*;
import java.util.*;


class ObjC extends Canvas
{
	private int ScreenW;		//Width of the screen
	private int ScreenH;		//Height of the screen
	private int SObj;			//Size of the object
	private int NSObj;			//New size of the object
	
    private int speed;			//Speed of object
    private int size;			//Size of the object
    
	private int ymin, ymax, xmin, xmax, yold, xold;		//Variaables to hold points on the canvas
	private int x,y;				//Current position of object
	private boolean rect = true;	//Circle or Rectangle
	private boolean tail = true;	//Tail or no tail
	private boolean clear = false;	//Clear boolean
	
	private boolean down = true;	//Y axis direction
	private boolean right = true;	//X axis direction
	private boolean done = false;	//Done boolean
	private boolean more = true;	//More boolean
	
	//ObjC constructor
	public ObjC(int SB, int w, int h)
	{
		speed = 10;
        
		ScreenW = w;
		ScreenH = h;
		SObj = SB;
		NSObj = SObj;
		
		calcMinMax();
		down = true;
		right = true;
		done = false;
		more = true;
		rect = true;
		tail = true;
		clear = false;
		
		y = ymin+1;
		x = xmin+1;
	}
	
	//Calculates the minimum and maximu x and y values on canvas
	public void calcMinMax()
	{
		ymin = 2;
		xmin = 2;
		ymax = ScreenH - 2 - SObj;
		xmax = ScreenW - 2 - SObj;
	}
	
	//Changes done to true
	public void quitit()
	{
		done = true;
	}
	
	//
	public void rectangle(boolean r)
	{
		rect = r;
	}
	
	//Changes between a circle and a rectangle
	public void setShape()
	{
		rect = !rect;
	}
	
	//Returns true for rectangle, false for circle
	public boolean getShape()
	{
		return rect;
	}
	
	//
	public void Tail(boolean t)
	{
		tail = t;
	}
	
	//Changes between tail and no tail
    public void setTail(){
        tail = !tail;
    }
    
	//Returns true for tail and false for no tail
	public boolean getTail()
	{
		return tail;
	}
	
	//Sets NSObj "new size of object" to SObj "size of object"
	public void update(int NS)
	{
		NSObj = NS;
		SObj = NSObj;
	}
	
	//Returns NSObj
	public int getNSObj()
	{
		return NSObj;
	}
	
	//Called when the window is resized. Sets screen hight and width and calls calc min max to set the canvas
	public void reSize(int w, int h)
	{
		ScreenW = w;
		ScreenH = h;
		calcMinMax();
	}

	//Sets location x
	public void setx(int a)
	{
		x = a;
	}
	
	//Sets location y
	public void sety(int a)
	{
		y = a;
	}
	
	//Returns x
	public int getx()
	{
		return x;
	}
	
	//Returns y
	public int gety()
	{
		return y;
	}
	
	//Changes clear to true
	public void Clear()
	{
		clear = true;
	}
	
	//Takes the value of the speed scrollbar divides it by 4 and sets speed
    public void setSpeed(int s){
        speed = s / 4;
    }
    
	//Draws the red border around the edge of the canvas
	public void paint(Graphics g)
	{
		g.setColor(Color.red);
		g.drawRect(0,0,ScreenW-1, ScreenH-1);
		update(g);
	}
	
	//Main painting fuction
	public void update(Graphics g)
	{
		//Checks to see if clear is true, Repaints whole  canvas if it is
		if(clear)
		{
			super.paint(g);
			clear = false;
			g.setColor(Color.red);
			g.drawRect(0, 0, ScreenW - 1, ScreenH - 1);
		}
		
		//Checks the tail boolean
		if(!tail)
        {        

			//Checks if its a circle or rectangle
            if(rect)
            {
			g.setColor(Color.white);
            g.fillRect(xold, yold, SObj, SObj);
			g.drawRect(xold, yold, SObj, SObj);

			if(x-speed < xmin)
			x = xmin;
			if(x+speed > xmax)
			x = xmax;
			if(y-speed < ymin)
			y = ymin;
			if(y+speed > ymax)
			y = ymax;
			
            g.setColor(Color.lightGray);
            g.fillRect(x,y, SObj, SObj);
            g.setColor(Color.black);
            g.drawRect(x,y, SObj, SObj);
			
			xold = x;
            yold = y;
            }
			
			//Checks if its a circle or rectangle
            else if(!rect)
            {
			g.setColor(Color.white);
            g.fillOval(xold, yold, SObj, SObj);
			g.drawOval(xold, yold, SObj, SObj);

			if(x-speed < xmin)
			x = xmin;
			if(x+speed > xmax)
			x = xmax;
			if(y-speed < ymin)
			y = ymin;
			if(y+speed > ymax)
			y = ymax;
		
            g.setColor(Color.lightGray);
            g.fillOval(x,y, SObj, SObj);
            g.setColor(Color.black);
            g.drawOval(x,y, SObj, SObj);
			
			xold = x;
            yold = y;
            }
        }
        
		//Checks if its a circle or rectangle
        if(rect)
        {

			if(x-speed < xmin)
			x = xmin;
			if(x+speed > xmax)
			x = xmax;
			if(y-speed < ymin)
			y = ymin;
			if(y+speed > ymax)
			y = ymax;
		
            g.setColor(Color.lightGray);
            g.fillRect(x,y, SObj, SObj);
            g.setColor(Color.black);
            g.drawRect(x,y, SObj, SObj);
			
			xold = x;
            yold = y;
        }
		
		//Checks if its a circle or rectangle
		else if(!rect)
        {
			if(x-speed < xmin)
			x = xmin;
			if(x+speed > xmax)
			x = xmax;
			if(y-speed < ymin)
			y = ymin;
			if(y+speed > ymax)
			y = ymax;
		
            g.setColor(Color.lightGray);
            g.fillOval(x,y, SObj, SObj);
            g.setColor(Color.black);
            g.drawOval(x,y, SObj, SObj);
			
			xold = x;
            yold = y;
        }
		
		
			
	}
	
	//Updates SObj and calculates new min/max
	public void Step(){
		SObj = NSObj;
		calcMinMax();
	}
	
	//Checks if x is inside the canvas
	public boolean checkx(){
/*        if(xmin >= x || xmax <= x){
            right = !right;
        }*/
		
		return(xmin<x && x<xmax);
	}
	
	//Checks if y is inside the canvas
	public boolean checky(){
 /*       if(ymin == x || ymax == y){
            down = !down;
        }
        */
		
		return(ymin<y && y<ymax);
	}
	
	//Moves the x and y values according to where they are on the canvas
	public void move(){
		if(y-speed < ymin)
			y = ymin;
		if(y+speed > ymax)
			y = ymax;
		
		if(checky()){
			if(down){
				y+=speed;
			}
			else{
				y-=speed;
			}
		}
		
		else{
						
			down = !down;
            

            
            if(down){
                y+=speed;
            }
            else{
                y-=speed;
            }
		}
		if(x-speed < xmin)
			x = xmin;
		if(x+speed > xmax)
			x = xmax;
		
			
		if(checkx()){
			if(right)
			{
				x+=speed;
			}
			
			else{
				x-=speed;
			}
		}
        else{

            right = !right;

            
            if(right){
                x+=speed;
            }
            else{
                x-=speed;
            }

        }
		
	}	
}
	