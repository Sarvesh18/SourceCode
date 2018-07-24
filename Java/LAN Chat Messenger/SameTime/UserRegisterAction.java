import java.awt.event.*;
import javax.swing.*;
class UserRegisterAction implements ActionListener
{
	UserRegister ur;
	UserRegisterAction(UserRegister ur)
	{
		this.ur=ur;
	}
	@Override
	public void actionPerformed(ActionEvent e)
	{
		if(e.getSource()==ur.cancelBt)
		{
			ur.ul.setVisible(true);
			ur.dispose();
		}
	}
}
