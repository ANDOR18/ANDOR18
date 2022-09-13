/*
Program 4
CET 350 Group 2
Kevin Andor Scutaru - AND3256@calu.edu
Matthew Oblock - OBL2109@calu.edu
*/

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.lang.*;
import java.util.*;

public class Bounce extends Frame implements WindowListener, ActionListener, 
AdjustmentListener, ComponentListener, Runnable
{
	//Initialize Variables
	private ObjC Obj;
	private Thread thr;
	private boolean TimePause = true;
	private long sp;
	private long delay;
	private boolean ThFlag = true;
	
	private static Button bRun;
    private static Button bShape;
    private static Button bTail;
    private static Button bClear;
    private static Button bQuit;
    private static Scrollbar speed = new Scrollbar(Scrollbar.HORIZONTAL, 50, 20, 0, 120);;
	private static Scrollbar size = new Scrollbar(Scrollbar.HORIZONTAL, 50, 20, 0, 120);;
	private static Label spl;
	private static Label sil;
	private static Label bln = new Label("");
	private static int spacing_size;
	
	private static int Control_height;
	private static int Control_width;
	private static int Win_height;
	private static int Win_width;
	private static int Screen_height;
	private static int Screen_width;
	private Insets I;
	private static int center;

	
	public static void main (String[] args) throws IOException
	{    
        new Bounce();   
    }
	
    public Bounce(){
        //Sets frame properties
        this.setLocation(10, 20);
        this.setResizable(true);
        this.addWindowListener(this);
		this.setBackground(Color.lightGray);
        this.setLayout(null);
		Win_width = this.getWidth();
		Win_height = this.getHeight();
		
        MakeSheet();
		InitComponents();
		SizeScreen();
		
		//Adds components to screen
		this.add(speed);
		this.add(bRun);
		this.add(bShape);
		this.add(bTail);
		this.add(bClear);
		this.add(bQuit);
		this.add(size);
		this.add(spl);
		this.add(sil);
		this.add(Obj);
		Start();

		this.addComponentListener(this);
		this.setVisible(true);
    }
    
	//Sets the size of the canvas and the controls
	private void MakeSheet()
	{
		Control_height = 80;
		I = getInsets();
		Screen_width = Win_width - I.left - I.right;
		Screen_height = Win_height - I.top - I.bottom - 2 * Control_height;
		this.setSize(Win_width, Win_height);
		center = Screen_width / 2;
		spacing_size =  Win_width/8;
	}
	
	//Initalizes the buttons and drawing object
	public void InitComponents()
	{
		this.setPreferredSize(new Dimension(1000, 800));
		this.setMinimumSize(getPreferredSize());
		delay = 167;

		bRun = new Button("RUN");
		bShape = new Button("CIRCLE");
		bTail = new Button("NO TAIL");
		bClear = new Button("CLEAR");
		bQuit = new Button("QUIT");
		speed = new Scrollbar(Scrollbar.HORIZONTAL, 50, 20, 10, 120);
		size = new Scrollbar(Scrollbar.HORIZONTAL, 50, 20, 10, 120);	
		spl = new Label("Speed:  " + String.valueOf(speed.getValue()));
		sil = new Label("Size:  " + String.valueOf(size.getValue()));
		Obj = new ObjC(50, Screen_width, Screen_height);
		
		speed.setBackground(Color.darkGray);
		size.setBackground(Color.darkGray);
		Obj.setBackground(Color.white);
		
		bRun.addActionListener(this);
		bShape.addActionListener(this);
		bTail.addActionListener(this);
		bClear.addActionListener(this);
		bQuit.addActionListener(this);
		speed.addAdjustmentListener(this);
		size.addAdjustmentListener(this);
		
	}

	//Sets the size and location based on the size of the window
	public void SizeScreen()
	{
		speed.setSize(100,30);
		speed.setLocation(spacing_size-100, Win_height-100);
			
		bRun.setSize(100,30);
		bRun.setLocation(spacing_size*2-100, Win_height-100);
		
		bShape.setSize(100,30);
		bShape.setLocation(spacing_size*3-100, Win_height-100);
		
		bTail.setSize(100,30);
		bTail.setLocation(spacing_size*4-100, Win_height-100);
		
		bClear.setSize(100,30);
		bClear.setLocation(spacing_size*5-100, Win_height-100);
		
		bQuit.setSize(100, 30);
		bQuit.setLocation(spacing_size*6-100, Win_height-100); 
		
		size.setSize(100,30);
		size.setLocation(spacing_size*7-100, Win_height-100);
		
		spl.setSize(70,30);
		spl.setLocation(spacing_size-100, Win_height-50);
		
		sil.setSize(70,30);
		sil.setLocation(spacing_size*7-100, Win_height-50);

		Obj.setBounds(I.left, I.top, Screen_width, Screen_height);

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
			bShape.removeActionListener(this);
			bTail.removeActionListener(this);
			bClear.removeActionListener(this);
			bQuit.removeActionListener(this);
			speed.removeAdjustmentListener(this);
			size.removeAdjustmentListener(this);
			this.dispose();
	}
	
    
    public void actionPerformed(ActionEvent e)
	{
			Object source = e.getSource();
            
			//Button that starts and pauses the program
			if(source == bRun)
			{
				if(bRun.getLabel().equals("RUN"))
				{
					TimePause = !TimePause;
					bRun.setLabel("PAUSE");
				}
				else if(bRun.getLabel().equals("PAUSE"))
				{
					TimePause = !TimePause;
					bRun.setLabel("RUN");
				}
				
			}
            
			//Button that sets if there should be a trail following the shape
            else if(source == bTail)
			{
				Obj.setTail();
				if(Obj.getTail())
				{
					bTail.setLabel("NO TAIL");
				}
				else if(!Obj.getTail())
				{
					bTail.setLabel("TAIL");
				}
			}
            
			
			//Button that clears the screen
			else if(source==bClear)
			{
				Obj.Clear();
				Obj.repaint();
			}
			
			//Button that changes the shape between a square and a circle
			else if(source==bShape)
			{
				Obj.setShape();
				if(Obj.getShape())
				{
					bShape.setLabel("CIRCLE");
				}
				else if(!Obj.getShape())
				{
					bShape.setLabel("SQUARE");
				}
			}
			
			//Button that quits the program
			else if(source==bQuit)
			{
				stop();
			}
    }
    
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
    
	public void adjustmentValueChanged(AdjustmentEvent e)
	{
		Object o = e.getSource();
		int tymin, tymax, txmin, txmax, x, y, i, TS, n;
		
		//Sends the appropriate values to the speed modifier for the object (10-100)
		if(o == speed)
		{
			Obj.setSpeed(speed.getValue());
			spl.setText("Speed:  " + String.valueOf(speed.getValue()));
		}
		
		//Sends the appropriate value to the size modifier for the object (10-100)
		else if(o == size)
		{
			Obj.update(size.getValue());
			sil.setText("Size:  " + String.valueOf(size.getValue()));
		}
	}
	
    //Updates the positions and sizes of components when the screen size has changed
	public void componentResized(ComponentEvent e)
	{
		Win_width = this.getWidth();
		Win_height = this.getHeight();
		MakeSheet();
		Obj.reSize(Screen_width, Screen_height);
		SizeScreen();
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
				Obj.move();
			}
		}
	}
}

