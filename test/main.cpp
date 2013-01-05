#include "../src/odbcxx.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;
using namespace odbcxx;

int main(int argc, char* argv[]) {
	char const * connstr = "DRIVER={MySQL};SERVER=localhost;"\
				"DATABASE=db_test;"\
				"UID=root;PWD=123";
	cout << boolalpha;
	cout << "Welcome to odbcxx library." << endl;

	return EXIT_SUCCESS;
}
