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
		%>
		<%-- <p><%=name%></p> --%>
        <center><h1>Welcome <%=name%></h1><br>
        <a href="searchCustomer.jsp">Search Customer</a>
        <a href="LogoutServlet">Logout</a>
        <a href="AdminProfileServlet">Profile</a>
        <a href="deleteCust.jsp">Delete a customer</a>
        </center>
        <!-- <form method="Get" action="LogoutServlet">
        
        <a>Logout</a>
        </form>
        
        <form method="Get" action="AdminProfileServlet">
        
        <a>Profile</a> </center>
        </form> -->
        <!--<a href="CreateEventServlet">Create Event</a>
        <a href="DisplayEventServlet">Display Event</a>-->
        

<!-- <div id="dashboard"> -->
	<!-- <div class="row"> -->
		<a href="addCustomer.jsp"
			class="span4""> <img class="img-circle"
			src="images/user_add.png" style="width: 120px;" />
			<!-- <br /> -->
		<h5>New Customer Account</h5>
		</a> 
		<a href="searchCustomer.jsp"
			class="span4""> <img class="img-circle"
			src="images/user_search.png" style="width: 120px;" />
			<br />
		<h5>Search Customer Account</h5>
		</a>
	<!-- </div> -->
<!-- </div> -->
    </body>
</html>