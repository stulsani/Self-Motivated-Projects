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
		Object cust_name = session.getAttribute("cust_name");
		Object cust_last_name = session.getAttribute("cust_last_name");
		Object cust_uname = session.getAttribute("cust_uname");
		Object cust_pass = session.getAttribute("cust_pass");
		%>
		<%-- <p><%=name%></p> --%>
        <center><h1><%=cust_name%> Profile</h1><br>
        <a href="CustomerLoginServlet?cust_uname=<%=cust_uname%>&cust_pass=<%=cust_pass%>">Dashboard</a>
        <a href="customerProfileEdit.jsp">Edit</a>
        <a href="LogoutServlet">Logout</a>
        </center>
        <br>
        <table border=1>
        	<tr>
           		<td>Account Id</td>
           		<td>First Name</td>
                <td>Last Name</td>
                <td>Username</td>
                <td>Password</td>
           </tr>
           <tr>
           		<td><%=acct_id%></td>
           		<td><%=cust_name%></td>
                <td><%=cust_last_name%></td>
                <td><%=cust_uname%></td>
                <td><%=cust_pass%></td>
           </tr>
       </table>
</body>
</html>