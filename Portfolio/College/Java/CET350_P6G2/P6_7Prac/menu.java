import java.awt.*;
import java.awt.event.*;

public class menu implements ActionListener, WindowListener, ItemListener
{
	private int sw = 650;
	private int sh = 480;
	private Frame EditorFrame;
	private TextArea EditArea;
	private MenuBar MMB;
	private Menu FILE,TEXT;
	private Menu NEW,SIZE,FONT;
	private MenuItem FOLDER,DOCUMENT;
	private MenuItem QUIT;
	private CheckboxMenuItem S10,S14,S18;
	private CheckboxMenuItem TNR,CO;
	private int FontType = Font.PLAIN;
	private String FontStyle = "TimesNewRoman";
	private int FontSize = 14;
	
	
	public static void main(String[] args)
	{
			new menu();
	}
	
	public menu()
	{
		EditArea = new TextArea("", sw-10, sh-10, TextArea.SCROLLBARS_BOTH);
		EditorFrame = new Frame("Editor");
		EditorFrame.setLayout(new BorderLayout(0,0));
		EditorFrame.setBackground(Color.lightGray);
		EditorFrame.setForeground(Color.black);
		EditorFrame.add("Center", EditArea);
		
		//Menu structure is sequential, left - right, top - bottom
		MMB = new MenuBar();
		FILE = new Menu("FILE");
		NEW = new Menu("New");

		FOLDER = NEW.add(new MenuItem("Folder", new MenuShortcut(KeyEvent.VK_F)));
		DOCUMENT = NEW.add(new MenuItem("Document", new MenuShortcut(KeyEvent.VK_D)));
		
		FILE.add(NEW);
		FILE.addSeparator();
		
		QUIT = FILE.add(new MenuItem("Quit", new MenuShortcut(KeyEvent.VK_Q)));
		
		TEXT = new Menu("TEXT");
		SIZE = new Menu("Size");
		FONT = new Menu("Font");
		
		SIZE.add(S10 = new CheckboxMenuItem("10"));
		SIZE.add(S14 = new CheckboxMenuItem("14"));
		SIZE.add(S18 = new CheckboxMenuItem("18"));
		
		S14.setState(true);
		
		TEXT.add(SIZE);
		
		FONT.add(TNR = new CheckboxMenuItem("TimesNewRoman"));
		FONT.add(CO = new CheckboxMenuItem("Courier"));
		
		TNR.setState(true);
		
		TEXT.add(FONT);
		
		MMB.add(FILE);
		MMB.add(TEXT);
		
		DOCUMENT.addActionListener(this);
		FOLDER.addActionListener(this);
		QUIT.addActionListener(this);
		
		S10.addItemListener(this);
		S14.addItemListener(this);
		S18.addItemListener(this);
		TNR.addItemListener(this);
		CO.addItemListener(this);
		
		EditorFrame.setMenuBar(MMB);
		
		EditorFrame.addWindowListener(this);
		EditorFrame.setSize(sw,sh);
		EditorFrame.setResizable(true);
		EditorFrame.setVisible(true);
		EditorFrame.validate();
		
		setTheFont();
		
	}
	
		public void setTheFont()
	{
		FontSize = 10;
		if(S10.getState()==true)
				FontSize = 10;
		if(S14.getState()==true)
				FontSize = 14;
		if(S18.getState()==true)
				FontSize = 18;
			
		FontStyle = "TimesNewRoman";
		if(TNR.getState()==true)
				FontStyle = "TimesNewRoman";
		if(CO.getState()==true)
				FontStyle = "Courier";
		FontType = Font.PLAIN;
		EditArea.setFont(new Font(FontStyle, FontType, FontSize));
	}
	
	public void itemStateChanged(ItemEvent e)
	{
		CheckboxMenuItem checkbox = (CheckboxMenuItem)e.getSource();
		if(checkbox == S10 || checkbox == S14 || checkbox == S18)
		{
				S10.setState(false);
				S14.setState(false);
				S18.setState(false);
				checkbox.setState(true);
		}
		
		if(checkbox == TNR || checkbox == CO)
		{
			TNR.setState(false);
			CO.setState(false);
			checkbox.setState(true);
		}
		
		setTheFont();
		
	}
	
	//actionPerformed handles MenuItems and MenuShortCut keys
	public void actionPerformed(ActionEvent e)
	{
		Object source = e.getSource();
		if(source==FOLDER)
				EditArea.append("\nFolder\n");
		if(source==DOCUMENT)
				EditArea.append("\nDOCUMENT\n");
		if(source==QUIT)
				stop();
		
	}
	
	public void stop()
	{
		DOCUMENT.removeActionListener(this);
		FOLDER.removeActionListener(this);
		QUIT.removeActionListener(this);
		S10.removeItemListener(this);
		S14.removeItemListener(this);
		S18.removeItemListener(this);
		TNR.removeItemListener(this);
		CO.removeItemListener(this);
		EditorFrame.removeWindowListener(this);
		EditorFrame.dispose();
	}
	
	public void windowClosing(WindowEvent e)
	{
		stop();
	}
	
	public void windowClosed(WindowEvent e){}
	public void windowOpened(WindowEvent e){}
	public void windowActivated(WindowEvent e){}
	public void windowDeactivated(WindowEvent e){}
	public void windowIconified(WindowEvent e){}
	public void windowDeiconified(WindowEvent e){}
	
}