import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.lang.*;
import java.util.*;


class ObjC extends Canvas //implements MouseListener, MouseMotionListener
{
	private int ScreenW;		//Width of the screen
	private int ScreenH;		//Height of the screen
	private int SObj;			//Size of the object
	private int NSObj;			//New size of the object
	
    private int speed;			//Speed of object
    private int size;			//Size of the object
    
	private int ymin;			//Variables to hold points on the canvas
	private int ymax;
	private int xmin;
	private int xmax;
	private int x,y;				//Current position of object
	
	private boolean down = true;	//Y axis direction
	private boolean right = true;	//X axis direction
	private boolean done = false;	//Done boolean
	private boolean more = true;	//More boolean

	//Vector that holds all the rectangles on the canvas
	private Vector<Rectangle> Walls = new Vector <Rectangle>();
	
	private int rx = 0;				//drag-box x coordinate
	private int ry = 0;				//drag-box y coordinate
	private int rWidth = 0;			//drag-box width
	private int rHeight = 0;		//drag-box height
	private static Point m1 = new Point(0,0);				//Holds first point
	private static Point m2 = new Point(0,0);				//Holds the second point
	private Rectangle drag_box = new Rectangle();			//Holds the drag box rectangle
	private Rectangle blank = new Rectangle(0, 0, 0, 0);	//A null rectangle
	
	public Image buffer;		//The image buffer
	public Graphics g;			//Graphics g for paint

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
	
	//Adds one to the vector
	public void addOne(Rectangle r)
	{	
		Walls.addElement(new Rectangle(r));
	}
	
	//Removes one from the vector
	public void removeOne(int i)
	{
		Walls.removeElementAt(i);
	}	
	
	//Retrieves one rectangle at index i from the vector
	public Rectangle getOne(int i)
	{
		return Walls.elementAt(i);
	}
	
	//Returns the amount of rectangles that are in the vector
	public int getWallSize()
	{
		return Walls.size();
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
	
	//Returns the current size of object
	public int getSObj()
	{
		return SObj;
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
	
	//Takes the value of the speed scrollbar divides it by 4 and sets speed
    public void setSpeed(int s){
        speed = s / 4;
    }
    
	//Draws the dragbox
	public void setDragBox(Rectangle r, Point p1, Point p2){
		drag_box = r;
		
		rx = (int)drag_box.getX();
		ry = (int)drag_box.getY();
		rWidth = (int)drag_box.getWidth();
		rHeight = (int)drag_box.getHeight();
		
		
		m1 = p1;
		m2 = p2;
		
	}
	
	//Main painting fuction
	public void paint(Graphics cg)
	{

		if(g!=null)
		{
			g.dispose();
		}

		if(x-speed < xmin)
		x = xmin;
		if(x+speed > xmax)
		x = xmax;
		if(y-speed < ymin)
		y = ymin;
		if(y+speed > ymax)
		y = ymax;
	
		buffer = createImage(ScreenW,ScreenH);
		g = buffer.getGraphics();
		
		
		for(int i = 0; i < Walls.size();i++)
		{
			Rectangle temp = Walls.elementAt(i);
			g.setColor(Color.black);
			g.fillRect(temp.x, temp.y, temp.width, temp.height);
		}
		
        g.setColor(Color.red);
        g.fillOval(x,y, SObj, SObj);
        g.setColor(Color.black);
        g.drawOval(x,y, SObj, SObj);
		
		g.setColor(Color.black);
		g.drawRect(rx, ry, rWidth, rHeight);

		cg.drawImage(buffer,0,0,null);
	}
	
	//Updates SObj and calculates new min/max
	public void Step(){
		SObj = NSObj;
		calcMinMax();
	}
	
	//Checks if x is inside the canvas
	public boolean checkx()
	{
		return(xmin<x && x<xmax);
	}
	
	//Checks if y is inside the canvas
	public boolean checky()
	{
		return(ymin<y && y<ymax);
	}
	
	//Chages the direction of the circle (verticle)
	public void downSwitch()
	{
		down = !down;
	}
	
	//Changes the direction of the circle (Horizontal)
	public void rightSwitch()
	{
		right = !right;
	}
	
	//Moves the x and y values according to where they are on the canvas
	public void move()
	{
		if(y-speed < ymin)
			y = ymin;
		if(y+speed > ymax)
			y = ymax;
		
		if(checky())
		{
			if(down)
			{
				y+=speed;
			}
			else
			{
				y-=speed;
			}
		}
		
		else
		{		
			down = !down;
         
            if(down)
			{
                y+=speed;
            }
            else
			{
                y-=speed;
            }
		}
		
		if(x-speed < xmin)
			x = xmin;
		if(x+speed > xmax)
			x = xmax;
		
		if(checkx())
		{
			if(right)
			{
				x+=speed;
			}
			else
			{
				x-=speed;
			}
		}
		
        else
		{
            right = !right;
            
            if(right)
			{
                x+=speed;
            }
            else
			{
                x-=speed;
            }
        }
	}
}
	