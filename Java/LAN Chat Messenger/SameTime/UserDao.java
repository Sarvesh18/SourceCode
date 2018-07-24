import java.sql.*;
class UserDao
{
	private static Connection con=null;
	private static PreparedStatement pstmt=null;
	private static ResultSet rs=null;
	static 
	{
		try
		{
			System.out.println("Inside UserDao Static");
			con=MySqlCon.getConnection();
		}
		catch(Exception e)                                              
		{
			//e.printStackTrace();
			System.out.println("Inside UserDao Static CATCH");
		}
	}
	public static User validateUser(User user)
	{
		try
		{
			System.out.println("Inside UserDao");
			String sql="SELECT * FROM User WHERE UserName=? and Password=?";
			pstmt=con.prepareStatement(sql);
			pstmt.setString(1,user.getUserName());
			pstmt.setString(2,user.getUserPassword());
			rs=pstmt.executeQuery();
			while(rs.next())
			{
				//user.setUserName(rs.getInt(1));
				System.out.println(rs.getInt(1));
				System.out.println(rs.getString(2));
				System.out.println(rs.getString(3));
				System.out.println(rs.getString(4));
				System.out.println(rs.getString(5));
				System.out.println(rs.getLong(6));
				System.out.println(rs.getString(7));
				System.out.println(rs.getString(8));
				System.out.println(rs.getInt(9));
				System.out.println(rs.getInt(10));			
			}
			return user;
		}
		catch(Exception e)
		{
			/*
			//e.printStackTrace();
			String sql=
			//pstmt=con.prepareStatement(sql);
			Statement stmt=con.createStatement(); 
			int i=stmt.executeUpdate(sql);  
			System.out.println(i);
			*/
			System.out.println("Inside UserDaO CATCH");
		}
		return null;
	}
}