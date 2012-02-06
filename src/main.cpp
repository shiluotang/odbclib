#include "../include/odbclib.hpp"

#include <cstdlib>
#include <iostream>

using namespace std;
using namespace odbclib;

void 
test_odbc()
{
	string const CONNSTR_MSACCESS = 
		"DRIVER={Microsoft Access Driver (*.mdb)};"\
		"DBQ=..\\data.mdb;"\
		"UID=Admin;PWD=;";
	string const CONNSTR_MSSQL = 
		"DRIVER={SQL SERVER};"\
		"SERVER=(local);"\
		"DATABASE=test;"\
		"UID=sa;PWD=123;";
	string const QUERY0 = "select {fn to_date(id)} from \"SQL\"";
	string const QUERY = "INSERT INTO [Students]([Name],[Age])"\
			     " VALUES('sqg',27);";
	string const QUERY2 = "SELECT * FROM [Students];";
	Environment env;
	Connection conn(env);
	Session s(conn,CONNSTR_MSACCESS);
	Transaction tran(s);
	Statement stmt(s);
	cout << "native sql statement is:" << endl
		<< conn.nativeSQL(QUERY0) << endl;
	cout << "cursor type: " << stmt.getCursorType() << endl;
	try
	{
		cout << "cursor scrollable: " 
			<< stmt.getCursorScrollable() << endl;
		cout << "cursor sensitivity: " 
			<< stmt.getCursorSensitivity() << endl;
	}
	catch(runtime_error &error)
	{
		cerr << error.what() << endl;
	}
	stmt.execute(QUERY);
	cout << "has resultset: " << stmt.hasResultSet() << endl;
	stmt.execute(QUERY2);
	tran.rollback();
}

static 
void
print_error(SQLSMALLINT handleType,SQLHANDLE handle)
{
	SQLCHAR state[7] = {0};
	SQLINTEGER error_code = 0;
	SQLCHAR message[0xff] = {0};
	SQLSMALLINT i = 0;
	SQLSMALLINT len = 0;
	SQLRETURN ret = 0;

	while(SQL_SUCCEEDED(ret = SQLGetDiagRec(
			handleType,
			handle,
			++i,
			state,
			&error_code,
			message,
			sizeof(message),
			&len)))
	{
		cout << state 
		<< ":" 
		<< error_code 
		<< ":" 
		<< message 
		<< endl;
		memset(state,0,sizeof(state));
		memset(message,0,sizeof(message));
	}
}

void 
test_mssql_native_client_10_sqlgetdata()
{
	string const CONNSTR = "DRIVER={SQL Server Native Client 10.0};"\
				"SERVER=sgaqcomputer;"\
				"DATABASE=some_db;UID=sa;PWD=123123";
	string const QUERY = "SELECT * FROM [在线造价_12_文件信息]";
	SQLHANDLE env = SQL_NULL_HANDLE,
		  dbc = SQL_NULL_HANDLE,
		  stmt = SQL_NULL_HANDLE;
	SQLRETURN ret = 0;
	ret = SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&env);
	if(!SQL_SUCCEEDED(ret))
		goto alloc_env_failed;
	ret = SQLSetEnvAttr(env,SQL_ATTR_ODBC_VERSION,(SQLPOINTER)SQL_OV_ODBC3,SQL_IS_UINTEGER);
	if(!SQL_SUCCEEDED(ret))
		goto set_env_ver_failed;
	ret = SQLAllocHandle(SQL_HANDLE_DBC,env,&dbc);
	if(!SQL_SUCCEEDED(ret))
		goto alloc_dbc_failed;
	ret = SQLDriverConnect(dbc,0,
		(SQLCHAR*)CONNSTR.c_str(),SQL_NTS,
		0,0,0,SQL_DRIVER_NOPROMPT);
	if(!SQL_SUCCEEDED(ret))
		goto connect_failed;
	ret = SQLAllocHandle(SQL_HANDLE_STMT,dbc,&stmt);
	if(!SQL_SUCCEEDED(ret))
		goto alloc_stmt_failed;
	ret = SQLExecDirect(stmt,(SQLCHAR*)QUERY.c_str(),SQL_NTS);
	if(!SQL_SUCCEEDED(ret))
		goto execute_failed;

	SQLINTEGER id;
	SQLCHAR filedata[0xff];
	SQLLEN id_indicator,filedata_indicator;
	while(SQL_SUCCEEDED(ret = SQLFetch(stmt)))
	{
		ret = SQLGetData(stmt,6,SQL_C_BINARY,
				filedata,
				sizeof(filedata),
				&filedata_indicator);
		if(!SQL_SUCCEEDED(ret))
			goto fetch_data_failed;
		if(filedata_indicator == SQL_NULL_DATA)
			cout << "<NULL>"; 
		else
			cout << "<BINARY DATA>";
		cout<< "\t";
		ret = SQLGetData(stmt,1,SQL_C_LONG,
				&id,
				sizeof(id),
				&id_indicator);
		if(!SQL_SUCCEEDED(ret))
			goto fetch_data_failed;
		if(id_indicator == SQL_NULL_DATA)
			cout << "<NULL>";
		else
			cout << id;
		cout << endl;
	}
	goto normal_close_cursor;
	fetch_data_failed:
		cout << endl;
		print_error(SQL_HANDLE_STMT,stmt);
	normal_close_cursor:
		SQLCloseCursor(stmt);
	execute_failed:
		SQLFreeHandle(SQL_HANDLE_STMT,stmt);
		stmt = SQL_NULL_HANDLE;
	alloc_stmt_failed:
		SQLDisconnect(dbc);
	connect_failed:
		SQLFreeHandle(SQL_HANDLE_DBC,dbc);
		dbc = SQL_NULL_HANDLE;
	alloc_dbc_failed:
	set_env_ver_failed:
		SQLFreeHandle(SQL_HANDLE_ENV,env);
		env = SQL_NULL_HANDLE;
	alloc_env_failed:;
}

int 
main(int argc,char* argv[])
{
	cout << boolalpha;
	try
	{
		test_odbc();
	}
	catch(exception& e)
	{
		cout << "[Exception]" << endl
		<< "==============================" << endl
		<< e.what() << endl
		<< "==============================" << endl;
	}
	system("pause");
	return EXIT_SUCCESS;
}

