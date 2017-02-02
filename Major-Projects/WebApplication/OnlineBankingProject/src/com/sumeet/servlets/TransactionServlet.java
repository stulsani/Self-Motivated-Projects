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

public class TransactionServlet extends HttpServlet{

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		PrintWriter out = response.getWriter();
		response.setContentType("text/html");
		String cdAcctNmbr = request.getParameter("cdAcctNmbr");
        String amtTransfer = request.getParameter("amtTransfer");
        String remarks = request.getParameter("remarks");
        String cust_uname = (String) request.getSession().getAttribute("cust_uname");
        int debt_acct_id;
        
        try {
	         
    		DbConnection connection = new DbConnection();
    		Connection con = connection.getConnection();
    		
    		
    		PreparedStatement ps=con.prepareStatement("exec transactions_update ?,?,?,?");
    		ps.setString(1,amtTransfer);
    		ps.setString(2,amtTransfer);
    		ps.setString(3,cdAcctNmbr);
    		ps.setString(4,remarks);
    		ResultSet rs=ps.executeQuery();
    		if(rs.next()){
    			acct_id = rs.getInt(1);
    			cust_last_name = rs.getString(3);
    			cust_uname = rs.getString(10);
    			request.getSession().setAttribute("acct_id",acct_id);
    			request.getSession().setAttribute("cust_last_name",cust_last_name);
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
