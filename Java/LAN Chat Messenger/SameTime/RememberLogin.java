import java.io.*;

public class RememberLogin {
	
	UserLogin ul;
	RememberLogin(UserLogin ul)
	{
		this.ul=ul;
		try
		{
			File file=new File("login.txt");			
			FileReader fr=new FileReader(file);   
			BufferedReader br=new BufferedReader(fr);    
			int i;    
			int j=0;
			String str="";
			while((i=br.read())!=-1)
			{  
				if((char)i=='='&&j==0)
				{
					i=br.read();
					str="";
					while((char)i!=';')
					{
						str=str+(char)i;
						i=br.read();						
					}
					ul.userServerTf.setText(str);
					j++;
				}
				else if((char)i=='='&&j==1)
				{
					i=br.read();
					str="";
					while((char)i!=';')
					{
						str=str+(char)i;
						i=br.read();						
					}
					ul.userPortTf.setText(str);
					j++;
				}
				else if((char)i=='='&&j==2)
				{
					i=br.read();
					str="";
					while((char)i!=';')
					{
						str=str+(char)i;
						i=br.read();						
					}
					ul.userNameTf.setText(str);
					j++;
				}
				else if((char)i=='='&&j==3)
				{
					i=br.read();
					str="";
					while((char)i!=';')
					{
						str=str+(char)i;
						i=br.read();						
					}
					ul.userPasswordTf.setText(str);
					j++;
				}
			}  
			br.close();    
			fr.close(); 			     
		}
		catch(Exception e)
		{    
			System.out.println("Inside RememberLogin");
		}  
	}
}
		
	