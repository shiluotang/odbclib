#ifndef ODBCLIB_RESULTSETMETADATA_HPP_INCLUDED
#define ODBCLIB_RESULTSETMETADATA_HPP_INCLUDED

#include "columnmetadata.hpp"
#include <vector>

NS_BEGIN_1(odbclib)

class ResultSetMetaData
{
public:
	inline
	size_t getColumnCount() const{return m_columns.size();}
	inline
	ColumnMetaData const& 
	getColumnMetaData(size_t index)const{return m_columns.at(index);}
private:
	std::vector<ColumnMetaData> m_columns;
};

NS_END_1

#endif //ODBCLIB_RESULTSETMETADATA_HPP_INCLUDED
