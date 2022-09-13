/*
Program 5
CET 350 Group 2
Kevin Andor Scutaru - AND3256@calu.edu
Matthew Oblock - OBL2109@calu.edu
*/

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.lang.*;
import java.util.*;

public class BouncingBall extends Frame implements WindowListener, ActionListener, 
AdjustmentListener, ComponentListener, Runnable, MouseListener, MouseMotionListener
{
	//Initialize Variables
	private ObjC Obj;
	private Thread thr;
	private boolean TimePause = true;
	private long sp;
	private long delay;
	private boolean ThFlag = true;
	
	private static Button bRun;
    private static Button bPause;
    private static Button bQuit;
    private static Scrollbar speed = new Scrollbar(Scrollbar.HORIZONTAL, 50, 20, 0, 120);;
	private static Scrollbar size = new Scrollbar(Scrollbar.HORIZONTAL, 50, 20, 0, 120);;
	private static Label spl;
	private static Label sil;
	private static Label bln = new Label("");
	private static int spacing_size;
	private static Panel sheet = new Panel();
	private static Panel control = new Panel();
	private static int Control_height;
	private static int Control_width;
	private static int Win_height;
	private static int Win_width;
	private static int Screen_height;
	private static int Screen_width;
	private Insets I;
	private boolean intersect;
	private static int center;
	private static Point FrameSize = new Point(1000, 800);
	private static Point Screen = new Point(FrameSize.x-1, FrameSize.y-1);
	private Rectangle Perimeter = new Rectangle(0,0, Screen.x, Screen.y);
	private Rectangle temp_b = new Rectangle(); 
	private	int old_sobj;
	private int bb_sp;
	private static Point m1 = new Point(0,0);
	private static Point m2 = new Point(0,0);
	private Rectangle drag_box = new Rectangle();
	private static final Rectangle ZERO = new Rectangle(0, 0, 0, 0);
	private static boolean ok_size = true;
	private static boolean ok_bounce = true;
	private static Point pTemp = new Point(0,0);
	private Rectangle hitBox = new Rectangle();
	
	//The main
	public static void main (String[] args) throws IOException
	{    
        new BouncingBall();   
    }
	
	//BouncingBall class
    public BouncingBall(){
		
        //Sets frame properties
        this.setResizable(true);
        this.addWindowListener(this);
		this.setBackground(Color.white);
        this.setLayout(new BorderLayout());
		this.setBounds(10,20,FrameSize.x, FrameSize.y);
		
		//Sets layout of the sheet
		sheet.setLayout(new BorderLayout(0,0));
		sheet.setBackground(Color.white);
		
		//Initializing the gridbag Layout
		double columnWeight[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
        double rowWeight[] = {1,1,1,1};
        int columnWidth[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
        int rowHeight[] = {1,1,1,1};
		
		GridBagLayout displ = new GridBagLayout();
		GridBagConstraints c = new GridBagConstraints();
		
		displ.rowHeights = rowHeight;
		displ.columnWidths = columnWidth;
		
		displ.rowWeights = rowWeight;
		displ.columnWeights = columnWeight;
		
		c.anchor = GridBagConstraints.WEST;
		
		control.setSize(FrameSize.x, 2*30);
		control.setLayout(displ);

		c.weightx = 1;
		c.weighty = 1;
		
		MakeSheet();
		InitComponents();
		
		
//Buttons and Scrollbars
	
		//Run Button
		bRun.setBounds(0,0,80,30);
		c.gridwidth = 1;
		c.gridheight = 1;
		c.fill = GridBagConstraints.BOTH;
		c.gridy = 2;
		c.gridx = 9;
		displ.setConstraints(bRun, c);
		
		//Pause Button
		bPause.setBounds(0,0,80,30);
		c.gridx = 10;
		displ.setConstraints(bPause, c);
		
		//Quit Button
		bQuit.setBounds(0, 0, 80, 30);
		c.gridx = 11;
		displ.setConstraints(bQuit, c);
		
		
		//Speed Scrollbar	
		speed.setBounds(0,0,120,20);
		c.gridwidth = 2;
		c.gridheight = 1;
		c.fill = GridBagConstraints.BOTH;
		c.gridy = 2;
		c.gridx = 1;
		displ.setConstraints(speed, c);
	
		//Size Scrollbar
		size.setBounds(0,0,120,20);
		c.gridx = 18;
		displ.setConstraints(size, c);
		
		
//Scrollbar labels

		//Speed
		spl.setBounds(0,0,60,30);
		c.gridwidth = 1;
		c.gridheight = 1;
		c.fill = GridBagConstraints.BOTH;
		c.gridy = 3;
		c.gridx = 2;
		displ.setConstraints(spl, c);
		
		//Size	
		sil.setBounds(0,0,60,30);
		c.gridx = 19;
		displ.setConstraints(sil, c);
		
		Win_width = this.getWidth();
		Win_height = this.getHeight();
	
		//Adds components to screen
		this.add("Center", sheet);
		this.add("South", control);
		this.validate();
		
		control.add(speed);
		control.add(bRun);
		control.add(bPause);
		control.add(bQuit);
		control.add(size);
		control.add(spl);
		control.add(sil);
		sheet.add("Center", Obj);
		bPause.setEnabled(false);
		
		Start();

		this.addComponentListener(this);
		this.setVisible(true);
		control.setVisible(true);
		sheet.setVisible(true);
    }
    
	//Sets the size of the canvas and the controls
	private void MakeSheet()
	{
		Control_height = 26;
		I = getInsets();
		Screen.x = FrameSize.x - I.left - I.right;
		Screen.y = FrameSize.y - I.top - I.bottom - 2 * Control_height;
		Perimeter.setBounds(0,0,Screen.x,Screen.y);
	}
	
	//Initalizes the buttons and drawing object
	public void InitComponents()
	{
		//Sets min size
		this.setPreferredSize(new Dimension(1000, 800));
		this.setMinimumSize(getPreferredSize());
		delay = 167-50;
		
		m1.setLocation(0,0);
		m2.setLocation(0,0);
		Perimeter.setBounds(0,0,Screen.x, Screen.y);
		Perimeter.grow(-1, -1);
		control.setBackground(Color.lightGray);
		
		bRun = new Button("RUN");
		bPause = new Button("PAUSE");
		bQuit = new Button("QUIT");
		speed = new Scrollbar(Scrollbar.HORIZONTAL, 50, 20, 10, 120);
		size = new Scrollbar(Scrollbar.HORIZONTAL, 50, 20, 10, 120);	
		spl = new Label("Speed:  " + String.valueOf(speed.getValue()));
		sil = new Label("Size:  " + String.valueOf(size.getValue()));
		Obj = new ObjC(50, Screen.x, Screen.y);
		
		speed.setBackground(Color.darkGray);
		size.setBackground(Color.darkGray);
		Obj.setBackground(Color.white);
		
		bRun.addActionListener(this);
		bPause.addActionListener(this);
		bQuit.addActionListener(this);
		speed.addAdjustmentListener(this);
		size.addAdjustmentListener(this);
		Obj.addMouseMotionListener(this);
		Obj.addMouseListener(this);

		
		
	}

	//Creates a new thread to start the program if one doesn't exist already 
	public void Start()
	{
		if(thr == null)
		{
			thr = new Thread(this);
			thr.start();
			Obj.repaint();
		}
	}
	
	//Stops the thread and removes all listeners used for the program
	public void stop()
	{
			TimePause = true;
			ThFlag = false;
			Thread.currentThread().setPriority(Thread.MIN_PRIORITY);
			this.removeWindowListener(this);
			this.removeComponentListener(this);
			bRun.removeActionListener(this);
			bPause.removeActionListener(this);
			bQuit.removeActionListener(this);
			speed.removeAdjustmentListener(this);
			size.removeAdjustmentListener(this);
			Obj.removeMouseMotionListener(this);
			Obj.removeMouseListener(this);
			this.dispose();
	}
	
    //When a button is pressed
    public void actionPerformed(ActionEvent e)
	{
			Object source = e.getSource();
            
			//Button that starts the program
			if(source == bRun)
			{
				TimePause = !TimePause;
				bRun.setEnabled(false);
				bPause.setEnabled(true);	
			}
            
			//Button that clears the screen
			else if(source==bPause)
			{
				TimePause = !TimePause;
				bPause.setEnabled(false);
				bRun.setEnabled(true);
			}
			
			//Button that quits the program
			else if(source==bQuit)
			{
				stop();
			}
    }
    
	//Calls stop to end the program
    public void windowClosing(WindowEvent e)
	{
		stop();
	}

	public void windowClosed(WindowEvent e)
	{
	}
	
	public void windowOpened(WindowEvent e)
	{
	}

	public void windowActivated(WindowEvent e)
	{
	}
	
	public void windowDeactivated(WindowEvent e)
	{
	}
	
	public void windowIconified(WindowEvent e)
	{
	}
	
	public void windowDeiconified(WindowEvent e)
	{
	}
    
	//Adjustment value listeners for speed and size
	public void adjustmentValueChanged(AdjustmentEvent e)
	{
		Object o = e.getSource();
		int tymin, tymax, txmin, txmax, x, y, i, TS, n;
		
		//Sends the appropriate values to the speed modifier for the object (10-100)
		if(o == speed)
		{
			Obj.setSpeed(speed.getValue());
			delay = 167-speed.getValue();
			bb_sp = speed.getValue();
			spl.setText("Speed:  " + String.valueOf(speed.getValue()));
		}
		
		//Sends the appropriate value to the size modifier for the object (10-100)
		else if(o == size)
		{
			i = 0;		
			ok_size = true;
			Rectangle t;
			temp_b.setBounds(Obj.getx()-1, Obj.gety()-1, size.getValue()+2, size.getValue()+2);
			
			if(temp_b.equals(Perimeter.intersection(temp_b)))
			{
				ok_size = true;
			}
			while((i<Obj.getWallSize())&&ok_size)
			{
				t = Obj.getOne(i);
				
				if(t.intersects(temp_b))
				{
					ok_size = false;
				}
				else
				{
					ok_size = true;
					i++;
				}
			}
			
			if(ok_size)
			{
				old_sobj = size.getValue();
				Obj.update(size.getValue());
				sil.setText("Size:  " + String.valueOf(size.getValue()));
			}
			
			else if(!ok_size)
			{
				size.setValue(old_sobj);
			}
		}
		
		Obj.repaint();
	}
	
    //Updates the positions and sizes of components when the screen size has changed
	public void componentResized(ComponentEvent e)
	{
		FrameSize.x = this.getWidth();
		FrameSize.y = this.getHeight();
		MakeSheet();
		Obj.reSize(Screen.x, Screen.y);
	}

	public void componentHidden(ComponentEvent e){}
	public void componentShown(ComponentEvent e){}
	public void componentMoved(ComponentEvent e){}
	
	//Runs the thread that will be looped until the user quits the program
	public void run()
	{
		while(ThFlag)
		{
			Thread.currentThread().setPriority(Thread.MAX_PRIORITY);
			while(!TimePause)
			{
				Obj.Step();
				try
				{
					Thread.sleep(delay);
				}
				catch (InterruptedException ex){}

				Obj.repaint();
				ballCheck();
				Obj.move();
			}
		}
	}
	
	//Initializes the drag box that will be tested and eventually stored in the vector
	public Rectangle getDragBox()
	{
		int tempWidth = 0;
		int tempHeight = 0;
		int tempX = 0;
		int tempY = 0;
		
		tempX = (int)Math.min(m1.getX(), m2.getX());
		tempY = (int)Math.min(m1.getY(), m2.getY());
		
		tempWidth = ((int)Math.max(m1.getX(), m2.getX()) - tempX);
		tempHeight = ((int)Math.max(m1.getY(), m2.getY()) - tempY);
		
		drag_box.setBounds(tempX, tempY, tempWidth, tempHeight);
		
		return drag_box;
		
	}
	
	//Checks collisions against rectangles placed by the user
	public void ballCheck()
	{
		Rectangle r = new Rectangle(ZERO);
		temp_b.setBounds(Obj.getx()-2, Obj.gety()-2, size.getValue()+4, size.getValue()+4);
		temp_b.grow(1,1);
		int i = 0;
		ok_bounce = true;
		Rectangle temp;

		
		while((i<Obj.getWallSize())&&ok_bounce)
		{
			r = Obj.getOne(i);
			if(r.intersects(temp_b))
			{	
				ok_bounce = false;
			}
				
			else
				i++;
		}
		
		if(!ok_bounce)
        {
			temp = r.intersection(temp_b);
			
			if (temp.height <= temp.width)
			{
				Obj.downSwitch();
			}
			
			else if (temp.width <= temp.height)
			{
				Obj.rightSwitch();
			}
			
			else if (temp.width == temp.height)
			{
				Obj.rightSwitch();
			}
		
			else
			{
				System.out.print("false ");
			}
		}
	}
	
	//Saves the point where the mouse was first pressed
	public void mousePressed(MouseEvent e)
	{ 
		m1.setLocation(e.getPoint());
	}
	
	//Checks the drag box to see if it is on the screen, not covering the ball,
	//and to make sure it deletes rectangles completley covered
	public void mouseReleased(MouseEvent e)
    {
        Boolean flag = true;
        Rectangle rTemp = new Rectangle();
        temp_b.setBounds(Obj.getx()-1, Obj.gety()-1, size.getValue()+2, size.getValue()+2);
        
        if(drag_box.intersects(temp_b))
		{
            flag = false;
        }
		
        else if(!Perimeter.contains(drag_box))
		{
            flag = false;
        }
        
        int x = 0;
        while(x < Obj.getWallSize())
		{
            rTemp = Obj.getOne(x);
            
            if(rTemp.contains(drag_box))
			{
                flag = false;
            }
			
            if(drag_box.contains(rTemp))
			{
                Obj.removeOne(x);
            }
            else if (!drag_box.contains(rTemp))
			{
				x++;
			}
		}
		
		if(flag == true)
		{
			Obj.addOne(drag_box);
			Obj.repaint();
		}
		else if(flag == false)
		{
            Obj.setDragBox(ZERO, m1.getLocation(), m2.getLocation());
            Obj.repaint();
        }         
    }
	
	//Removes rectangles from the vectore when a rectangle is clicked on
	public void mouseClicked(MouseEvent e)
	{
        Rectangle recTemp = new Rectangle();
        pTemp.setLocation(e.getPoint());
        int i = 0;
		while(i < Obj.getWallSize())
		{
            recTemp = Obj.getOne(i);

            if(recTemp.contains(pTemp))
			{
                Obj.removeOne(i);
                Obj.repaint();
			}
			else
			{
				i++;
			}
			
			Obj.repaint();
		}
    }
	
	public void mouseEntered(MouseEvent e){}
	public void mouseExited(MouseEvent e){}

	//Keeps a running point of where your mouse is compared to where you first clicked.
	public void mouseDragged(MouseEvent e)
	{
		m2.setLocation(e.getPoint());
		
		drag_box.setBounds(getDragBox());
		
		if(Perimeter.contains(drag_box))
		{
			Obj.setDragBox(drag_box, m1.getLocation(), m2.getLocation());
			Obj.repaint();
		}
	}
	
	public void mouseMoved(MouseEvent e){}
}

