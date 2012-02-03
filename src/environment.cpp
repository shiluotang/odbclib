#include "../include/environment.hpp"

#include <iostream>
using namespace std;
using namespace odbclib;
using namespace odbclib::environmentversions;

NS_BEGIN_1(odbclib)

Environment::Environment()
try
	:m_handle(new Handle(0,odbclib::handletypes::Environment))
{
	DEBUG_INIT("Environment");
	setVersion(ODBC3);
}
catch(...)
{
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
	SQLUINTEGER ver = static_cast<SQLUINTEGER>(version);
	if(!SQL_SUCCEEDED(m_handle->setAttribute(SQL_ATTR_ODBC_VERSION,ver)))
		throw runtime_error("environment version setting failed!");
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

