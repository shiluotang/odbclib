#include "../src/odbcxx.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;
using namespace odbcxx;

int test1(int argc, char* argv[]) {
	char const *connstr = "DRIVER={MySQL ODBC 5.1 Driver};"
		"SERVER=localhost;"
		"PORT=3306;"
		"DATABASE=test;"
		"DBQ=test;"
		"UID=root;";
	//char const *sql = "insert into students(sid, name) values(100, 'what');";
	//char const *sql2 = "insert into students(sid, name) values(1000, 'what');";

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
	stmt.rowset_size(2);

	clog << conn.current_catalog("test") << endl;

	long no;
	string name;
	long age;
	bool is_null;

	if (stmt.execute(c, "SELECT * FROM STUDENTS")) {
		size_t rows = 0U;
		while (c.next() && !c.eof()) {
			for (int i = 0; i < 2; ++i) {
				stmt.set_pos_in_rowset(i + 1, SQL_POSITION, SQL_LOCK_NO_CHANGE);
				stmt.get_data(1, no, is_null);
				stmt.get_data(2, name, is_null);
				stmt.get_data(3, age, is_null);
				clog << "no = " << no
					<< ", name = " << name
					<< ", age = " << age
					<< endl;
			}
			++rows;
		}
		clog << "There're " << rows << " rows." << endl;
	}
	return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
	try {
		test1(argc, argv);
	} catch(exception &e) {
		cerr << e.what() << endl;
	}
	return EXIT_SUCCESS;
}
