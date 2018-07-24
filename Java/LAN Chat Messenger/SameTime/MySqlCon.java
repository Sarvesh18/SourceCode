import java.sql.*;
class MySqlCon
{
	public static Connection getConnection()
	{
		try
		{
			Class.forName("com.mysql.jdbc.Driver");  
			Connection con=DriverManager.getConnection("jdbc:mysql://localhost:3306/test","root",""); 
			return con;
		}
		catch(Exception e)
		{
			//e.printStackTrace();
			System.out.println("Inside MySqlCon");
			return null;
		}
	}
}