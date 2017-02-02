package com.sumeet.servlets;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.sumeet.connection.DbConnection;

public class AdminServlet extends HttpServlet{

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		//String pass = " ";
		//String uname = " ";
		String fname = " ";
		
		PrintWriter out = response.getWriter();
		response.setContentType("text/html");
		String admin_username = request.getParameter("admin_uname");
        String admin_passwrd = request.getParameter("admin_pass");
           boolean status = false;    
               
        try {
         
        		DbConnection connection = new DbConnection();
        		Connection con = connection.getConnection();
        		PreparedStatement ps=con.prepareStatement("select * from bank_admin where username=? and password =?");
        		ps.setString(1,admin_username);
        		ps.setString(2,admin_passwrd);
        		ResultSet rs=ps.executeQuery();
        		if(rs.next()){
        			status = true;
            		fname = rs.getString(2);
        		}
        		
        		if(status){
                    HttpSession session=request.getSession();  
                    session.setAttribute("adm_name",fname);
                    session.setAttribute("adm_pass",admin_passwrd);
                    request.getRequestDispatcher("/dashboard.jsp").forward(request, response); 
        		}
        		else {
        			out.print("Sorry, username or password error!");  
                    request.getRequestDispatcher("index.jsp").forward(request, response); 
        		}
        }
        
        catch (Exception e2) {
        	e2.printStackTrace();
        	}
		finally{
			out.close();
			}
	}
}

