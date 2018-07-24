import java.awt.*;
import javax.swing.*;
import java.io.*;
import java.net.*;

public class FileReceiver
{
	Socket s;
	ServerSocket ss;
	InputStream in;
    OutputStream out;
	DataInputStream dis;
	public FileReceiver()
	{
		try
		{
			ss = new ServerSocket(10);
			s = ss.accept();
	
			while(true)
			{
			dis= new DataInputStream(s.getInputStream());
			String s2=dis.readUTF();
			System.out.println(s2);
		
			in = s.getInputStream();
            out = new FileOutputStream(s2);
			
			fileReceiver();
			}
		}
		catch(Exception e)
		{
			System.out.println(e);
		}
	}
	public void fileReceiver()
	{	
		try 
		{ 
			byte[] bytes = new byte[16*1024];

			int count;
			while ((count = in.read(bytes)) > 0) 
			{
				out.write(bytes, 0, count);
			}
			//out.close();
			//in.close();
		}
		catch(Exception e)
		{
			System.out.println(e);
		}
	}
	public static void main(String args[])
	{
		new FileReceiver();
	}
}
			