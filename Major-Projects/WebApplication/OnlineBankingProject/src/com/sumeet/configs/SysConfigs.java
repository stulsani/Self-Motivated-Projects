package com.sumeet.configs;

public class SysConfigs {

	/* --- Names --- */
	public static final String name_App = "Online Banking";

	/* --- URL --- */
	public static final String url_Host = "http://localhost:8090/";
	public static final String url_AppPath = "OnlineBankingServlet/";
	public static final String url_Assets = url_Host + url_AppPath + "resources/";

	/* --- Database --- */
	public static final String db_Driver = "oracle.jdbc.driver.OracleDriver";
	public static final String db_ConnectionString = "jdbc:oracle:thin:@localhost:1521:xe";
	public static final String db_Username = "banking";
	public static final String db_Password = "Password1";
}
