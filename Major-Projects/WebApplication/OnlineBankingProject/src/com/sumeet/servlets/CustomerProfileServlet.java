package com.sumeet.servlets;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.sumeet.connection.DbConnection;

public class CustomerProfileServlet extends HttpServlet{

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		PrintWriter out = response.getWriter();
		response.setContentType("text/html");
		out.print("I am in Admin Profile");
		int acct_id, ssn, loc_id, cust_id, phn_id;
		String cust_last_name, email, lname;
		String cust_uname;
		String fname = (String) request.getSession().getAttribute("cust_name");
		String pass = (String) request.getSession().getAttribute("cust_pass");
		try {
	         
    		DbConnection connection = new DbConnection();
    		Connection con = connection.getConnection();
    		PreparedStatement ps=con.prepareStatement("select * from customer where first_name=? and password =?");
    		ps.setString(1,fname);
    		ps.setString(2,pass);
    		ResultSet rs=ps.executeQuery();
    		if(rs.next()){
    			acct_id = rs.getInt(1);
    			//cust_last_name = rs.getString(3);
    			cust_uname = rs.getString(10);
    			fname = rs.getString(2);
        		lname = rs.getString(3);
        		ssn = rs.getInt(4);
        		email = rs.getString(6);
        		loc_id = rs.getInt(11);
        		cust_id = rs.getInt(12);
        		phn_id = rs.getInt(13);
    			request.getSession().setAttribute("acct_id",acct_id);
    			//request.getSession().setAttribute("fname",fname);
    			request.getSession().setAttribute("lname",lname);
    			request.getSession().setAttribute("ssn",ssn);
    			request.getSession().setAttribute("email",email);
    			request.getSession().setAttribute("loc_id",loc_id);
    			request.getSession().setAttribute("phn_id",phn_id);
    			//request.getSession().setAttribute("cust_last_name",cust_last_name);
    			request.getSession().setAttribute("cust_uname",cust_uname);
    			request.getRequestDispatcher("/custProfile.jsp").forward(request, response);
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
