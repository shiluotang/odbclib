#include "../include/cursor.hpp"
#include "../include/resultset.hpp"

using namespace std;

NS_BEGIN_1(odbclib)

ResultSet::ResultSet(Cursor &cursor)
	:m_cursor_ref(cursor)
{

}

NS_END_1
