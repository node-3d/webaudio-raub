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
		Napi::Object that,
		const char* name,
		int argc = 0,
		const Napi::Value *argv = nullptr
	);
	
	void emitAsync(
		Napi::Object that,
		const char* name,
		int argc = 0,
		const Napi::Value *argv = nullptr
	);
	
	bool _isDestroyed;
	
	Napi::ObjectReference _context;
	Napi::AsyncContext asyncCtx;
	
	JS_GETTER(isDestroyedGetter);
	JS_METHOD(destroy);
	
};

struct CommonNode: public Common {
	
	typedef std::shared_ptr<lab::AudioNode> NodePtr;
	
	CommonNode(Napi::Env env, const char *name);
	~CommonNode();
	
	void _destroy();
	
	NodePtr getNode() const;
	
	void reset(Napi::Object context, NodePtr node);
	
	NodePtr _impl;
	
};

struct CommonParam: public Common {
	
	typedef std::shared_ptr<lab::AudioParam> ParamPtr;
	
	CommonParam(Napi::Env env, const char *name);
	~CommonParam();
	
	void _destroy();
	
	ParamPtr getParam() const;
	
	void reset(Napi::Object context, ParamPtr param);
	
	ParamPtr _impl;
	
};

struct CommonCtx: public Common {
	
	typedef std::shared_ptr<lab::AudioContext> CtxPtr;
	
	CommonCtx(Napi::Env env, const char *name);
	~CommonCtx();
	
	void _destroy();
	
	CtxPtr getCtx() const;
	
	void reset(CtxPtr ctx);
	
	CtxPtr _impl;
	
};

struct CommonBus: public Common {
	
	typedef std::shared_ptr<lab::AudioBus> BusPtr;
	
	CommonBus(Napi::Env env, const char *name);
	~CommonBus();
	
	void _destroy();
	
	BusPtr getBus() const;
	
	void reset(Napi::Object context, BusPtr ctx);
	
	BusPtr _impl;
	
};

struct CommonListener: public Common {
	
	typedef std::shared_ptr<lab::AudioListener> ListenerPtr;
	
	CommonListener(Napi::Env env, const char *name);
	~CommonListener();
	
	void _destroy();
	
	ListenerPtr getListener() const;
	
	void reset(Napi::Object context, ListenerPtr ctx);
	
	ListenerPtr _impl;
	
};

#endif // _COMMON_HPP_
