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
		Object cust_fname = session.getAttribute("cust_fname");
		Object cust_lname = session.getAttribute("cust_lname");
		Object cust_ssn = session.getAttribute("cust_ssn");
		Object cust_dob = session.getAttribute("cust_dob");
		Object cust_uname = session.getAttribute("cust_uname");
		Object uname = session.getAttribute("uname");
		Object adm_pass = session.getAttribute("adm_pass");
		Object adm_name = session.getAttribute("adm_name");
		%>
		<%-- <p><%=name%></p> --%>
        <center><h1><%=adm_name%> Profile</h1><br>
        <a href="AdminServlet?admin_uname=<%=uname%>&admin_pass=<%=adm_pass%>">Dashboard</a>
        <a href="AdminProfileServlet">Profile</a>
        <a href="LogoutServlet">Logout</a>
        </center>
        <br>
        <table border=1>
        	<tr>
           		<td>First Name</td>
           		<td>Last Name</td>
                <td>SSN</td>
                <td>Date of Birth</td>
                <td>Username</td>
                
           </tr>
           <tr>
           		<td><%=cust_fname%></td>
           		<td><%=cust_lname%></td>
                <td><%=cust_ssn%></td>
                <td><%=cust_dob%></td>
                <td><%=cust_uname%></td>
           </tr>
       </table>
</body>
</html>