#ifndef _COMMON_HPP_
#define _COMMON_HPP_

#include <memory>

#include <addon-tools.hpp>


#define PARAM_GETTER(CLASS, NAME)                                             \
JS_GETTER(CLASS::NAME ## Getter) { THIS_CHECK;                                \
	RET_VALUE(_ ## NAME.Value());                                             \
}


namespace lab {
	class AudioNode;
	class AudioParam;
	class AudioContext;
};


struct Common {
	
	// Destroy an instance from C++ land
	void _destroy();
	
	~Common();
	Common();
	
	JS_GETTER(isDestroyedGetter);
	JS_METHOD(destroy);
	
	void emit(
		const Napi::CallbackInfo& info,
		const char* name,
		int argc = 0,
		const Napi::Value *argv = nullptr
	);
	
	bool _isDestroyed;
	
};

struct CommonNode: public Common {
	
	typedef std::shared_ptr<lab::AudioNode> NodePtr;
	
	NodePtr getNode() const;
	
	void _destroy();
	
	~CommonNode();
	void reset(Napi::Object context, NodePtr node);
	
	NodePtr _impl;
	Napi::ObjectReference _context;
	
};

struct CommonParam: public Common {
	
	typedef std::shared_ptr<lab::AudioParam> ParamPtr;
	
	ParamPtr getParam() const;
	
	void _destroy();
	
	~CommonParam();
	void reset(Napi::Object context, ParamPtr param);
	
	ParamPtr _impl;
	Napi::ObjectReference _context;
	
};

struct CommonCtx: public Common {
	
	typedef std::shared_ptr<lab::AudioContext> CtxPtr;
	
	CtxPtr getCtx() const;
	
	void _destroy();
	
	~CommonCtx();
	void reset(CtxPtr ctx);
	
	CtxPtr _impl;
	
};

#endif // _COMMON_HPP_
