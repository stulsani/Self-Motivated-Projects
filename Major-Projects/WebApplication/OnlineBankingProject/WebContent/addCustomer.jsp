<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Insert title here</title>
</head>
<body>
<h1><center>Add a new customer</center></h1>
<form method="Get" action="AddCustomerServlet">
        <table>
        	<tr><td>First Name</td>
                <td><input type="text" name="fname"></td>
            </tr>
            <tr><td>Last Name</td>
                <td><input type="text" name="lname"></td>
            </tr>
            <tr><td>SSN</td>
                <td><input type="text" name="ssn"></td>
            </tr>
            <tr><td>Date of Birth</td>
                <td><input type="text" name="dob"></td>
            </tr>
            <tr><td>Email Id</td>
                <td><input type="text" name="email"></td>
            </tr>
            <tr><td>Account State</td>
                <td><input type="text" name="acctState"></td>
            </tr>
            <tr><td>Username</td>
                <td><input type="text" name="uname"></td>
            </tr>
            <tr><td>Password</td>
                <td><input type="text" name="password"></td>
            </tr>
            <tr><td>Balance</td>
                <td><input type="text" name="balance"></td>
            </tr>
            <tr><td>Interest Rate:</td>
                <td><input type="text" name="intrate"></td>
            </tr>
            <tr><td>Category:</td>
                <td><input type="text" name="cust_categ"></td>
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
                    <input type="submit" value="Submit">
                    <input type="reset" value="Reset">
                </td>
            </tr>
        </table>
    </form>
</body>
</html>