import java.io.*;  
import javax.servlet.*;  
import javax.servlet.http.*;  
  
  
public class LoginServlet extends HttpServlet {  
  
public void doPost(HttpServletRequest request, HttpServletResponse response)  
        throws ServletException, IOException {  
  
    response.setContentType("text/html");  
    PrintWriter out = response.getWriter();  
          
    String userName=request.getParameter("userName");  
    String userPass=request.getParameter("userPassword");  
          
    if(userName.equals("sumeet") && userPass.equals("sumeet123")){  
        RequestDispatcher rd=request.getRequestDispatcher("WelcomeServlet");  
        rd.forward(request, response);  
    }  
    else{  
        out.print("Sorry User Name or Password Error!");  
        RequestDispatcher rd=request.getRequestDispatcher("/login.html");  
        rd.include(request, response);  
                      
        }  
    }  
  
}  