import java.awt.*;
import javax.swing.*;
class UserLogin extends JFrame 
{
	JLabel userServerLb,userPortLb,userNameLb,userPasswordLb;
	JTextField userServerTf,userPortTf,userNameTf;
	JPasswordField userPasswordTf;
	JButton loginBt,registerBt;
	
	UserLogin(String name)
	{
		super(name);
	
		int x1=50,x2=250;
		
		userServerLb=new JLabel("Server");
		userServerLb.setBounds(x1,50,200,40);
add(userServerLb);	
		userServerTf=new JTextField();
		userServerTf.setBounds(x2,50,200,40);
add(userServerTf);	

		userPortLb=new JLabel("Port");
		userPortLb.setBounds(x1,100,200,40);
add(userPortLb);
		userPortTf=new JTextField();
		userPortTf.setBounds(x2,100,200,40);
add(userPortTf);
	
		userNameLb=new JLabel("User Name");
		userNameLb.setBounds(x1,150,200,40);
add(userNameLb);
		userNameTf=new JTextField();
		userNameTf.setBounds(x2,150,200,40);
add(userNameTf);

		userPasswordLb=new JLabel("Password");
		userPasswordLb.setBounds(x1,200,200,40);
add(userPasswordLb);
		userPasswordTf=new JPasswordField();
		userPasswordTf.setBounds(x2,200,200,40);
add(userPasswordTf);
	
		loginBt=new JButton("Login");
		loginBt.setBounds(x1+50,300,100,40);
add(loginBt);
		registerBt=new JButton("Register");
		registerBt.setBounds(x2+50,300,100,40);
add(registerBt);

		loginBt.addActionListener(new UserLoginAction(this));
		registerBt.addActionListener(new UserLoginAction(this));

		setLayout(null);
		setSize(550,450);
		
		new RememberLogin(this);
		
		setVisible(true);	
	}
	public static void main(String args[])
	{
		new UserLogin("Login");
	}	
}