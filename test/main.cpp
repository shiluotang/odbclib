#include "../src/odbcxx.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;
using namespace odbcxx;

int main(int argc, char* argv[]) {
	char const *connstr = "DRIVER={MySQL ODBC 5.1 Driver};"
		"SERVER=localhost;"
		"PORT=3306"
		"DATABASE=test;"
		"DBQ=test;"
		"UID=root;";
	char const *sql = "insert into students(sid, name) values(100, 'what');";
	char const *sql2 = "insert into students(sid, name) values(1000, 'what');";

	cout << boolalpha;
	clog << boolalpha;
	cerr << boolalpha;

	environment env;
	connection conn;
	session ss;
	statement stmt;
	cursor c;

	env.alloc(conn);
	conn.driver_connect(ss, connstr);
	ss.alloc(stmt);

	clog << conn.current_catalog("test") << endl;
	
	if (stmt.execute(c, "SELECT * FROM STUDENTS")) {
		size_t rows = 0U;
		while (c.next() && !c.eof())
			++rows;
		clog << "There're " << rows << " rows." << endl;
	}

	return EXIT_SUCCESS;
}
