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
	
//	private Point ptest;
	
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
	public Graphics g;			//Graphics g for painting
	public Polygon poly = new Polygon();
	
	private Point m = new Point();
	private Point n = new Point();
	
	private int pro_x;
	private int pro_y;
	private int movex;
	private	int movey;
	private int dx, dy;
	boolean flag = true;
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
	
	public void setProMovement(int px, int py, int o, int p)
	{
		pro_x = px;
		pro_y = py;
		dx = o;
		dy = p;
		
		movex = n.x;
		movey = n.y;
	};
	
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
	
/*	public void pointTest(int px, int py)
	{
		ptest = new Point(px,py);
	}*/
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
	
	//Returns xmin
	public int getxmin()
	{
		return xmin;
	}
	
	//Returns ymax
	public int getymax()
	{
		return ymax;
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
		
		/*g.setColor(Color.green);
		g.fillOval(ptest.x, ptest.y, 50, 50);*/
		g.setColor(Color.gray);
		g.fillPolygon(poly);
		g.setColor(Color.black);
		g.drawPolygon(poly);
		
/*		g.setColor(Color.blue);
		g.drawLine(m.x,m.y,n.x,n.y);*/
		
		g.setColor(Color.darkGray);
		g.fillOval(m.x-150, m.y-150, 300, 300);
		g.setColor(Color.blue);
		if(flag)
		{
			g.fillOval(n.x, n.y, 20, 20);
			flag = false;
		}

		movey = movey+dy;
		movex = movex-dx;
		g.fillOval(movex, movey, 20, 20);

/*		g.setColor(Color.green);
		g.fillOval(pro_x, pro_y, 20, 20);*/
		
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
	
	
	//Updates the points of the cannon
	public void updateBarrel(Point a1, Point a2, Point c1, Point c2)
    {
        poly.reset();
        poly.addPoint(a1.x, a1.y);
		poly.addPoint(a2.x, a2.y);
		poly.addPoint(c1.x, c1.y);
		poly.addPoint(c2.x, c2.y);
//		poly.getBounds();  
    }
	
	//Gets points a and c
	public void testLine(Point a, Point c)
	{
		m.setLocation(a);
		n.setLocation(c);
		
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
	