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
		Object adm_id = session.getAttribute("adm_id");
		Object adm_name = session.getAttribute("adm_name");
		Object last_name = session.getAttribute("last_name");
		Object uname = session.getAttribute("uname");
		Object adm_pass = session.getAttribute("adm_pass");
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
           		<td>Admin Id</td>
           		<td>First Name</td>
                <td>Last Name</td>
                <td>Username</td>
                <td>Password</td>
           </tr>
           <tr>
           		<td><%=adm_id%></td>
           		<td><%=adm_name%></td>
                <td><%=last_name%></td>
                <td><%=uname%></td>
                <td><%=adm_pass%></td>
           </tr>
       </table>
</body>
</html>