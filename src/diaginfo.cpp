#include "../include/handle.hpp"
#include "../include/diaginfo.hpp"

#include <sstream>

using namespace std;
using namespace odbclib::diags;

NS_BEGIN_1(odbclib)

DiagInfo::DiagInfo()
	:m_nativeErrorCode(0)
{

}

DiagInfo::DiagInfo(SQLCHAR const* state,
		SQLINTEGER nativeErrorCode,
		SQLCHAR const* message,
		DiagLevel level)
	:m_nativeErrorCode(0),
	m_level(level)
{
	memcpy(m_state,state,sizeof(m_state));
	m_state[sizeof(m_state) - 1] = 0;
	memcpy(m_message,message,sizeof(m_message));
	m_message[sizeof(m_message) - 1] = 0;
	m_nativeErrorCode = nativeErrorCode;
}

string
DiagInfo::toString()const
{
	stringstream ss;
	ss << *this;
	return ss.str();
}

vector<DiagInfo>
DiagInfo::getDiagInfos(SQLRETURN retcode,Handle const& handle)
{
	vector<DiagInfo> diaglist;
	if(retcode == SQL_SUCCESS)
		return diaglist;
	DiagInfo diag;
	diag.m_level = (retcode == SQL_SUCCESS_WITH_INFO ? Warning : Error);
	SQLRETURN ret = 0;
	SQLSMALLINT i = 0;
	SQLSMALLINT len = 0;
	do
	{
		memset(diag.m_state,0,sizeof(diag.m_state));
		memset(diag.m_message,0,sizeof(diag.m_message));
		ret = SQLGetDiagRec(
				handle.getType(),
				handle.getHandle(),
				++i,
				diag.m_state,
				&diag.m_nativeErrorCode,
				diag.m_message,
				sizeof(diag.m_message),
				&len);
		if(SQL_SUCCEEDED(ret))
			diaglist.push_back(diag);
	}while(ret == SQL_SUCCESS);
	return diaglist;
}

ostream& operator<<(ostream& os,DiagInfo const& diag)
{
	os << diag.m_state << ":" 
	<< diag.m_nativeErrorCode << ":"
	<< diag.m_message;
	return os;
}

NS_END_1
