package com.chits.servlets;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.sumeet.connection.DbConnection;

public class CustomerLoginServlet extends HttpServlet{

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
String fname = " ", lname = " ", email = " ";
int cust_id = 0, ssn = 0, loc_id = 0, phn_id = 0;
		
		PrintWriter out = response.getWriter();
		response.setContentType("text/html");
		String cust_username = request.getParameter("cust_uname");
        String cust_passwrd = request.getParameter("cust_pass");
       // String cust_id = request.getParameter("cust_id");
           boolean status = false;    
               
        try {
         
        		DbConnection connection = new DbConnection();
        		Connection con = connection.getConnection();
        		PreparedStatement ps=con.prepareStatement("select * from customer where username=? and password =?");
        		ps.setString(1,cust_username);
        		ps.setString(2,cust_passwrd);
        		//ps.setString(3,cust_id);
        		ResultSet rs=ps.executeQuery();
        		if(rs.next()){
        			status = true;
            		fname = rs.getString(2);
            		lname = rs.getString(3);
            		ssn = rs.getInt(4);
            		email = rs.getString(6);
            		loc_id = rs.getInt(11);
            		cust_id = rs.getInt(12);
            		phn_id = rs.getInt(13);
            		
        		}
        		
        		if(status){
                    HttpSession session=request.getSession();  
                    session.setAttribute("cust_name",fname);
                    session.setAttribute("last_name",lname);
                    session.setAttribute("ssn",ssn);
                    session.setAttribute("email",email);
                    session.setAttribute("cust_pass",cust_passwrd);
                    session.setAttribute("cust_uname",cust_username);
                    session.setAttribute("loc_id",loc_id);
                    session.setAttribute("cust_id",cust_id);
                    session.setAttribute("phn_id",phn_id);
                    request.getRequestDispatcher("/cust_dashboard.jsp").forward(request, response); 
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
