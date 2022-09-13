import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.lang.*;
import java.util.*;

public class KK_List implements WindowListener, ActionListener, ItemListener
{
	private int Window_h = 600;
	private int Window_w = 800;
	private Frame Main_Window;
	private MenuBar menu;
	private Menu FILE;
	private MenuItem NEW, SAVE;
	private MenuItem QUIT;
//	private CheckBox Item;
	private Label count = new Label("Songs owned:");
	private GridBagLayout displ;


	public static void main (String[] args) throws IOException
	{    
		new KK_List();   
	}

public KK_List()
{
	Main_Window = new Frame("ACNH K.K. Song Checklist");
//	Main_Window.setLayout();
	menu = new MenuBar();
	FILE = new Menu("FILE");
	NEW = new MenuItem("New List");
	SAVE = new MenuItem("Save List");
	Main_Window.setBackground(Color.lightGray);
	Main_Window.setForeground(Color.black);

	
	double columnWeight[] = {1,1,1,1,1};
    double rowWeight[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	
	int columnWidth[] = {1,1,1,1,1};
	int rowHeight[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

	displ =  new GridBagLayout();
	GridBagConstraints c = new GridBagConstraints();
	
	displ.rowHeights = rowHeight;
	displ.columnWidths = columnWidth;
		
	displ.rowWeights = rowWeight;
	displ.columnWeights = columnWeight;
	
	c.anchor = GridBagConstraints.WEST;
	
	
/*	try
	{
		BufferedReader in = new BufferedReader(new FileReader("L_DEF"));
		
	}

	catch (FileNotFoundException x)
	{
		System.out.print("Please insert a valid L_DEF file and restart the program!");
	}
*/
	Main_Window.setVisible(true);
	
}
	public void itemStateChanged(ItemEvent e)
	{}
	public void actionPerformed(ActionEvent e)	{}
	public void windowClosing(WindowEvent e){
	Main_Window.removeWindowListener(this);
	Main_Window.dispose();}
	public void windowClosed(WindowEvent e){}
	public void windowOpened(WindowEvent e){}
	public void windowActivated(WindowEvent e){}
	public void windowDeactivated(WindowEvent e){}
	public void windowIconified(WindowEvent e){}
	public void windowDeiconified(WindowEvent e){}
}