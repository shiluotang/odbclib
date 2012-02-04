#ifndef ODBCLIB_RESULTSET_HPP_INCLUDED
#define ODBCLIB_RESULTSET_HPP_INCLUDED

#include "config.hpp"
#include "macros.hpp"
#include "types.hpp"

NS_BEGIN_1(odbclib)

class Cursor;
class ResultSet
{
	public:
		explicit ResultSet(Cursor &);

		bool next();
		bool previous();
		bool first();
		bool last();

		void* getData(std::size_t,std::size_t);
	protected:
	private:
		Cursor &m_cursor_ref;
};

NS_END_1

#endif

