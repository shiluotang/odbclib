#include "cursor.hpp"
#include "resultset.hpp"

using namespace std;

NS_BEGIN_1(odbclib)

ResultSet::ResultSet(Cursor &cursor)
	:m_cursor_ref(cursor)
{

}

bool
ResultSet::next(){return true;}

bool
ResultSet::previous(){return true;}

bool
ResultSet::first(){return true;}

bool
ResultSet::last(){return true;}

NS_END_1
