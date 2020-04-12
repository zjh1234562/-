package hhjk;

import java.awt.List;
import java.sql.*;
import java.util.ArrayList;

import com.mysql.jdbc.UpdatableResultSet;

public class Mysqljdbc {
	
    public static void updatedata(String string,String string2)  //ÐÞ¸ÄµÇÂ½×´Ì¬
    {
    	int i;
    	String[] string3= {"Ð¡Ã÷","Ð¡¾ü","Ð¡ºì"};
    	for(i=0;i<3;i++)
    	{
    	try {
			Class.forName("com.mysql.jdbc.Driver");
		} catch (Exception e) {
			// TODO: handle exception
		}
        try
        {
        	
        	Connection conn=DriverManager.getConnection("jdbc:mysql://localhost:3306/ÅÀ³æ?useSSL=false","root","zjh123456");
        	String sql2 = "update "+string3[i]+" set islogin=? where name=?";
        	//System.out.println(sql2);
        	PreparedStatement pst = conn.prepareStatement(sql2);
        	pst.setString(1,string2);
        	pst.setString(2, string);
        	pst.executeUpdate();
        	conn.close();

        }catch(SQLException e){
            e.printStackTrace();
        }catch (Exception e) {
            e.printStackTrace();
            
        }finally{
                System.out.println("Êý¾Ý¿âÊý¾ÝÐÞ¸Ä³É¹¦£¡");
        }
    	}
    }
	public static String[] search(String name) throws SQLException{
		//²éÑ¯
		int i=0;
		try {
			Class.forName("com.mysql.jdbc.Driver");
		} catch (Exception e) {
			// TODO: handle exception
		}
		
		Connection connection=DriverManager.getConnection("jdbc:mysql://localhost:3306/ÅÀ³æ?useSSL=false","root","zjh123456");
		Statement statement=connection.createStatement();
		ResultSet resultSet=statement.executeQuery("select * from "+name);
		resultSet.last();
		int n =resultSet.getRow();
		//System.out.println(n);
		resultSet.beforeFirst();
		String []strs= new String[n];
		while (resultSet.next()) {
			String string1=resultSet.getString("name");
			String string2=resultSet.getString("islogin");
				
			String string=string1.concat(string2);
			//System.out.println(string);
			strs[i]=string;
			i++;}
		connection.close();
	return strs;
	
	}
	
	public static void insert(String string1,String string2) {
		//Ôö¼Ó
		try {
			Class.forName("com.mysql.jdbc.Driver");
		} catch (Exception e) {
			// TODO: handle exception
		}
		try {
        	Connection conn=DriverManager.getConnection("jdbc:mysql://localhost:3306/ÅÀ³æ?useSSL=false","root","zjh123456");
        	String sql2 = "insert into "+string1+" values('"+string2+"','F')";
        	Statement statement=conn.createStatement();
        	statement.executeUpdate(sql2);
        	conn.close();
		} catch (Exception e) {
			// TODO: handle exception
			System.out.println("²åÈëÊ§°Ü");
		}
		
	}
	
	public static void delect(String string1,String string2) {
		//É¾³ý
		try {
			Class.forName("com.mysql.jdbc.Driver");
		} catch (Exception e) {
			// TODO: handle exception
		}
		try {
        	Connection conn=DriverManager.getConnection("jdbc:mysql://localhost:3306/ÅÀ³æ?useSSL=false","root","zjh123456");
        	String sql2 = "delete from "+string1+" where name='"+string2+"'";
        	Statement statement=conn.createStatement();
        	statement.executeUpdate(sql2);
        	conn.close();
		} catch (Exception e) {
			// TODO: handle exception
			System.out.println("É¾³ýÊ§°Ü");
		}
		
	}
}
