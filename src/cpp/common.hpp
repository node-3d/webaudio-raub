#ifndef _COMMON_HPP_
#define _COMMON_HPP_


#define CACHE_CAS(CACHE, V)                                                   \
	if (CACHE == V) {                                                         \
		return;                                                               \
	}                                                                         \
	CACHE = V;


#endif // _COMMON_HPP_
