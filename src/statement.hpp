#ifndef ODBCLIB_STATEMENT_HPP_INCLUDED
#define ODBCLIB_STATEMENT_HPP_INCLUDED

#include "config.hpp"
#include "macros.hpp"
#include "types.hpp"
#include "component.hpp"

NS_BEGIN_1(odbclib)

class Session;
class Cursor;
class Statement:
	protected Component
{
public:
	explicit Statement(Session &);
	virtual ~Statement();
	inline Session& getSession(){return m_session_ref;}

	void prepare(std::string const&);
	void execute();
	void execute(std::string const&);
	void cancel();
	bool hasResultSet();
	SQLLEN getAffectedRowCount();
protected:
	virtual void doDispose();
	void closeCursor();
public:
	std::string getCursorName();
	void setCursorName(std::string const&);
	void setCursorType(cursor::CursorType);
	cursor::CursorType getCursorType();
	void setCursorScrollable(cursor::CursorScrollable);
	cursor::CursorScrollable getCursorScrollable();
	void setCursorSensitivity(cursor::CursorSensitivity);
	cursor::CursorSensitivity getCursorSensitivity();
	void setCursorConcurrency(cursor::CursorConcurrency);
	cursor::CursorConcurrency getCursorConcurrency();
	void setCursorRowArraySize(std::size_t);
	size_t getCursorRowArraySize();
private:
	Session &m_session_ref;
	Handle  *m_handle;
	std::string m_preparedsql;
	bool m_prepared;
	Cursor *m_cursor_ptr;

	friend class Cursor;
};

NS_END_1

#endif //ODBCLIB_STATEMENT_HPP_INCLUDED
