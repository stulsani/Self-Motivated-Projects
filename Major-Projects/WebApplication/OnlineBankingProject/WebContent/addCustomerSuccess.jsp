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
		Object name = session.getAttribute("adm_name");
		Object uname = session.getAttribute("uname");
		Object adm_pass = session.getAttribute("adm_pass");
		%>
		<%-- <p><%=name%></p> --%>
        <center><h1>Welcome <%=name%></h1><br>
        <a href="AdminServlet?admin_uname=<%=uname%>&admin_pass=<%=adm_pass%>">Dashboard</a>
        <a href="LogoutServlet">Logout</a>
        <a href="AdminProfileServlet">Profile</a>
        </center>
Successfully added the customer.
</body>
</html>