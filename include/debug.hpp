#ifndef ODBCLIB_DEBUG_HPP_INCLUDED
#define ODBCLIB_DEBUG_HPP_INCLUDED

extern void debug_msg(char const*);
extern void debug_init(char const*);
extern void debug_release(char const*);

#if defined(DEBUG)
#	define DEBUG_INIT(X) debug_init((X))
#	define DEBUG_RELEASE(X) debug_release((X))
#	define DEBUG_MSG(X) debug_msg((X))
#else
#	define DEBUG_INIT(X)
#	define DEBUG_RELEASE(X)
#	define DEBUG_MSG(X)
#endif

#endif //ODBCLIB_DEBUG_HPP_INCLUDED
