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
	
	Common(Napi::Env env, const char *name);
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
	
	CommonNode(Napi::Env env, const char *name): Common(env, name) {};
	~CommonNode();
	
	void _destroy();
	
	NodePtr getNode() const;
	
	void reset(Napi::Object context, NodePtr node);
	
	NodePtr _impl;
	Napi::ObjectReference _context;
	
};

struct CommonParam: public Common {
	
	typedef std::shared_ptr<lab::AudioParam> ParamPtr;
	
	CommonParam(Napi::Env env, const char *name): Common(env, name) {};
	~CommonParam();
	
	void _destroy();
	
	ParamPtr getParam() const;
	
	void reset(Napi::Object context, ParamPtr param);
	
	ParamPtr _impl;
	Napi::ObjectReference _context;
	
};

struct CommonCtx: public Common {
	
	typedef std::shared_ptr<lab::AudioContext> CtxPtr;
	
	CommonCtx(Napi::Env env, const char *name): Common(env, name) {};
	~CommonCtx();
	
	void _destroy();
	
	CtxPtr getCtx() const;
	
	void reset(CtxPtr ctx);
	
	CtxPtr _impl;
	
};

struct CommonBus: public Common {
	
	typedef std::shared_ptr<lab::AudioBus> BusPtr;
	
	CommonBus(Napi::Env env, const char *name): Common(env, name) {};
	~CommonBus();
	
	void _destroy();
	
	BusPtr getBus() const;
	
	void reset(BusPtr ctx);
	
	BusPtr _impl;
	Napi::ObjectReference _context;
	
};

struct CommonListener: public Common {
	
	typedef std::shared_ptr<lab::AudioListener> ListenerPtr;
	
	CommonListener(Napi::Env env, const char *name): Common(env, name) {};
	~CommonListener();
	
	void _destroy();
	
	ListenerPtr getListener() const;
	
	void reset(ListenerPtr ctx);
	
	ListenerPtr _impl;
	Napi::ObjectReference _context;
	
};

#endif // _COMMON_HPP_
