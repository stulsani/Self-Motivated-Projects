<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
        <title>Customer Login</title>
       
    </head>
    <body bgcolor="orange">
         <center><h1>Customer Login </h1><br>
    <form method="Get" action="CustomerLoginServlet">
        <table>
            <tr>
                <td>
                    Username:
                </td>
                <td>
                    <input type="text" name="cust_uname">          
                </td>
            </tr>
            <tr>
                <td>
                    Password:
                </td>
                <td>
                    <input type="password" name="cust_pass">
                </td>
            </tr>
            <tr>
                <td>
                    
                </td>
                <td>
                    <input type="submit" value="Login">
                    <input type="reset" value="Reset">
                </td>
                <td>
                    
                </td>
            </tr>
        </table>
    </form>
    </center>
    </body>
</html>