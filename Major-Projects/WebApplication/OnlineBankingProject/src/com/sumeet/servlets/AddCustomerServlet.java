package com.sumeet.servlets;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.Date;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.text.SimpleDateFormat;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.sumeet.connection.DbConnection;

public class AddCustomerServlet extends HttpServlet{

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		//String acct_id = request.getParameter("acct_id");
		String fname = request.getParameter("fname");
        String lname = request.getParameter("lname");
        String ssn = request.getParameter("ssn");
        String dob = request.getParameter("dob");
        String email = request.getParameter("email");
        String acctState = request.getParameter("acctState");
        
        String uname = request.getParameter("uname");
        String password = request.getParameter("password");
        
        String balance = request.getParameter("balance");
        String intrate = request.getParameter("intrate");
        String cust_categ = request.getParameter("cust_categ");
        String wphone = request.getParameter("wphone");
        
        String streetno = request.getParameter("streetno");
        String city = request.getParameter("city");
        String state = request.getParameter("state");
        String zip = request.getParameter("zip");
        //String country = request.getParameter("country");
        //String wphone = request.getParameter("wphone");
        
        PrintWriter out = response.getWriter();
		response.setContentType("text/html");
		try {
			DbConnection connection = new DbConnection();
    		Connection con = connection.getConnection();
    		
    		String phone_sql = "insert into phone(phone_id, work_phone) values (phone_phone_id_seq.nextval,?)";
    		PreparedStatement pst_phone = con.prepareStatement(phone_sql);
			//pst.setString(1, acct_id);
    		pst_phone.setString(1, wphone);
    		
			int numRowsChanged_phone = pst_phone.executeUpdate();
			if(numRowsChanged_phone == 1){
				con.commit();
			}
			
			String location_sql = "insert into locations values (locations_location_id_seq.nextval,?,?,?,?,1)";
    		PreparedStatement pst_location = con.prepareStatement(location_sql);
			//pst.setString(1, acct_id);
    		pst_location.setString(1, streetno);
    		pst_location.setString(2, city);
    		pst_location.setString(3, state);
    		pst_location.setString(4, zip);
			int numRowsChanged_location = pst_location.executeUpdate();
			if(numRowsChanged_location == 1){
				con.commit();
			}
			
    		String account_sql = "insert into account_detail values (account_detail_account_id_seq.nextval,?,?,?)";
    		PreparedStatement pst_account = con.prepareStatement(account_sql);
			//pst.setString(1, acct_id);
    		pst_account.setString(1, balance);
    		pst_account.setString(2, intrate);
    		pst_account.setString(3, cust_categ);
    		//pst_phone.setString(4, zip);
			int numRowsChanged_account = pst_account.executeUpdate();
			if(numRowsChanged_account == 1){
				con.commit();
			}
    		
			java.util.Date now = new java.util.Date(dob);
			String DATE_FORMAT = "MM/dd/yyyy";
			SimpleDateFormat sdf = new SimpleDateFormat(DATE_FORMAT);


			String strDateNew = sdf.format(now) ;

    		String cust_sql = "insert into customer values (account_detail_account_id_seq.currval,?,?,?,'"+strDateNew+"',?,?,locations_location_id_seq.currval,sysdate,?,?,customer_customer_id_seq.nextval,phone_phone_id_seq.currval)";
		    PreparedStatement pst = con.prepareStatement(cust_sql);
			//pst.setString(1, acct_id);
			pst.setString(1, fname);
			pst.setString(2, lname);
			pst.setString(3, ssn);
			//pst.setString(4, dob);
			pst.setString(4, email);
			pst.setString(5, acctState);
			
			pst.setString(6, uname);
			pst.setString(7, password);
			
				  
			int numRowsChanged = pst.executeUpdate();
				  // show that the new account has been created
			if(numRowsChanged == 1){
				con.commit();
				out.println(" Hello : ");
				
				request.getRequestDispatcher("/addCustomerSuccess.jsp").forward(request, response);
			}
			else {
				request.getRequestDispatcher("/addCustomerError.jsp").forward(request, response);
			}
				  pst.close();
		}
		catch(SQLException e){
			out.println("SQLException caught: " 
				  + e.getMessage());
		}
		catch (Exception e){
			out.println(e);
		}
		finally {
				  // Always close the database connection.
					  out.close();
		}
	    	  
       
	}
}
