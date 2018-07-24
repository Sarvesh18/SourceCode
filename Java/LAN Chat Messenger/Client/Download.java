import java.io.*;
import java.net.*;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Download implements Runnable{
    
    public ServerSocket server;
    public Socket socket;
    public int port;
    public String saveTo = "";
    //public InputStream In;
    //public FileOutputStream Out;
	InputStream in;
    OutputStream out;
	public ChatFrame ui;
    
    public Download(String saveTo, ChatFrame ui){
			
		try {
            server = new ServerSocket(10);
            port = server.getLocalPort();
            this.saveTo = saveTo;
            this.ui = ui;
        } 
        catch (IOException ex) {
            System.out.println("Exception [Download : Download(...)]");
			System.out.println(ex);
        }
    }

    @Override
    public void run() {
	   try {
            socket = server.accept();
            System.out.println("Download : "+socket.getRemoteSocketAddress());
            
			//dis= new DataInputStream(s.getInputStream());
			//String s2=dis.readUTF();
			//System.out.println(s2);
			
			in = socket.getInputStream();
            out = new FileOutputStream(saveTo);
			 
			byte[] bytes = new byte[16*1024];

			int count;
			while ((count = in.read(bytes)) > 0) 
			{
				out.write(bytes, 0, count);
			}
			out.close();
			in.close();
            ui.jTextArea1.append("[Application > Me] : Download complete\n");
            
            //if(Out != null){ Out.close(); }
            //if(In != null){ In.close(); }
            if(socket != null){ socket.close(); }
        } 
        catch (Exception ex) {
            System.out.println("Exception [Download : run(...)]");
			System.out.println(ex);
        }
    }
}