<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Search Customer</title>
</head>
<body>
<form method="Get" action="SearchCustomerServlet">
        <table>
            <tr>
                <td>
                    Customer username:
                </td>
                <td>
                    <input type="text" name="cust_uname">          
                </td>
            </tr>
            
            <tr>
                <td>
                    
                </td>
                <td>
                    <input type="submit" value="Search">
                    <input type="reset" value="Reset">
                </td>
                <td>
                    
                </td>
            </tr>
        </table>
    </form>
</body>
</html>