import java.io.*;
import java.net.*;
public class MyServer
{
	ServerSocket ss;
	Socket s;
	DataInputStream dis;
	DataOutputStream dout;
	public MyServer()
	{
		try
		{
			System.out.println("Server Started");
			ss= new ServerSocket(10);
			s=ss.accept();
			System.out.println(s);
			System.out.println("Client Connected");
			dis=new DataInputStream(s.getInputStream());
			dout= new DataOutputStream(s.getOutputStream());
			serverChat();
		}
		catch(Exception e)
		{
			System.out.println(e);
		}
	}
	public static void main(String args[])
	{
		new MyServer();
	}
	public void serverChat() throws IOException
	{
		String str, s1;
		do
		{
			str= dis.readUTF();
			System.out.println("CLIENT MSG:"+str);
			BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
			s1=br.readLine();
			dout.writeUTF(s1);
			dout.flush();
		}
		while(!s1.equals("stop"));
	}
}
			
			
			