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
	environment env;
	connection conn;
	session ss;
	statement stmt;
	cursor c;

	env.alloc(conn)
		.driver_connect(ss, connstr)
		.alloc(stmt);
	stmt.execute(c, sql);
	return EXIT_SUCCESS;
}
