<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Insert title here</title>
</head>
<body>
<%
		Object acct_id = session.getAttribute("acct_id");
		Object lname = session.getAttribute("cust_last_name");
		Object ssn = session.getAttribute("ssn");
		Object email = session.getAttribute("email");
		//Object loc_id = session.getAttribute("loc_id");
		//Object phn_id = session.getAttribute("phn_id");
		Object cust_name = session.getAttribute("cust_name");
		//Object cust_last_name = session.getAttribute("cust_last_name");
		Object cust_uname = session.getAttribute("cust_uname");
		Object cust_pass = session.getAttribute("cust_pass");
		%>

<h1><center>Edit your details</center></h1>
<center><a href="LogoutServlet">Logout</a></center>
<form method="Get" action="EditCustomerServlet">
        <table>
        	<tr><td>First Name</td>
                <td><input type="text" name="fname" value="<%=cust_name%>"></td>
            </tr>
            <tr><td>Last Name</td>
                <td><input type="text" name="lname" value="<%=cust_last_name%>"></td>
            </tr>
            <tr><td>SSN</td>
                <td><input type="text" name="ssn" value="<%=ssn%>"></td>
            </tr>
            <tr><td>Date of Birth</td>
                <td><input type="text" name="dob"></td>
            </tr>
            <tr><td>Email Id</td>
                <td><input type="text" name="email" value="<%=email%>"></td>
            </tr>
            <tr><td>Account State</td>
                <td><input type="text" name="acctState" readonly></td>
            </tr>
            <tr><td>Username</td>
                <td><input type="text" name="uname" readonly></td>
            </tr>
            <tr><td>Password</td>
                <td><input type="text" name="password" value="<%=cust_pass%>"></td>
            </tr>
            <tr><td>Work Phone</td>
                <td><input type="text" name="wphone"></td>
            </tr>
            <tr><td>Street Number</td>
                <td><input type="text" name="streetno"></td>
            </tr>
            <tr><td>City</td>
                <td><input type="text" name="city"></td>
            </tr>
            <tr><td>State</td>
                <td><input type="text" name="state"></td>
            </tr>
            <tr><td>Zip</td>
                <td><input type="text" name="zip"></td>
            </tr>
            <tr><td>Country</td>
                <td><input type="text" name="country"></td>
            </tr>
            <tr><td>
                    <input type="cancel" value="Cancel">
                    <input type="submit" value="Submit">
                </td>
            </tr>
        </table>
    </form>
</body>
</html>