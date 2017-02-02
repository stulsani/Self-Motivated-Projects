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
		Object name = session.getAttribute("cust_name");
		%>
		<%-- <p><%=name%></p> --%>
        <center><h1>Welcome <%=name%></h1><br>
        <a href="transaction.jsp">Transaction</a><br>
        <a href="LogoutServlet">Logout</a><br>
        <a href="CustomerProfileServlet">Profile</a><br>
        <!-- <a href="AdminProfileServlet">Edit</a> -->
        <a href="CustomerRequestServlet">Request for cheque book</a><br>
        </center>
</body>
</html>