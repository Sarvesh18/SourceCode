import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.io.*;
import java.net.*;

public class FileTransfer extends JFrame implements ActionListener
{
	JFrame jf;
	JButton jb1,jb2;
	TextField tf;
	JFileChooser jfc;
	Socket s;
	DataInputStream din;
	DataOutputStream dout;
	String s1=new String();
	String s2=new String();
	File f;
	FileTransfer()
	{
		jf=new JFrame("File Transfer");
		jf.setSize(400,400);
		Container c=jf.getContentPane();
		c.setBackground(Color.red);
		jf.setLayout(null);
		jb1=new JButton("Choose File");
		jb2=new JButton("Send");
		jb1.setBounds(30,50,100,50);
		jb2.setBounds(250,100,70,50);
		jf.add(jb1);
		jf.add(jb2);
		tf=new TextField();
		tf.setEditable(false);
		tf.setBackground(Color.white);
		tf.setBounds(150,50,190,50);
		jf.add(tf);
		jf.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		jf.setVisible(true);
		jfc=new JFileChooser();
		jb1.addActionListener(this);
		jb2.addActionListener(this);
	}
	public void fileTransfer(String s1)
	{
		try
		{
			dout.writeUTF(s1);
			dout.flush();
			s2=f.getAbsolutePath();
			
			
			
			File file = new File(s2);
			long length = file.length();
			byte[] bytes = new byte[16 * 1024];
			InputStream in = new FileInputStream(file);
			OutputStream out = s.getOutputStream();

			int count;
			while ((count = in.read(bytes)) > 0) 
			{
				out.write(bytes, 0, count);
			}
			out.close();
			in.close();
		}
		catch(Exception e)
		{
			System.out.println(e);
		}
	}

	public void actionPerformed(ActionEvent e)
	{
		if(e.getSource()==jb1)
		{
			int x = jfc.showOpenDialog(null);
			if(x==JFileChooser.APPROVE_OPTION)
			{
				f=jfc.getSelectedFile();
				String path=f.getPath();
				s1=f.getName();
				tf.setText(path);
			}
		}
		if(e.getSource()==jb2)
		{
			try
			{
				s=new Socket ("localhost",10);
				dout= new DataOutputStream(s.getOutputStream());	
			}
			catch(Exception e1)
			{
				System.out.println(e1);
			}
			fileTransfer(s1);
		}
	}
	public static void main(String args[])
	{
		FileTransfer ft = new FileTransfer();
	}
}