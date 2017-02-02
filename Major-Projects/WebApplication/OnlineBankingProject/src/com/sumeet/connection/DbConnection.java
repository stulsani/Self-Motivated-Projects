package com.sumeet.connection;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

import com.sumeet.configs.SysConfigs;

public class DbConnection {

	public Connection getConnection() {
		return getMySQLConnection();
	}

	public Connection getMySQLConnection() {
		Connection dbConnection;

		try {
			Class.forName("oracle.jdbc.driver.OracleDriver");
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}

		try {
			dbConnection = DriverManager.getConnection(
					"jdbc:oracle:thin:@localhost:1521:xe", "banking",
					"Password1");
			dbConnection.setAutoCommit(false);

			return dbConnection;
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return null;
	}
}
