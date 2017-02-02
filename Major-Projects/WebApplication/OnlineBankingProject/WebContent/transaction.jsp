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
<form method="Get" action="TransactionServlet">
        <table>
        	<tr><td>Credit Account number</td>
                <td><input type="text" name="cdAcctNmbr"></td>
            </tr>
            <tr><td>Amount to transfer</td>
                <td><input type="text" name="amtTransfer"></td>
            </tr>
            <tr><td>Reamrks</td>
                <td><input type="text" name="remarks"></td>
            </tr>
            <tr><td>
                    <input type="submit" value="Transfer">
                    <input type="reset" value="Reset">
                </td>
            </tr>
        </table>
    </form>

</body>
</html>