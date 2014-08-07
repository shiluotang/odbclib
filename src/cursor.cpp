#include "cursor.hpp"
#include "statement.hpp"

#include <utility>

using namespace std;

namespace odbcxx {

	cursor::cursor() :m_stmt_ptr(0) {}
	cursor::cursor(cursor &&other)
		:m_stmt_ptr(0) {
		std::swap(m_stmt_ptr, other.m_stmt_ptr);
	}
	cursor& cursor::operator = (cursor &&other) {
		if (this == &other)
			return *this;
		m_stmt_ptr = other.m_stmt_ptr;
		other.m_stmt_ptr = 0;
		return *this;
	}
	cursor::~cursor() { close(); }

	cursor::operator bool() const
	{ return m_stmt_ptr != 0 && static_cast<bool>(*m_stmt_ptr); }

	cursor& cursor::close() {
		if (m_stmt_ptr) {
			m_stmt_ptr->close_cursor();
			m_stmt_ptr = 0;
		}
		return *this;
	}
}
