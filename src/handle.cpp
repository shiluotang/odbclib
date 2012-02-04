#include "../include/diaginfoeventargs.hpp"
#include "../include/diaginfo.hpp"
#include "../include/handle.hpp"


#include "../include/utils/utils.hpp"
#include <iostream>
using namespace std;
using namespace odbclib;
using namespace odbclib::handletypes;

namespace
{
	using namespace std;
	using namespace odbclib;
	class DefaultDiagInfoListener:
		public DiagInfo::DiagInfoListener
	{
		public:
			virtual void 
			onEvent(DiagInfo::DiagInfoEvent &e,DiagInfoEventArgs const& args)
			{
				cout << "[DIAGINFO]: " << args.getDiagInfo() << endl;
			}
	};
}

DefaultDiagInfoListener DEFAULT_DIAG_LISTENER;

NS_BEGIN_1(odbclib)

Handle::HandleInfo::HandleInfo(SQLSMALLINT type)
	:m_handle(SQL_NULL_HANDLE),
	m_type(type)
{}

Handle::Handle(Handle *parentHandle,HandleType handleType)
try
	:m_handleInfo(handleType)
{
	DEBUG_INIT((string("Handle type=") + to_string(getType())).c_str());
	SQLRETURN ret = SQLAllocHandle(m_handleInfo.m_type,
		parentHandle == 0 ? SQL_NULL_HANDLE : parentHandle->getHandle(),
		&m_handleInfo.m_handle);
	if(!parentHandle)
		parentHandle->checkError(ret);
	else if(!SQL_SUCCEEDED(ret))
		throw runtime_error("failed to alloc handle");
	m_diagEvent.addListener(DEFAULT_DIAG_LISTENER);
}
catch(...){throw;}

Handle::~Handle()
try
{
	DEBUG_RELEASE((string("Handle type=") + to_string(getType())).c_str());
	SQLRETURN ret = SQLFreeHandle(m_handleInfo.m_type,
		m_handleInfo.m_handle);
	checkError(ret);
	m_handleInfo.m_handle = 0;
}
catch(...){throw;}

SQLRETURN
Handle::getAttribute(SQLINTEGER attrb,SQLPOINTER array,SQLINTEGER len,SQLINTEGER* outLen)
{
	SQLRETURN ret = 0;
	SQLRETURN (SQL_API *fp)(SQLHANDLE,SQLINTEGER,SQLPOINTER,SQLINTEGER,SQLINTEGER*) = 0;
	switch(m_handleInfo.m_type)
	{
		case handletypes::Environment:
			fp = &SQLGetEnvAttr;
			break;
		case handletypes::Connection:
			fp = &SQLGetConnectAttr;
			break;
		case handletypes::Statement:
			fp = &SQLGetStmtAttr;
			break;
		default:
			throw runtime_error("Handle::getAttribute is"\
					"not supported of this handle type");
	}
	ret = (*fp)(m_handleInfo.m_handle,
				attrb,
				(SQLPOINTER)array,
				len,
				outLen);
	return ret;
}

SQLRETURN 
Handle::setAttribute(SQLINTEGER attrb,SQLPOINTER array,SQLINTEGER len)
{
	SQLRETURN ret = 0;
	SQLRETURN (SQL_API *fp)(SQLHANDLE,SQLINTEGER,SQLPOINTER,SQLINTEGER) = 0;
	switch(m_handleInfo.m_type)
	{
		case handletypes::Environment:
			fp = &SQLSetEnvAttr;
			break;
		case handletypes::Connection:
			fp = &SQLSetConnectAttr;
			break;
		case handletypes::Statement:
			fp = &SQLSetStmtAttr;
			break;
		default:
			throw std::runtime_error("Handle::getAttribute is"\
					"not supported of this handle type");
	}
	ret = (*fp)(m_handleInfo.m_handle,
				attrb,
				(SQLPOINTER)array,
				len);
	return ret;
}

void
Handle::checkError(SQLRETURN retcode) 
{
	if(!SQL_SUCCEEDED(retcode))
	{
		stringstream ss;
		vector<DiagInfo> const& infos = 
			DiagInfo::getDiagInfos(retcode,*this);
		for(vector<DiagInfo>::const_iterator iter = infos.begin();
				iter != infos.end(); ++iter)
		{
			m_diagEvent.occur(DiagInfoEventArgs(*this,*iter));
			ss << *iter << endl;
		}
		throw runtime_error(ss.str());
	}
	else if(retcode == SQL_SUCCESS_WITH_INFO)
	{
		vector<DiagInfo> const& infos = 
			DiagInfo::getDiagInfos(retcode,*this);
		for(vector<DiagInfo>::const_iterator iter = infos.begin();
				iter != infos.end(); ++iter)
			m_diagEvent.occur(DiagInfoEventArgs(*this,*iter));
	}
}

NS_END_1
