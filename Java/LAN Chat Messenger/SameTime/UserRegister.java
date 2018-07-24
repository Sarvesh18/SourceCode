import javax.swing.*;
import java.awt.*;
class UserRegister extends JFrame
{
	JButton cancelBt;
	UserLogin ul;
	UserRegister(UserLogin ul)
	{
		super("User Register");
		this.ul=ul;
		cancelBt=new JButton("Cancel");
		cancelBt.addActionListener(new UserRegisterAction(this));
		setLayout(new FlowLayout(10));
		add(cancelBt);
		setSize(300,300);
		setVisible(true);
	}
}