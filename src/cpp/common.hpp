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
	
	Common(const char *asyncName);
	~Common();
	
	void _destroy();
	
	void emit(
		const Napi::CallbackInfo& info,
		const char* name,
		int argc = 0,
		const Napi::Value *argv = nullptr
	);
	
	void emitAsync(
		const Napi::CallbackInfo& info,
		const char* name,
		int argc = 0,
		const Napi::Value *argv = nullptr
	);
	
	bool _isDestroyed;
	
	Napi::AsyncContext asyncCtx;
	
	JS_GETTER(isDestroyedGetter);
	JS_METHOD(destroy);
	
};

struct CommonNode: public Common {
	
	typedef std::shared_ptr<lab::AudioNode> NodePtr;
	
	CommonNode(): Common("AudioNode") {};
	~CommonNode();
	
	void _destroy();
	
	NodePtr getNode() const;
	
	void reset(Napi::Object context, NodePtr node);
	
	NodePtr _impl;
	Napi::ObjectReference _context;
	
};

struct CommonParam: public Common {
	
	typedef std::shared_ptr<lab::AudioParam> ParamPtr;
	
	CommonParam(): Common("AudioParam") {};
	~CommonParam();
	
	void _destroy();
	
	ParamPtr getParam() const;
	
	void reset(Napi::Object context, ParamPtr param);
	
	ParamPtr _impl;
	Napi::ObjectReference _context;
	
};

struct CommonCtx: public Common {
	
	typedef std::shared_ptr<lab::AudioContext> CtxPtr;
	
	CommonCtx(): Common("AudioContext") {};
	~CommonCtx();
	
	void _destroy();
	
	CtxPtr getCtx() const;
	
	void reset(CtxPtr ctx);
	
	CtxPtr _impl;
	
};

#endif // _COMMON_HPP_
