/*
Program 7; Chat.java
CET 350 Group 2
Kevin Andor Scutaru - AND3256@calu.edu
Matthew Oblock - OBL2109@calu.edu
*/

import java.awt.*;
import java.awt.event.*;
import java.net.Socket;
import java.net.ServerSocket;
import java.net.InetSocketAddress;
import java.net.SocketTimeoutException;
import java.io.*;


public class Chat implements Runnable, ActionListener, WindowListener
{
	private int Screen_h = 550; //Height of the screen
	private int Screen_w = 800; //Width of the screen
	private Frame ChatWindow; //The frame
	private TextArea ChatLog; //The chat log
	private TextArea StatusLog; //The status message log
	private TextField Message, IAddress, Port; //TextFields for the message, host name, and port number
	private Label HostL = new Label("Host: "); //Host label
	private Label PortL = new Label("Port: "); //Port label
	private Button ChangeHost, ChangePort, Send, StartServer, Connect, Disconnect; //Buttons for Change Host, Change Port, Send, Start Server, Connect, and Disconnect
	private int state = 0; //Stores the state of the program. 0 = Initial State, 1 = Server State, 2 = Client State
	private static int timeout = 1000; //Stores the connection timeout. Can be set manually via command line parameter
	boolean more = true; //Stores the state of the thread
	BufferedReader br; //Stores the BufferedReader
	PrintWriter pw; //Stores the PrintWriter
	protected final static boolean auto_flush = true; //Stores value for flushing the print writer
	private Thread TheThread; //Stores the thread
	private Socket client; //Socket used to connect to a client
	private Socket server; //Socket used to connect to a server
	static ServerSocket listen_socket; //Stores the port number to listen to
	private String hostName = ""; //Stores the host name the user wishes to connect to
	private int DEFAULT_PORT = 44004; //Specifies the default port number
	private int portNumber = DEFAULT_PORT; //Sets the default port number as the port number to be used
	private String inData; //Stores incoming messages
	private String outData; //Stores outgoing messages
	
	
	//main will attempt to set the timeout specified in the command line before opening the chat window
	public static void main(String[] args)
	{
		try{
            timeout = Integer.parseInt(args[0]);
            listen_socket.setSoTimeout(timeout);
        }
        catch(Exception m){}
		new Chat();
	}
	
