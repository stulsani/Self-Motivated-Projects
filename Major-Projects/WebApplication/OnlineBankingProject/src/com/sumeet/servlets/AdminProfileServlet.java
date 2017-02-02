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
import javax.servlet.http.HttpSession;

import com.sumeet.connection.DbConnection;

public class AdminProfileServlet extends HttpServlet{

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		PrintWriter out = response.getWriter();
		response.setContentType("text/html");
		out.print("I am in Admin Profile");
		int adm_id;
		String last_name;
		String uname;
		String fname = (String) request.getSession().getAttribute("adm_name");
		String pass = (String) request.getSession().getAttribute("adm_pass");
		try {
	         
    		DbConnection connection = new DbConnection();
    		Connection con = connection.getConnection();
    		PreparedStatement ps=con.prepareStatement("select * from bank_admin where first_name=? and password =?");
    		ps.setString(1,fname);
    		ps.setString(2,pass);
    		ResultSet rs=ps.executeQuery();
    		if(rs.next()){
    			adm_id = rs.getInt(1);
    			last_name = rs.getString(3);
    			uname = rs.getString(4);
    			request.getSession().setAttribute("adm_id",adm_id);
    			request.getSession().setAttribute("last_name",last_name);
    			request.getSession().setAttribute("uname",uname);
    			request.getRequestDispatcher("/adminProfile.jsp").forward(request, response);
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
