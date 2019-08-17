#ifndef _COMMON_HPP_
#define _COMMON_HPP_

#include <memory>

#include <addon-tools.hpp>


#define CACHE_CAS(CACHE, V)                                                   \
	if (CACHE == V) {                                                         \
		return;                                                               \
	}                                                                         \
	CACHE = V;

#define THIS_SETTER_CHECK                                                \
	NAPI_ENV;                                                                 \
	if (_isDestroyed) return;

#define PARAM_GETTER(CLASS, NAME)                                             \
JS_GETTER(CLASS::NAME ## Getter) { THIS_CHECK;                                \
	RET_VALUE(_ ## NAME.Value());                                             \
}


namespace lab {
	class AudioNode;
	class AudioParam;
};


struct Common {
	
	bool _isDestroyed;
	Napi::ObjectReference _context;
	
	// Destroy an instance from C++ land
	void _destroy();
	
	~Common();
	Common();
	void reset(Napi::Object context);
	
	JS_GETTER(isDestroyedGetter);
	JS_METHOD(destroy);
	
	void emit(
		const Napi::CallbackInfo& info,
		const char* name,
		int argc = 0,
		Napi::Value *argv = nullptr
	);
	
};
struct CommonNode: public Common {
	
	typedef std::shared_ptr<lab::AudioNode> NodePtr;
	
	NodePtr _impl;
	
	NodePtr getNode() const;
	
	~CommonNode();
	CommonNode();
	void reset(Napi::Object context, NodePtr node);
	
};

struct CommonParam {
	
	typedef std::shared_ptr<lab::AudioParam> ParamPtr;
	
	ParamPtr _impl;
	Napi::ObjectReference _context;
	
	ParamPtr getParam() const;
	
	~CommonParam();
	CommonParam();
	void reset(Napi::Object context, ParamPtr param);
	
};


#endif // _COMMON_HPP_