	//Chat constructor that initalizes the layout of window components, adds listeners, and sets the initial state
	public Chat()
	{
		//Initalizes the chat window
		ChatWindow = new Frame("Chat");
		ChatWindow.setSize(Screen_w, Screen_h);
		ChatWindow.setMinimumSize(new Dimension(Screen_w, Screen_h));
		ChatWindow.setBackground(Color.lightGray);
		
		//Sets layout of the sheet
		double columnWeight[] = {1,1,1,1,1,1,1};
        double rowWeight[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
        int columnWidth[] = {1,1,1,1,1,1,1};
        int rowHeight[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
		GridBagLayout displ = new GridBagLayout();
		GridBagConstraints c = new GridBagConstraints();
		
		displ.rowHeights = rowHeight;
		displ.columnWidths = columnWidth;
		
		displ.rowWeights = rowWeight;
		displ.columnWeights = columnWeight;
		
		c.anchor = GridBagConstraints.WEST;
		
		c.weightx = 1;
		c.weighty = 1;
		
		InitComponents();
		
//TextAreas
		//ChatLog
		ChatLog.setBounds(0,0,1,1);
		c.gridwidth = 7;
		c.gridheight = 15;
		c.fill = GridBagConstraints.BOTH;
		c.gridy = 0;
		c.gridx = 0;
		displ.setConstraints(ChatLog, c);
		ChatWindow.add(ChatLog);
	
		//StatusLog
		StatusLog.setBounds(0,0,1,1);
		c.gridheight = 3;
		c.gridy = 22;
		c.fill = GridBagConstraints.BOTH;
		displ.setConstraints(StatusLog, c);	
		ChatWindow.add(StatusLog);
		

		
//Message row
		//Message field
		Message.setBounds(0,0,1,1);
		c.gridwidth = 6;
		c.gridheight = 1;
		c.fill = GridBagConstraints.BOTH;
		c.gridy = 16;
		displ.setConstraints(Message, c);
		ChatWindow.add(Message);
		
		//Send button
		Send.setBounds(0,0,1,1);
		c.gridwidth = 1;
		c.gridheight = 1;
		c.gridx = 6;
		displ.setConstraints(Send, c);
		ChatWindow.add(Send);
		
//Host row
		//Host label
		HostL.setBounds(0,0,1,1);
		c.gridwidth = 1;
		c.gridheight = 1;
		c.gridy = 17;
		c.gridx = 1;
		displ.setConstraints(HostL, c);
		ChatWindow.add(HostL);
		
		//Address field
		IAddress.setBounds(0,0,1,1);
		c.gridwidth = 3;
		c.gridx = 2;
		displ.setConstraints(IAddress, c);
		ChatWindow.add(IAddress);
		
		//ChangeHost button
		ChangeHost.setBounds(0,0,1,1);
		c.gridwidth = 1;
		c.gridx = 5;
		displ.setConstraints(ChangeHost, c);
		ChatWindow.add(ChangeHost);
		
		//StartServer button
		StartServer.setBounds(0,0,1,1);
		c.gridwidth = 1;
		c.gridx = 6;
		displ.setConstraints(StartServer, c);
		ChatWindow.add(StartServer);
		
//Port row
		//Port label
		PortL.setBounds(0,0,1,1);
		c.gridwidth = 1;
		c.gridheight = 1;
		c.gridy = 18;
		c.gridx = 1;
		displ.setConstraints(PortL, c);
		ChatWindow.add(PortL);
		
		//Port field
		Port.setBounds(0,0,1,1);
		c.gridwidth = 3;
		c.gridx = 2;
		displ.setConstraints(Port, c);
		ChatWindow.add(Port);
		
		//ChangePort button
		ChangePort.setBounds(0,0,1,1);
		c.gridwidth = 1;
		c.gridx = 5;
		displ.setConstraints(ChangePort, c);
		ChatWindow.add(ChangePort);
		
		//Connect button
		Connect.setBounds(0,0,1,1);
		c.gridwidth = 1;
		c.gridx = 6;
		displ.setConstraints(Connect, c);
		ChatWindow.add(Connect);
		
//Disconnect
		Disconnect.setBounds(0,0,1,1);
		c.gridy = 19;
		c.gridwidth = 1;
		c.gridx = 6;
		displ.setConstraints(Disconnect, c);
		ChatWindow.add(Disconnect);
		
	//Initalizes Listeners
		Message.addActionListener(this);
		IAddress.addActionListener(this);
		Port.addActionListener(this);
		ChangeHost.addActionListener(this);
		ChangePort.addActionListener(this);
		Send.addActionListener(this);
		StartServer.addActionListener(this);
		Connect.addActionListener(this);
		Disconnect.addActionListener(this);
		
	//Sets initial state
		ChatLog.setEditable(false);
		StatusLog.setEditable(false);
		StatusLog.setBackground(Color.lightGray);
		Message.setBackground(Color.darkGray);
		state = 0;
		SetButtons(state);


		ChatWindow.addWindowListener(this);
		ChatWindow.setLayout(displ);
		ChatWindow.setResizable(true);
		ChatWindow.setVisible(true);
		ChatWindow.validate();
	}
	
	//Used in the Chat constructor to create the window components
	public void InitComponents()
	{
		ChatLog = new TextArea("", 10, 80);		
		StatusLog = new TextArea("", 3, 80);
		Message = new TextField(70);
		IAddress = new TextField(10);
		Port = new TextField(Integer.toString(portNumber),10);
		ChangeHost = new Button("Change Host");
		ChangePort = new Button("Change Port");
		Send = new Button("Send");
		StartServer = new Button("Start Server");
		Connect = new Button("Connect");
		Disconnect = new Button("Disconnect");
	}
	
	//Stops the thread, closes sockets, reader/writer, listeners, and window 
	public void stop()
	{
		Thread.currentThread().setPriority(Thread.MIN_PRIORITY);
		close();
		Message.removeActionListener(this);
		IAddress.removeActionListener(this);
		Port.removeActionListener(this);
		ChangeHost.removeActionListener(this);
		ChangePort.removeActionListener(this);
		Send.removeActionListener(this);
		StartServer.removeActionListener(this);
		Connect.removeActionListener(this);
		Disconnect.removeActionListener(this);
		ChatWindow.removeWindowListener(this);
		ChatWindow.dispose();
	}
	
	//Enables/disables buttons based on the program state
	public void SetButtons(int s)
	{
		
		//If initial state
		if(s == 0)
		{
			
			StartServer.setEnabled(true);
			Connect.setEnabled(false);
			Message.setEnabled(false);
			Message.setBackground(Color.darkGray);
		}
		
		//If server state
		if(s == 1)
		{
			StartServer.setEnabled(false);
			Connect.setEnabled(false);
			Message.setEnabled(true);
			Message.setBackground(Color.white);
		}
		
		//If client state
		if(s == 2)
		{
			StartServer.setEnabled(false);
			Connect.setEnabled(false);
			Message.setEnabled(true);
			Message.setBackground(Color.white);
			
		}
		
	}
	
	//Removes active readers/writers and sockets, stops the thread, and sets program to initial state
	public void close()
	{
		try
		{
			ChatWindow.setTitle("Chat");
			
			//Disconnects the server socket and closes the printwriter
			if(server!=null)
			{
				if(pw != null)
				{
					pw.print("");
					pw = null;
				}
				server.close();
				server = null;
			}
			
			//Disconnects the client socket and closes the printwriter
			if(client!=null)
			{
				if(pw != null)
				{
					pw.print("");
					pw = null;
				}
				client.close();
				client = null;
			}
			
			if(listen_socket!=null)
			{
				listen_socket.close();
				listen_socket = null;
			}

			//Closes the buffered reader
			if(br!=null)
			{
				br.close();
				br = null;
			}
			
			//Changes the thread flag to false
			more = false;
			
			//Nullifies the thread
			TheThread = null;
			
			//Sets program to initial state
			state = 0;
			SetButtons(state);
		}
		catch (IOException e){}
		catch (NullPointerException no){}
		
	}
	
	public void actionPerformed(ActionEvent e)
	{
			Object source = e.getSource();
			
			//If 'Send' button is pressed or the 'Enter' key is hit while the respective field is selected, it writes the message on the user's end and sends it to the other connected instance of the program
			if(source == Send ||source == Message)
			{
				outData = Message.getText();
				if(!outData.equals(""))
				{
					ChatLog.append("out: "+outData+"\n");
					pw.println(outData);
					Message.setText("");
				}
			}
			
			//If 'Start Server' button is pressed, it sets up the socket, bufferedreader, and printwriter and opens a server with the port and timeout that was entered
			if(source == StartServer)
			{
				StatusLog.append("Starting Server\n");
				StatusLog.append("Server: listening on " + Integer.toString(portNumber) + ".\n");
				StatusLog.append("Server: timeout time set to " + Integer.toString(timeout) + " mS.\n");
				StatusLog.append("Server: waiting for a request on " + Integer.toString(portNumber) + ".\n");

				try
				{
					if(listen_socket!=null)
					{
						listen_socket.close();
						listen_socket = null;
					}
					listen_socket = new ServerSocket(portNumber);
					listen_socket.setSoTimeout(10*timeout);
					if(client!=null)
					{
						client.close();
						client = null;
					}
				}
				catch (IOException er)
				{
					StatusLog.append("Server: failed to start connection.\n");
					close();
				}

				try
				{
					client = listen_socket.accept();
					StatusLog.append("Server: connection from " + client.getInetAddress() + ".\n"); 
				}
				
				catch (SocketTimeoutException s)
				{
					StatusLog.append("Server: the server has timed out.\n");
					close();
				}
				catch (IOException er)
				{
					StatusLog.append("Server: failed to start connection.\n");
					close();
				}
				
				try
				{
					br = new BufferedReader(new InputStreamReader(client.getInputStream()));
					pw = new PrintWriter(client.getOutputStream(), auto_flush);
					state = 1;
					SetButtons(state);
					more = true;
					Start();
					ChatWindow.setTitle("Server: Connected to " + client.getInetAddress() + "\n");
				}
				catch (NullPointerException no)
				{
					StatusLog.append("Server: failed to start connection.\n");
					close();
				}
				catch (IOException er)
				{
					StatusLog.append("Server: failed to start connection.\n");
					close();
				}

			}
			
			//If 'Change Host' button is pressed or the 'Enter' key is hit while the respective field is selected, it stores the host name the user wants to connect to and enable the connect button
			//Will not store the name if in Server or Client state
			if(source == ChangeHost || source == IAddress)
			{
				hostName = IAddress.getText();
				if(state == 0)
				{
					if(!hostName.equals(""))
					{
						StatusLog.append("Host set to: "+hostName+"\n");
						Connect.setEnabled(true);
					}
				
					else	
					{
						Connect.setEnabled(false);
					}
				}
				if(state == 1)
				{
					StatusLog.append("Server: cannot change host while connected to client.\n");
				}
				if(state == 2)
				{
					StatusLog.append("Client: cannot change host while connected to server.\n");
				}
			}
			
			//If 'Change Port' button is pressed or the 'Enter' key is hit while the respective field is selected, it stores the port number the user wants to connect to and enable the connect button if a host is stored
			//Will not store the number if in Server or Client state
			//Port number has to be between 1-65535
			if(source == ChangePort ||source == Port)
			{
				try
				{
					if(state == 0)
					{
						if(Integer.parseInt(Port.getText())>65535||Integer.parseInt(Port.getText())<=0)
						{
							StatusLog.append("Please enter a valid port number (1-65535).\n");
						}
						else
						{
							portNumber = Integer.parseInt(Port.getText());	
							StatusLog.append("Port set to: "+Port.getText()+"\n");
					
							if(!hostName.equals(""))
							{
							Connect.setEnabled(true);
							}
							else
							{
								Connect.setEnabled(false);
							}
						}
					}
					
					if(state == 1)
					{
						StatusLog.append("Server: cannot change port while connected to client.\n");
					}
					if(state == 2)
					{
						StatusLog.append("Client: cannot change port while connected to server.\n");
					}
				}
				catch(NumberFormatException n){StatusLog.append("Please enter a valid port number (1-65535).\n");}
			}		
			
			//If 'Connect' button is pressed, it sets up the socket, bufferedreader, and printwriter and opens a server with the host name, port and timeout that was entered
			if(source == Connect)
			{
				StatusLog.append("Starting Client\n");
				StatusLog.append("Client: timeout time set to " + Integer.toString(timeout) + " mS.\n");
				StatusLog.append("Client: connecting to " + hostName + ":" + Integer.toString(portNumber) + ".\n");
				try
				{
					if(server!=null)
					{
						server.close();
						server = null;
					}
					server = new Socket();
					server.setSoTimeout(timeout);
				}
				catch (IOException er)
				{
					StatusLog.append("Client: connection to /" + hostName +" failed.\n");
					close();
				}
				
				try
				{
					server.connect(new InetSocketAddress(hostName, portNumber));
					StatusLog.append("Client: connected to "+server.getInetAddress() + " at port " + Integer.toString(portNumber) + "\n");
				}
				
				catch (SocketTimeoutException s)
				{
					StatusLog.append("Client: connection to /" + hostName + "timed out.\n");
					close();
				}
				catch (IOException er){close();}
				
				try
				{
					br = new BufferedReader(new InputStreamReader(server.getInputStream()));
					pw = new PrintWriter(server.getOutputStream(), auto_flush);
					state = 2;
					SetButtons(state);
					more = true;
					Start();
					ChatWindow.setTitle("Client: Connected to "+server.getInetAddress() + " at port " + Integer.toString(portNumber) + "\n");
				}
				catch (NullPointerException no)
				{
					StatusLog.append("Client: connection to /" + hostName +" failed.\n");
					close();
				}
				catch (IOException er)
				{
					StatusLog.append("Client: connection to /" + hostName +" failed.\n");
					close();
				}

			}
			
			//If the program is not in the initial state, anything pressed will cause the message field to be highlighted
			if(state!=0)
				Message.requestFocus();
			
			//If the program is in Server or Client mode, it calls the function to disconnect the sockets, reader/writer, and set program to initial state
			if(source == Disconnect)
			{
				if(state == 1)
				{
					StatusLog.append("Server: chat has disconnected.\n");
					close();
				}
		
				if(state == 2)
				{
					StatusLog.append("Client: chat has disconnected.\n");
					close();
				}
			}
			
	}
	
	//Calls the stop method to close the program
	public void windowClosing(WindowEvent e)
	{stop();}
	
	public void windowClosed(WindowEvent e){}
	public void windowOpened(WindowEvent e){}
	public void windowActivated(WindowEvent e){}
	public void windowDeactivated(WindowEvent e){}
	public void windowIconified(WindowEvent e){}
	public void windowDeiconified(WindowEvent e){}
	
	//Initalizes and starts the thread
	public void Start()
	{
		if(TheThread == null)
		{
			TheThread = new Thread(this);
			TheThread.start();
		}
		
	}
	
	//Runs the thread while connected to a user (more = true)
	public void run()
	{
		Thread.currentThread().setPriority(Thread.MAX_PRIORITY);
		if(state == 1)
		{
			StatusLog.append("Server: chat has started.\n");
		}
		
		if(state == 2)
		{
			StatusLog.append("Client: chat has started. \n");
		}

		while(more)
		{
			try
			{
				inData = br.readLine();
				if(inData!=null)
				{
					ChatLog.append("in: "+inData+"\n");
				}
				else if(inData==null)
				{
					more = !more;
				}
			}
			catch (IOException e){}
			
		}
		
		if(state == 1)
		{
			StatusLog.append("Server: chat has disconnected.\n");
			state = 0;
			SetButtons(state);
		}
		
		if(state == 2)
		{
			StatusLog.append("Client: chat has disconnected.\n");
			state = 0;
			SetButtons(state);
		}
		
		close();

			
	}
}