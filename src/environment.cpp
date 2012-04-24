#include "../include/environment.hpp"

#include <iostream>
using namespace std;
using namespace odbclib;
using namespace odbclib::environment;

NS_BEGIN_1(odbclib)

Environment::Environment()
try
	:m_handle(new Handle(0,odbclib::handle::Environment))
{
	DEBUG_INIT("Environment");
	setVersion(ODBC3);
}
catch(...)
{
	doDispose();
	throw;
}

Environment::~Environment()
{
	DEBUG_RELEASE("Environment");
	dispose();
}

void
Environment::setVersion(EnvironmentVersion version)
{
	SQLUINTEGER ver = //static_cast<SQLUINTEGER>(4UL);
		static_cast<SQLUINTEGER>(version);
	SQLRETURN ret = m_handle->setAttribute(SQL_ATTR_ODBC_VERSION,ver);
	m_handle->checkError(ret);
	m_version = version;
}

void
Environment::doDispose()
{
	delete m_handle;
	m_handle = 0;
}

void
Environment::commit()
{
	SQLRETURN ret = SQLEndTran(m_handle->getType(),
		m_handle->getHandle(),SQL_COMMIT);
	m_handle->checkError(ret);
}

void
Environment::rollback()
{
	SQLRETURN ret = SQLEndTran(m_handle->getType(),
		m_handle->getHandle(),SQL_ROLLBACK);
	m_handle->checkError(ret);
}

NS_END_1

