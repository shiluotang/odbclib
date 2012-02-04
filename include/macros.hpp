#ifndef ODBCLIB_MACROS_HPP_INCLUDED
#define ODBCLIB_MACROS_HPP_INCLUDED

#define NS_BEGIN_1(NS1) namespace NS1{
#define NS_END_1 }

#define NS_BEGIN_2(NS2,NS1) NS_BEGIN_1(NS2) NS_BEGIN_1(NS1)
#define NS_END_2 NS_END_1 NS_END_1

#define NS_BEGIN_3(NS3,NS2,NS1) NS_BEGIN_2(NS3,NS2) NS_BEGIN_1(NS1)
#define NS_END_3 NS_END_2 NS_END_1

#define ENUM_BEGIN(ENUM_TYPE) typedef enum tag##ENUM_TYPE {
#define ENUM_ITEM_PAIR(ENUM_NAME,ENUM_VALUE) ENUM_NAME = ENUM_VALUE,
#define ENUM_ITEM(ENUM_NAME) ENUM_NAME,
#define ENUM_END(ENUM_TYPE) ENUM_TYPE##_EnumEnd} ENUM_TYPE;

#define ENUM_OUTPUT_BEGIN(ENUM_TYPE) \
	std::ostream& operator<<(std::ostream& os,ENUM_TYPE e)\
{\
	switch(e)\
	{
#define ENUM_OUTPUT_ITEM(ENUM_NAME) \
		case ENUM_NAME:	return os << #ENUM_NAME ;
#define ENUM_OUTPUT_ITEM_PAIR(ENUM_NAME,ENUM_VALUE) ENUM_OUTPUT_ITEM(ENUM_NAME)

#define ENUM_OUTPUT_END(ENUM_TYPE) \
		default: return os << "The value " << (int)e \
			 << " is not defined in enum type "\
			<< #ENUM_TYPE;\
	}\
}

#define ENUM_OUTPUT_DECL(ENUM_TYPE) extern std::ostream& operator<<(std::ostream&,ENUM_TYPE);

#endif
