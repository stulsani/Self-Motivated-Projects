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

public class DeleteCustomerServlet extends HttpServlet{

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		PrintWriter out = response.getWriter();
		response.setContentType("text/html");
		String admin_username = request.getParameter("cust_uname");
		try {
	         
    		DbConnection connection = new DbConnection();
    		Connection con = connection.getConnection();
    		/*PreparedStatement pst = connection.prepareStatement
    				  ("delete from emp_sal where EmpName = 'vinod'");
    				  int i = pst.executeUpdate();
    				  if (i==0){
    				  pw.println("Row has been deleted");
    				  }
    				  else{
    				  pw.println("No rows has been deleted");
    				  }*/
    		PreparedStatement ps=con.prepareStatement("delete  from customer where username=?");
    		ps.setString(1,admin_username);
    		//ps.setString(2,admin_passwrd);
    		 int i = ps.executeUpdate();
    		 if (i==1){
    			 con.commit();
				  out.println("Row has been deleted");
				  request.getRequestDispatcher("/deleteCustSuccess.jsp").forward(request, response);
				  }
				  else{
				  request.getRequestDispatcher("/dashboard.jsp").forward(request, response);
				  }
    		/*ResultSet rs=ps.executeQuery();
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
    		}*/
    }
    
    catch (Exception e2) {
    	e2.printStackTrace();
    	}
	finally{
		out.close();
		}
	}

}
