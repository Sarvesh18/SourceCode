import java.awt.event.*;
import javax.swing.*;   
import java.io.*;         
class UserLoginAction implements ActionListener
{
	UserLogin ul;
	UserLoginAction(UserLogin ul)
	{
		this.ul=ul;
	}
	@Override
	public void actionPerformed(ActionEvent e)
	{
		if(e.getSource()==ul.loginBt)
		{
			User user=new User();
			user.setUserServer(ul.userServerTf.getText());
			user.setUserPort(ul.userPortTf.getText());
			user.setUserName(ul.userNameTf.getText());
			user.setUserPassword(ul.userPasswordTf.getText());

			try
			{    
				File file=new File("login.txt");
				FileWriter fw=new FileWriter(file);    
				fw.write("Server="+user.getUserServer()+";\n");
				fw.write("Port="+user.getUserPort()+";\n");
				fw.write("UserName="+user.getUserName()+";\n"); 
				fw.write("UserName="+user.getUserPassword()+";\n");	   
				fw.close();   
			}
			catch(Exception e1)
			{
				System.out.println("Inside UserLoginAction");
			}
			
			user=UserDao.validateUser(user);
			ul.setVisible(false);
			new UserUi(ul);

			/*
			if(user!=null && user.getUserType().equalsIgnoreCase("Admin"))
			{
				System.out.println(user.getFirstName()+" Login : "+user.getUserType());
			}
			else if(user!=null && user.getUserType().equalsIgnoreCase("store"))
			{
				System.out.println(user.getFirstName()+" Login : "+user.getUserType());
			}
			*/
			//ul.userNameTf.setText("Invalid MC");
		}
		else if(e.getSource()==ul.registerBt)
		{
			/*
			ul.setVisible(false);
			new UserRegister(ul);
			*/
		}		
	}
}
