#ifndef ODBCLIB_DIAGINFO_HPP_INCLUDED
#define ODBCLIB_DIAGINFO_HPP_INCLUDED

#include "config.hpp"
#include "types.hpp"
#include "macros.hpp"

#include "utils/event/event.hpp"
#include "utils/event/eventlistener.hpp"

#include <string>

NS_BEGIN_1(odbclib)

class Handle;
class DiagInfoEventArgs;
class DiagInfo
{
	private:
		DiagInfo();
	public:
		typedef odbclib::utils::event::Event<DiagInfoEventArgs> DiagInfoEvent;
		typedef odbclib::utils::event::EventListener<DiagInfoEventArgs> DiagInfoListener;

		DiagInfo(SQLCHAR const*,
			SQLINTEGER,
			SQLCHAR const*,
			diagnostics::DiagLevel);
		inline 
		SQLCHAR const* 
		getState() const{return m_state;}
		inline 
		SQLCHAR const* 
		getMessage() const{return m_message;}
		inline 
		SQLINTEGER 
		getNativeErrorCode()const{return m_nativeErrorCode;}
		inline
		diagnostics::DiagLevel
		getLevel() const{return m_level;}
		std::string toString() const;

		static
		std::vector<DiagInfo> getDiagInfos(SQLRETURN,Handle const&);
	private:
		SQLCHAR m_state[7];
		SQLINTEGER m_nativeErrorCode;
		SQLCHAR m_message[0x1 << 10];
		diagnostics::DiagLevel m_level;

	friend std::ostream& operator<<(std::ostream&,
			DiagInfo const&);
	friend class Handle;
};

extern std::ostream& operator << (std::ostream&,DiagInfo const&);

NS_END_1

#endif
