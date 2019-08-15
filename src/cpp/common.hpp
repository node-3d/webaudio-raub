#ifndef _COMMON_HPP_
#define _COMMON_HPP_


#define CACHE_CAS(CACHE, V)                                                   \
	if (CACHE == V) {                                                         \
		return;                                                               \
	}                                                                         \
	CACHE = V;


#define PARAM_GETTER(CLASS, NAME)                                             \
JS_GETTER(CLASS::NAME ## Getter) { THIS_CHECK;                                \
	RET_VALUE(_ ## NAME.Value());                                             \
}


#endif // _COMMON_HPP_
