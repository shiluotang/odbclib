#include "../include/debug.hpp"
#include <iostream>

using namespace std;

void debug_msg(char const* msg)
{
	cout << "[DEBUG]:" << msg << endl;
}

void debug_init(char const* type_name)
{
	cout << "[DEBUG]:" << "[" << type_name << "] constructing..." << endl;
}
void debug_release(char const* type_name)
{
	cout << "[DEBUG]:" << "[" << type_name << "] destructing..." << endl;
}
