/*
Program 6
CET 350 Group 2
Kevin Andor Scutaru - AND3256@calu.edu
Matthew Oblock - OBL2109@calu.edu
*/

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.lang.*;
import java.util.*;

public class CannonVSBall extends Frame implements WindowListener, ActionListener, 
AdjustmentListener, ComponentListener, Runnable, MouseListener, MouseMotionListener, ItemListener
{
	//Initialize Variables
	private ObjC Obj;
	private Thread thr;
	private boolean TimePause = true;
	private long sp;
	private long delay;
	private boolean ThFlag = true;
	
	
	private int BallC;
	private int PlayerC;
	private static Label lTime;
    private static Label lBall;
    private static Label lPlayer;
    private static Scrollbar velocity;
	private static Scrollbar angle;
	private static Label vel;
	private static Label anl;
	private static Label message = new Label("Test");
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
	private int cur_sobj = 50;
	private	int old_sobj = cur_sobj;
	private int bb_sp;
	private static Point m1 = new Point(0,0);
	private static Point m2 = new Point(0,0);
	private Rectangle drag_box = new Rectangle();
	private static final Rectangle ZERO = new Rectangle(0, 0, 0, 0);
	private static boolean ok_size = true;
	private static boolean ok_bounce = true;
	private static Point pTemp = new Point(0,0);
	private Rectangle hitBox = new Rectangle();
	
	private MenuBar MMB;
	private Menu CONTROL,PARAMETERS, ENVIRONMENT;
	private MenuItem PAUSE, RUN, RESTART, QUIT;
	private Menu SIZE, SPEED;
	private CheckboxMenuItem X_SMALL, SMALL, MEDIUM, LARGE, X_LARGE;
	private CheckboxMenuItem SLOWEST, SLOW, NORMAL , FAST, FASTEST;
	private CheckboxMenuItem Mercury, Venus, Earth,
	Moon, Mars, Jupiter, Saturn, Uranus, Neptune, Pluto;
	
	private Polygon barrel = new Polygon();
    private int barrelWidth = 30;
    private int barrelLength = 300;
	
    private Point a = new Point();
    private Point a1 = new Point();
	private Point a2 = new Point();
//	private Point b = new Point(a.x-100, Screen.y-5);
    private Point c = new Point(/*Screen.x+5, Screen.y + 5*/);
    private Point c1 = new Point();
    private Point c2 = new Point();
	private double gravity = 9.807;
	
	private int cx;
    private int cy;
	private double x1;
    private double x2;
    private double y1;
    private double y2;
	private int a1x;
	private int a1y;
	private int a2x;
	private int a2y;
	private int c1x;
	private int c1y;
	private int c2x;
	private int c2y;
	
	private double V0;
	private double V0x;
	private double V0y;
	private int pro_x;
	private int pro_y;
	private double Vy;
	private double t;
	private double dt = 1;
	private int dx;
	private int dy;
	private double dVy;
	
	//The main
	public static void main (String[] args) throws IOException
	{    
        new CannonVSBall();   
    }
	
	//BouncingBall class
    public CannonVSBall(){
		
        //Sets frame properties
        this.setResizable(true);
        this.addWindowListener(this);
		this.setBackground(Color.white);
        this.setLayout(new BorderLayout());
		this.setBounds(10,20,FrameSize.x, FrameSize.y);
		
		
		//Sets up the menu bar and it's items
		MMB = new MenuBar();
		CONTROL = new Menu("Control");
		PARAMETERS = new Menu("Parameters");
		ENVIRONMENT = new Menu("Environment");
		
		//Control menu & items
		PAUSE = CONTROL.add(new MenuItem("Pause", new MenuShortcut(KeyEvent.VK_P)));
		RUN = CONTROL.add(new MenuItem("Run", new MenuShortcut(KeyEvent.VK_R)));
		
		MMB.add(CONTROL);
		CONTROL.addSeparator();
		RESTART = CONTROL.add(new MenuItem("Restart"));
		MMB.add(CONTROL);
		CONTROL.addSeparator();
		QUIT = CONTROL.add(new MenuItem("Quit", new MenuShortcut(KeyEvent.VK_Q)));
		MMB.add(CONTROL);
		
		//Parameters menu & items
		SIZE = new Menu("Size");
		SPEED = new Menu("Speed ");
		
		SIZE.add(X_SMALL = new CheckboxMenuItem("X-Small"));
		SIZE.add(SMALL = new CheckboxMenuItem("Small"));
		SIZE.add(MEDIUM = new CheckboxMenuItem("Medium"));
		SIZE.add(LARGE = new CheckboxMenuItem("Large"));
		SIZE.add(X_LARGE = new CheckboxMenuItem("X-Large"));
		
		SPEED.add(SLOWEST = new CheckboxMenuItem("Slowest"));
		SPEED.add(SLOW = new CheckboxMenuItem("Slow"));
		SPEED.add(NORMAL = new CheckboxMenuItem("Normal"));
		SPEED.add(FAST = new CheckboxMenuItem("Fast"));
		SPEED.add(FASTEST = new CheckboxMenuItem("Fastest"));
		
		PARAMETERS.add(SIZE);
		PARAMETERS.add(SPEED);
		MMB.add(PARAMETERS);
		
		
		//Environment menu & items
		ENVIRONMENT.add(Mercury = new CheckboxMenuItem("Mercury"));
		ENVIRONMENT.add(Venus = new CheckboxMenuItem("Venus"));
		ENVIRONMENT.add(Earth = new CheckboxMenuItem("Earth"));
		ENVIRONMENT.add(Moon = new CheckboxMenuItem("Moon"));
		ENVIRONMENT.add(Mars = new CheckboxMenuItem("Mars"));
		ENVIRONMENT.add(Jupiter = new CheckboxMenuItem("Jupiter"));
		ENVIRONMENT.add(Saturn = new CheckboxMenuItem("Saturn"));
		ENVIRONMENT.add(Uranus = new CheckboxMenuItem("Uranus"));
		ENVIRONMENT.add(Neptune = new CheckboxMenuItem("Neptune"));
		ENVIRONMENT.add(Pluto = new CheckboxMenuItem("Pluto"));
		
		MMB.add(ENVIRONMENT);
		
		//Applies menu bar to frame
		this.setMenuBar(MMB);
		NORMAL.setState(true);
		MEDIUM.setState(true);
		Earth.setState(true);
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
			


		//Speed Scrollbar	
		velocity.setBounds(0,0,120,20);
		c.gridwidth = 2;
		c.gridheight = 1;
		c.fill = GridBagConstraints.BOTH;
		c.gridy = 2;
		c.gridx = 1;
		displ.setConstraints(velocity, c);
	
		//Size Scrollbar
		angle.setBounds(0,0,120,20);
		c.gridx = 18;
		displ.setConstraints(angle, c);
		
		
//Labels

		//Speed
		vel.setBounds(0,0,60,30);
		c.gridwidth = 1;
		c.gridheight = 1;
		c.fill = GridBagConstraints.BOTH;
		c.gridy = 3;
		c.gridx = 2;
		displ.setConstraints(vel, c);
		
		//Size	
		anl.setBounds(0,0,60,30);
		c.gridx = 19;
		displ.setConstraints(anl, c);
		
		//Time
		lTime.setBounds(0,0,60,30);
		c.gridwidth = 1;
		c.gridheight = 1;
		c.fill = GridBagConstraints.BOTH;
		c.gridx = 9;
		displ.setConstraints(lTime, c);
		
		//Ball tally
		lBall.setBounds(0,0,60,30);
		c.gridx = 10;
		displ.setConstraints(lBall, c);
		
		//Player tally
		lPlayer.setBounds(0, 0, 60, 30);
		c.gridx = 11;
		displ.setConstraints(lPlayer, c);
		
		Win_width = this.getWidth();
		Win_height = this.getHeight();
		
		//Message
		message.setBounds(0,0,60,30);
		c.gridy = 2;
		c.gridx = 10;
		displ.setConstraints(message, c);
	
		//Adds components to screen
		this.add("Center", sheet);
		this.add("South", control);
		this.validate();
		
		control.add(velocity);
		control.add(lTime);
		control.add(lBall);
		control.add(lPlayer);
		control.add(angle);
		control.add(vel);
		control.add(anl);
		control.add(message);
		sheet.add("Center", Obj);

		X_SMALL.addItemListener(this);
		SMALL.addItemListener(this);
		MEDIUM.addItemListener(this);
		LARGE.addItemListener(this);
		X_LARGE.addItemListener(this);
		
		SLOWEST.addItemListener(this);
		SLOW.addItemListener(this);
		NORMAL.addItemListener(this);
		FAST.addItemListener(this);
		FASTEST.addItemListener(this);
		
		Earth.addItemListener(this);
		Moon.addItemListener(this);
		Mercury.addItemListener(this);
		Venus.addItemListener(this);
		Mars.addItemListener(this);
		Jupiter.addItemListener(this);
		Saturn.addItemListener(this);
		Uranus.addItemListener(this);
		Neptune.addItemListener(this);
		Pluto.addItemListener(this);
		
		RUN.addActionListener(this);
		PAUSE.addActionListener(this);
		RESTART.addActionListener(this);
		QUIT.addActionListener(this);
		
		Start();
		initAngle();
		Obj.setSpeed(48);
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
		a.setLocation(Screen.x-20, Screen.y-20);
		Perimeter.setBounds(0,0,Screen.x,Screen.y);
	}
	
	//Initalizes the buttons and drawing object
	public void InitComponents()
	{
		//Sets min size
		this.setPreferredSize(new Dimension(1000, 800));
		this.setMinimumSize(getPreferredSize());
		delay = 167-48;

		
		
		m1.setLocation(0,0);
		m2.setLocation(0,0);
		Perimeter.setBounds(0,0,Screen.x, Screen.y);
		Perimeter.grow(-1, -1);
		control.setBackground(Color.lightGray);
		
		lTime = new Label("Time: ");
		lBall = new Label("Ball: ");
		lPlayer = new Label("Player: ");
		velocity = new Scrollbar(Scrollbar.HORIZONTAL, 20, 20, 20, 75);
		angle = new Scrollbar(Scrollbar.HORIZONTAL, 45, 20, 0, 110);	
		vel = new Label("Velocity:  " + String.valueOf(velocity.getValue()));
		anl = new Label("Angle:  " + String.valueOf(angle.getValue()));
		Obj = new ObjC(50, Screen.x, Screen.y);
		
		velocity.setBackground(Color.darkGray);
		angle.setBackground(Color.darkGray);
		Obj.setBackground(Color.white);
		

		velocity.addAdjustmentListener(this);
		angle.addAdjustmentListener(this);
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
			RUN.removeActionListener(this);
			PAUSE.removeActionListener(this);
			QUIT.removeActionListener(this);
			RESTART.removeActionListener(this);
			SLOWEST.removeItemListener(this);
			SLOW.removeItemListener(this);
			NORMAL.removeItemListener(this);
			FAST.removeItemListener(this);
			FASTEST.removeItemListener(this);
			
			X_SMALL.removeItemListener(this);
			SMALL.removeItemListener(this);
			MEDIUM.removeItemListener(this);
			LARGE.removeItemListener(this);
			X_LARGE.removeItemListener(this);
			
			Earth.removeItemListener(this);
			Moon.removeItemListener(this);
			Mercury.removeItemListener(this);
			Venus.removeItemListener(this);
			Mars.removeItemListener(this);
			Jupiter.removeItemListener(this);
			Saturn.removeItemListener(this);
			Uranus.removeItemListener(this);
			Neptune.removeItemListener(this);
			Pluto.removeItemListener(this);
			velocity.removeAdjustmentListener(this);
			angle.removeAdjustmentListener(this);
			Obj.removeMouseMotionListener(this);
			Obj.removeMouseListener(this);
			this.dispose();
	}
	
    //When a button is pressed
    public void actionPerformed(ActionEvent e)
	{
			Object source = e.getSource();
            
			//Button that starts the program
			if(source == RUN)
			{
				TimePause = !TimePause;
			}
            
			//Button that clears the screen
			else if(source==PAUSE)
			{
				TimePause = !TimePause;
			}
			
/*			else if(source == RESTART)
			{
				this.dispose();
				new BouncingBall();
			}*/
			//Button that quits the program
			else if(source==QUIT)
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
    
	//Adjustment value listeners for velocity and angle
	public void adjustmentValueChanged(AdjustmentEvent e)
    {
        Object o = e.getSource();
        
        
        if(o == angle)
        {
            double theta = Math.toRadians(angle.getValue());
            
            x1 = (barrelWidth/2) * Math.cos(theta);
            y1 = (barrelWidth/2) * Math.sin(theta);
            
           // a1x = a.y - x1;
           // a1y = a.x - y1;
            
			/*a1x = 78;
			a1y = 178;*/
			
			x2 = x1;
            y2 = y1;
            
            a1x = (int)(a.x - y1);
            a1y = (int)(a.y + x1);
            a1.setLocation(a1x, a1y);
            
            a2x = (int)(a.x + y2);
            a2y = (int)(a.y - x2);
            a2.setLocation(a2x, a2y);
			
			cx = a.x - (int)(barrelLength * Math.cos(theta));
            cy = a.y - (int)(barrelLength * Math.sin(theta));
            c.setLocation(cx, cy);
            
			c1x = (int)(c.x + y2);
            c1y = (int)(c.y - x2);
            c1.setLocation(c1x, c1y);
			
            c2x = (int)(c.x - y1);
            c2y = (int)(c.y + x2);
            c2.setLocation(c2x, c2y);
            
			Obj.testLine(a, c);
            
			Obj.updateBarrel(a1, a2, c1, c2);
            anl.setText("Angle:  " + String.valueOf(angle.getValue()));
        }
		
		
		//Sets the velocity
		if(o == velocity)
		{
			double theta = Math.toRadians(angle.getValue());
			V0 = velocity.getValue();
			
			V0x = V0 * Math.cos(theta);
			V0y = V0 * Math.sin(theta);
			t = V0y/gravity;
			
			//distance x
			pro_x = c.x -(int)((.5)*V0x*t);
			
			//distance y
			pro_y = c.y + (int)((.5)*V0y*t-gravity*(t*t));

	
			//velocity y
			Vy = V0y - gravity * t;
			
			dx = (int)((.5)*V0x*dt);
			dy = (int)((.5)*Vy*dt-gravity*(dt*dt));
			
//			Obj.setProMovement(pro_x, pro_y, dx, dy);
			vel.setText("Velocity: " + String.valueOf(velocity.getValue()));
		}
        
    }
	
	public void initAngle()
	{
		double theta = Math.toRadians(angle.getValue());
            
            x1 = (barrelWidth/2) * Math.cos(theta);
            y1 = (barrelWidth/2) * Math.sin(theta);
            
           // a1x = a.y - x1;
           // a1y = a.x - y1;
            
			/*a1x = 78;
			a1y = 178;*/
			
			x2 = x1;
            y2 = y1;
            
            a1x = (int)(a.x - y1);
            a1y = (int)(a.y + x1);
            a1.setLocation(a1x, a1y);
            
            a2x = (int)(a.x + y2);
            a2y = (int)(a.y - x2);
            a2.setLocation(a2x, a2y);
			
			cx = a.x - (int)(barrelLength * Math.cos(theta));
            cy = a.y - (int)(barrelLength * Math.sin(theta));
            c.setLocation(cx, cy);
            
			c1x = (int)(c.x + y2);
            c1y = (int)(c.y - x2);
            c1.setLocation(c1x, c1y);
			
            c2x = (int)(c.x - y1);
            c2y = (int)(c.y + x2);
            c2.setLocation(c2x, c2y);
            
			Obj.testLine(a, c);
            
			Obj.updateBarrel(a1, a2, c1, c2);
            anl.setText("Angle:  " + String.valueOf(angle.getValue()));
	}
	
    //Updates the positions and sizes of components when the screen size has changed
	public void componentResized(ComponentEvent e)
	{
		FrameSize.x = this.getWidth();
		FrameSize.y = this.getHeight();
		MakeSheet();
		initAngle();
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
		Rectangle canon = new Rectangle();
		temp_b.setBounds(Obj.getx()-2, Obj.gety()-2, cur_sobj+4, cur_sobj+4);
		temp_b.grow(1,1);
		int i = 0;
		ok_bounce = true;
		boolean rects = true;
		boolean cannon = false;
		
		Rectangle temp = r;
		canon.setBounds(Screen.x - 150, Screen.y - 150, 300, 300);
		
        if(canon.intersects(temp_b))
        {
			rects = false;
			cannon = true;
			BallC = BallC+1;
            lBall.setText("Ball: "+ Integer.toString(BallC));
			ok_bounce = false;
        }
		
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
			if(rects)
				temp = r.intersection(temp_b);
			
			if(cannon)
				temp = canon.intersection(temp_b);
			
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
        temp_b.setBounds(Obj.getx()-1, Obj.gety()-1, cur_sobj+2, cur_sobj+2);
        
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
		Rectangle canon = new Rectangle();
		
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
		canon.setBounds(Screen.x - 150, Screen.y - 150, 300, 300);
        
        if(canon.contains(pTemp))
        {
            Obj.setProMovement(pro_x, pro_y, dx, dy);
        }
		
    }
	public void setMessage()
	{
		message.setText("Projectile will not be returning to the screen");
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
	
	//Changes values based on the items selected in menu
	public void itemStateChanged(ItemEvent e)
	{
		
		//Checks the Size checkboxes
		CheckboxMenuItem checkbox = (CheckboxMenuItem)e.getSource();
		if(checkbox == X_SMALL || checkbox == SMALL || checkbox == MEDIUM || checkbox == LARGE || checkbox == X_LARGE)
		{
			X_SMALL.setState(false);
			SMALL.setState(false);
			MEDIUM.setState(false);
			LARGE.setState(false);
			X_LARGE.setState(false);
			checkbox.setState(true);
		}
		
		//Checks the Speed checkboxes
		if(checkbox == SLOWEST || checkbox == SLOW || checkbox == NORMAL || checkbox == FAST || checkbox == FASTEST)
		{
			SLOWEST.setState(false);
			SLOW.setState(false);
			NORMAL.setState(false);
			FAST.setState(false);
			FASTEST.setState(false);
			checkbox.setState(true);
		}
		
		//Checks the environment checkboxes
		if(checkbox == Mercury)
		{	
			Mercury.setState(false);
			Venus.setState(false);
			Mars.setState(false);
			Jupiter.setState(false);
			Saturn.setState(false);
			Uranus.setState(false);
			Neptune.setState(false);
			Pluto.setState(false);
			Earth.setState(false);
			Moon.setState(false);
			checkbox.setState(true);
			gravity = 3.7;
		}

		if(checkbox == Venus)
		{	
			Mercury.setState(false);
			Venus.setState(false);
			Mars.setState(false);
			Jupiter.setState(false);
			Saturn.setState(false);
			Uranus.setState(false);
			Neptune.setState(false);
			Pluto.setState(false);
			Earth.setState(false);
			Moon.setState(false);
			checkbox.setState(true);
			gravity = 8.87;
		}	
		
		if(checkbox == Mars)
		{	
			Mercury.setState(false);
			Venus.setState(false);
			Mars.setState(false);
			Jupiter.setState(false);
			Saturn.setState(false);
			Uranus.setState(false);
			Neptune.setState(false);
			Pluto.setState(false);
			Earth.setState(false);
			Moon.setState(false);
			checkbox.setState(true);
			gravity = 3.711;
		}	
		
		if(checkbox == Jupiter)
		{	
			Mercury.setState(false);
			Venus.setState(false);
			Mars.setState(false);
			Jupiter.setState(false);
			Saturn.setState(false);
			Uranus.setState(false);
			Neptune.setState(false);
			Pluto.setState(false);
			Earth.setState(false);
			Moon.setState(false);
			checkbox.setState(true);
			gravity = 24.79;
		}	
		
		if(checkbox == Saturn)
		{	
			Mercury.setState(false);
			Venus.setState(false);
			Mars.setState(false);
			Jupiter.setState(false);
			Saturn.setState(false);
			Uranus.setState(false);
			Neptune.setState(false);
			Pluto.setState(false);
			Earth.setState(false);
			Moon.setState(false);
			checkbox.setState(true);
			gravity = 10.44;
		}	
		
		if(checkbox == Uranus)
		{	
			Mercury.setState(false);
			Venus.setState(false);
			Mars.setState(false);
			Jupiter.setState(false);
			Saturn.setState(false);
			Uranus.setState(false);
			Neptune.setState(false);
			Pluto.setState(false);
			Earth.setState(false);
			Moon.setState(false);
			checkbox.setState(true);
			gravity = 8.87;
		}	
		
		if(checkbox == Neptune)
		{	
			Mercury.setState(false);
			Venus.setState(false);
			Mars.setState(false);
			Jupiter.setState(false);
			Saturn.setState(false);
			Uranus.setState(false);
			Neptune.setState(false);
			Pluto.setState(false);
			Earth.setState(false);
			Moon.setState(false);
			checkbox.setState(true);
			gravity = 11.15;
		}	
		
		if(checkbox == Pluto)
		{	
			Mercury.setState(false);
			Venus.setState(false);
			Mars.setState(false);
			Jupiter.setState(false);
			Saturn.setState(false);
			Uranus.setState(false);
			Neptune.setState(false);
			Pluto.setState(false);
			Earth.setState(false);
			Moon.setState(false);
			checkbox.setState(true);
			gravity = 0.62;
		}	
		
		if(checkbox == Earth)
		{	
			Mercury.setState(false);
			Venus.setState(false);
			Mars.setState(false);
			Jupiter.setState(false);
			Saturn.setState(false);
			Uranus.setState(false);
			Neptune.setState(false);
			Pluto.setState(false);
			Earth.setState(false);
			Moon.setState(false);
			checkbox.setState(true);
			gravity = 9.807;
		}	
		
		if(checkbox == Moon)
		{	
			Mercury.setState(false);
			Venus.setState(false);
			Mars.setState(false);
			Jupiter.setState(false);
			Saturn.setState(false);
			Uranus.setState(false);
			Neptune.setState(false);
			Pluto.setState(false);
			Earth.setState(false);
			Moon.setState(false);
			checkbox.setState(true);
			gravity = 1.62;
		}	
		
		setTheParameters();
		
	}
	
	public void setTheParameters()
	{
		if(SLOWEST.getState())
		{
			Obj.setSpeed(16);
			delay = 167-16;
			bb_sp = 16;
		}
		
		if(SLOW.getState())
		{
			Obj.setSpeed(32);
			delay = 167-32;
			bb_sp = 32;
		}
		
		if(NORMAL.getState())
		{
			Obj.setSpeed(48);
			delay = 167-48;
			bb_sp = 48;
		}
		
		if(FAST.getState())
		{
			Obj.setSpeed(64);
			delay = 167-64;
			bb_sp = 64;
		}
		
		if(FASTEST.getState())
		{
			Obj.setSpeed(80);
			delay = 167-80;
			bb_sp = 80;
		}
		
		
		
		if(X_SMALL.getState())
		{
			int i = 0;		
			ok_size = true;
			Rectangle t;
			cur_sobj = 10;
			temp_b.setBounds(Obj.getx()-1, Obj.gety()-1, cur_sobj+2, cur_sobj+2);
			
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
				old_sobj = cur_sobj;
				Obj.update(cur_sobj);
			}
			
			else if(!ok_size)
			{
				X_SMALL.setState(false);
				SMALL.setState(false);
				MEDIUM.setState(false);
				LARGE.setState(false);
				X_LARGE.setState(false);
				
				if(old_sobj == 10)
					X_SMALL.setState(true);
				else if(old_sobj == 25)
					SMALL.setState(true);
				else if(old_sobj == 50)
					MEDIUM.setState(true);
				else if(old_sobj == 75)
					LARGE.setState(true);
				else if(old_sobj == 100)
					X_LARGE.setState(true);
			}
		}
		if(SMALL.getState())
		{
			int i = 0;		
			ok_size = true;
			Rectangle t;
			cur_sobj = 25;
			temp_b.setBounds(Obj.getx()-1, Obj.gety()-1, cur_sobj+2, cur_sobj+2);
			
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
				old_sobj = cur_sobj;
				Obj.update(cur_sobj);
			}
			
			else if(!ok_size)
			{
				X_SMALL.setState(false);
				SMALL.setState(false);
				MEDIUM.setState(false);
				LARGE.setState(false);
				X_LARGE.setState(false);
				
				if(old_sobj == 10)
					X_SMALL.setState(true);
				else if(old_sobj == 25)
					SMALL.setState(true);
				else if(old_sobj == 50)
					MEDIUM.setState(true);
				else if(old_sobj == 75)
					LARGE.setState(true);
				else if(old_sobj == 100)
					X_LARGE.setState(true);
			}
		}
		
		if(MEDIUM.getState())
		{
			int i = 0;		
			ok_size = true;
			Rectangle t;
			cur_sobj = 50;
			temp_b.setBounds(Obj.getx()-1, Obj.gety()-1, cur_sobj+2, cur_sobj+2);
			
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
				old_sobj = cur_sobj;
				Obj.update(cur_sobj);
			}
			
			else if(!ok_size)
			{
				X_SMALL.setState(false);
				SMALL.setState(false);
				MEDIUM.setState(false);
				LARGE.setState(false);
				X_LARGE.setState(false);
				
				if(old_sobj == 10)
					X_SMALL.setState(true);
				else if(old_sobj == 25)
					SMALL.setState(true);
				else if(old_sobj == 50)
					MEDIUM.setState(true);
				else if(old_sobj == 75)
					LARGE.setState(true);
				else if(old_sobj == 100)
					X_LARGE.setState(true);
			}
		}
		
		if(LARGE.getState())
		{
			int i = 0;		
			ok_size = true;
			Rectangle t;
			cur_sobj = 75;
			temp_b.setBounds(Obj.getx()-1, Obj.gety()-1, cur_sobj+2, cur_sobj+2);
			
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
				old_sobj = cur_sobj;
				Obj.update(cur_sobj);
			}
			
			else if(!ok_size)
			{
				X_SMALL.setState(false);
				SMALL.setState(false);
				MEDIUM.setState(false);
				LARGE.setState(false);
				X_LARGE.setState(false);
				
				if(old_sobj == 10)
					X_SMALL.setState(true);
				else if(old_sobj == 25)
					SMALL.setState(true);
				else if(old_sobj == 50)
					MEDIUM.setState(true);
				else if(old_sobj == 75)
					LARGE.setState(true);
				else if(old_sobj == 100)
					X_LARGE.setState(true);
			}
		}
		
		
		if(X_LARGE.getState())
		{
			int i = 0;		
			ok_size = true;
			Rectangle t;
			cur_sobj = 100;
			temp_b.setBounds(Obj.getx()-1, Obj.gety()-1, cur_sobj+2, cur_sobj+2);
			
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
				old_sobj = cur_sobj;
				Obj.update(cur_sobj);
			}
			
			else if(!ok_size)
			{
				X_SMALL.setState(false);
				SMALL.setState(false);
				MEDIUM.setState(false);
				LARGE.setState(false);
				X_LARGE.setState(false);
				
				if(old_sobj == 10)
					X_SMALL.setState(true);
				else if(old_sobj == 25)
					SMALL.setState(true);
				else if(old_sobj == 50)
					MEDIUM.setState(true);
				else if(old_sobj == 75)
					LARGE.setState(true);
				else if(old_sobj == 100)
					X_LARGE.setState(true);
			}
		}
		
		
		
		
		
	}
}


