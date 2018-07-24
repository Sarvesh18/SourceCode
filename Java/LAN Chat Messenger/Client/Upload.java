import java.io.*;
import java.net.*;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Upload implements Runnable{

    public String addr;
    public int port;
    public Socket socket;
    public ChatFrame ui;
	
	
	
	//public FileInputStream In;
    //public OutputStream Out;
	//DataInputStream din;
	//DataOutputStream dout;
	public File file;
	
	
	
    
    public Upload(String addr, int port, File filepath, ChatFrame frame){
        super();
        try {
			file = filepath; ui = frame;
            socket = new Socket(InetAddress.getByName(addr), port);
        } 
        catch (Exception ex) {
            System.out.println("Exception [Upload : Upload(...)]");
			System.out.println(ex);
        }
    }
    
    @Override
    public void run() {
		try
		{
			//dout= new DataOutputStream(socket.getOutputStream());
			//dout.writeUTF(s1);
			//dout.flush();
			//s2=f.getAbsolutePath();
			
			
			long length = file.length();
			byte[] bytes = new byte[16 * 1024];
			InputStream in = new FileInputStream(file);
			OutputStream out = socket.getOutputStream();

			int count;
			while ((count = in.read(bytes)) > 0) 
			{
				out.write(bytes, 0, count);
			}
			
			ui.jTextArea1.append("[Applcation > Me] : File upload complete\n");
            ui.jButton5.setEnabled(true); ui.jButton6.setEnabled(true);
            ui.jTextField5.setVisible(true);
			
			
			out.close();
			in.close();
			
			
			//if(In != null){ In.close(); }
            //if(Out != null){ Out.close(); }
            if(socket != null){ socket.close(); }
		}
        catch (Exception ex) {
            System.out.println("Exception [Upload : run()]");
			System.out.println(ex);
            ex.printStackTrace();
        }
    }

}