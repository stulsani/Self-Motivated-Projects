package com.sumeet.servlets;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.text.SimpleDateFormat;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.sumeet.connection.DbConnection;

public class EditCustomerServlet extends HttpServlet{

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		String fname = request.getParameter("fname");
        String lname = request.getParameter("lname");
        String ssn = request.getParameter("ssn");
        String dob = request.getParameter("dob");
        String email = request.getParameter("email");
        String acctState = request.getParameter("acctState");
        String uname = request.getParameter("uname");
        String password = request.getParameter("password");
        String wphone = request.getParameter("wphone");
        String streetno = request.getParameter("streetno");
        String city = request.getParameter("city");
        String state = request.getParameter("state");
        String zip = request.getParameter("zip");
        //String country = request.getParameter("country");
        //String wphone = request.getParameter("wphone");
        int cust_id = (int) request.getSession().getAttribute("cust_id");
        PrintWriter out = response.getWriter();
		response.setContentType("text/html");
		try {
			DbConnection connection = new DbConnection();
    		Connection con = connection.getConnection();
    		
    		String phone_sql = "update phone set (wphone = ?) where phone_id = (select phone_id from customer where customer_id = ?)";
    		PreparedStatement pst_phone = con.prepareStatement(phone_sql);
			//pst.setString(1, acct_id);
    		pst_phone.setString(1, wphone);
    		pst_phone.setInt(2, cust_id);
    		
			int numRowsChanged_phone = pst_phone.executeUpdate();
			if(numRowsChanged_phone == 1){
				con.commit();
			}
			
			String location_sql = "update locations set (streetno = ?, city = ?, state = ?, zip = ?) where location_id = (select location_id from customer where customer_id = ?)";
    		//(locations_location_id_seq.nextval,?,?,?,?,1)
			PreparedStatement pst_location = con.prepareStatement(location_sql);
			//pst.setString(1, acct_id);
    		pst_location.setString(1, streetno);
    		pst_location.setString(2, city);
    		pst_location.setString(3, state);
    		pst_location.setString(4, zip);
    		pst_location.setInt(5, cust_id);
			int numRowsChanged_location = pst_location.executeUpdate();
			if(numRowsChanged_location == 1){
				con.commit();
			}
			
			java.util.Date now = new java.util.Date(dob);
			String DATE_FORMAT = "MM/dd/yyyy";
			SimpleDateFormat sdf = new SimpleDateFormat(DATE_FORMAT);


			String strDateNew = sdf.format(now) ;
    		
			String cust_sql = "update customer set (fname = ?, lname = ?, ssn = ?, email = ?, password = ?) where customer_id = ?)";
			//(account_detail_account_id_seq.currval,?,?,?,'"+strDateNew+"',?,?,locations_location_id_seq.currval,sysdate,?,?,customer_customer_id_seq.nextval,phone_phone_id_seq.currval
		    PreparedStatement pst = con.prepareStatement(cust_sql);
			//pst.setString(1, acct_id);
			pst.setString(1, fname);
			pst.setString(2, lname);
			pst.setString(3, ssn);
			//pst.setString(4, dob);
			pst.setString(4, email);
			//pst.setString(5, acctState);
			
			//pst.setString(5, uname);
			pst.setString(5, password);
			pst.setInt(6, cust_id);
				  
			int numRowsChanged = pst.executeUpdate();
				  // show that the new account has been created
			if(numRowsChanged == 1){
				con.commit();
				//out.println(" Hello : ");
				
				request.getRequestDispatcher("/editCustomerSuccess.jsp").forward(request, response);
			}
			else {
				request.getRequestDispatcher("/editCustomerError.jsp").forward(request, response);
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
