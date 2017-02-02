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

public class CustomerRequestServlet extends HttpServlet{

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		PrintWriter out = response.getWriter();
		response.setContentType("text/html");
		String cust_uname = (String) request.getSession().getAttribute("cust_uname");
		String cust_city ;
		int admin_id;
		int cust_id;
		
		 try {
	         
     		DbConnection connection = new DbConnection();
     		Connection con = connection.getConnection();
     		PreparedStatement ps=con.prepareStatement("select l.city_name, c.account_id from customer c join locations l using(location_id) where c.username=?");
     		ps.setString(1,cust_uname);
     		//out.print(cust_uname);
     		//ps.setString(2,cust_passwrd);
     		ResultSet rs=ps.executeQuery();
     		if(rs.next()){
     			//out.print("Reached"); 
     			
     			//status = true;
     			cust_city = rs.getString(1);
     			cust_id = rs.getInt(2);
     			//out.print(cust_id);
     			//out.print(cust_city);
     			//String cust_city_initcap = cust_city.
     			PreparedStatement admin_ps=con.prepareStatement("select admin_id from bank_admin where city=?");
     			admin_ps.setString(1,cust_city);
         		//ps.setString(2,cust_passwrd);
         		ResultSet admin_rs=admin_ps.executeQuery();
         		if(admin_rs.next()){
         			//status = true;
         			out.print("Reached");
         			admin_id = rs.getInt(1);
         			out.print(admin_id);
         			String request_sql = "insert into pending_request values (pending_request_request_id_seq.nextval,?,?,(sysdate+3),'Pending','Cheque')";
            		PreparedStatement pst_req = con.prepareStatement(request_sql);
        			//pst.setString(1, acct_id);
            		pst_req.setInt(1, admin_id);
            		pst_req.setInt(2, cust_id);
            		
        			int numRowsChanged_request = pst_req.executeUpdate();
        			if(numRowsChanged_request == 1){
        				con.commit();
        				String request_mapping_sql = "insert into request_mapping values (request_mapping_mapping_id_seq.nextval,pending_request_request_id_seq.currval,?,?)";
                		PreparedStatement pst_req_mapping = con.prepareStatement(request_mapping_sql);
            			//pst.setString(1, acct_id);
                		
                		pst_req_mapping.setInt(1, cust_id);
                		pst_req_mapping.setInt(2, admin_id);
            			int numRowsChanged_request_mapping = pst_req_mapping.executeUpdate();
            			if(numRowsChanged_request_mapping == 1){
            				con.commit();
            				out.print("The request is accepted."); 
            				//request.getRequestDispatcher("index.jsp").forward(request, response);
            			}
        			}
         			
         		}
     		
     		
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
