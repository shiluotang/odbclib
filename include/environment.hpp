#ifndef ODBCLIB_ENVIRONMENT_HPP_INCLUDED
#define ODBCLIB_ENVIRONMENT_HPP_INCLUDED

#include "config.hpp"
#include "macros.hpp"
#include "types.hpp"

#include "component.hpp"

NS_BEGIN_1(odbclib)

class Environment
	:protected Component
{
	public:
		Environment();
		virtual ~Environment();

		void commit();
		void rollback();
		inline 
		odbclib::environmentversions::EnvironmentVersion
		getVersion()const{return m_version;}
	protected:
		virtual void doDispose();
		void setVersion(
			odbclib::environmentversions::EnvironmentVersion);
	private:
		odbclib::environmentversions::EnvironmentVersion
			m_version;
		Handle *m_handle;

		friend class Connection;
};

NS_END_1

#endif
