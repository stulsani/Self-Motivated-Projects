<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
<h1>Employee Form Bean Value</h1>


<jsp:useBean id="emp" class="mypackage.Employee" scope="page" />
<jsp:setProperty name="emp" property="firstName" value="Sumeet"/>
<jsp:setProperty name="emp" property="lastName" value="Tulsani"/>
<jsp:setProperty name="emp" property="address" value="USA"/>

	<table>
      <tr>
       <td>First Name</td>
       <td> : </td>
       <td> <jsp:getProperty name="emp" property="firstName"/> </td>
      </tr>
      <tr>
       <td>Last Name</td>
       <td> : </td>
       <td> <jsp:getProperty name="emp" property="lastName"/> </td>
      </tr>
      <tr>
       <td>Address</td>
       <td> : </td>
       <td> <jsp:getProperty name="emp" property="address"/> </td>
      </tr>
     </table>

</body>
</html>