package com.sumeet.servlets;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.Date;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.sumeet.connection.DbConnection;

public class SearchCustomerServlet extends HttpServlet{

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		PrintWriter out = response.getWriter();
		response.setContentType("text/html");
		String cust_username = request.getParameter("cust_uname");
       // String admin_passwrd = request.getParameter("admin_pass");
           //boolean status = false;    
		int adm_id;
		String last_name;
		String uname, ssn;
		Date dob;
		String fname;
		String pass;  
        try {
         
        		DbConnection connection = new DbConnection();
        		Connection con = connection.getConnection();
        		PreparedStatement ps=con.prepareStatement("select * from customer where username=?");
        		ps.setString(1,cust_username);
        		//ps.setString(2,admin_passwrd);
        		ResultSet rs=ps.executeQuery();
        		if(rs.next()){
        			fname = rs.getString(2);
        			last_name = rs.getString(3);
        			ssn = rs.getString(4);
        			dob = rs.getDate(5);
        			uname = rs.getString(10);
        			request.getSession().setAttribute("cust_fname",fname);
                    request.getSession().setAttribute("cust_lname",last_name);
                    request.getSession().setAttribute("cust_ssn",ssn);
                    request.getSession().setAttribute("cust_dob",dob);
                    request.getSession().setAttribute("cust_uname",uname);
                    request.getRequestDispatcher("/searchedCustomer.jsp").forward(request, response); 
        		}
        		
        		else {
        			out.print("Sorry, customer NOT found");  
                    request.getRequestDispatcher("/dashboard.jsp").forward(request, response); 
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
