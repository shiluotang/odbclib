#include "../src/odbcxx.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;
using namespace odbcxx;

int main(int argc, char* argv[]) {
	char const *connstr = "DRIVER={MySQL};SERVER=localhost;"\
				"DATABASE=db_test;"\
				"UID=root;PWD=123";
	char const *sql = "insert into students(sid, name) values(100, 'what');";
	char const *sql2 = "insert into students(sid, name) values(1000, 'what');";
	cout << boolalpha;
	cout << "Welcome to odbcxx library." << endl;
	environment env;
	connection conn;
	session ss;
	statement stmt;

	env.alloc(conn)
		.driver_connect(ss, connstr)
		.alloc(stmt);
	stmt.prepare(sql);
	stmt.execute();	

	ss.close();

	stmt.execute(sql2);
	stmt.execute();

	return EXIT_SUCCESS;
}
