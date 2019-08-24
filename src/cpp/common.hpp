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


template <typename T>
struct Common : public Napi::ObjectWrap<T> {
	
	template <typename T>
	Common<T>(const Napi::CallbackInfo &info, const char *name):
	Napi::ObjectWrap<T>(info)
	asyncCtx(info, name) {
		_isDestroyed = false;
	};
	~Common() { _destroy(); };
	
	void _destroy();
	
	void emit(
		const char* name,
		int argc = 0,
		const Napi::Value *argv = nullptr
	);
	
	void emitAsync(
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

template <typename T>
struct CommonNode: public Common<T> {
	
	typedef std::shared_ptr<lab::AudioNode> NodePtr;
	
	template <typename T>
	CommonNode<T>(const Napi::CallbackInfo &info, const char *name):
	Common<T>(info, name) {
	};
	
	~CommonNode() { _destroy(); };
	
	void _destroy();
	
	NodePtr getNode() const;
	
	void reset(Napi::Object context, NodePtr node);
	
	NodePtr _impl;
	
};

template <typename T>
struct CommonParam: public Common<T> {
	
	typedef std::shared_ptr<lab::AudioParam> ParamPtr;
	
	template <typename T>
	CommonParam<T>(const Napi::CallbackInfo &info, const char *name):
	Common<T>(info, name) {
	};
	
	~CommonParam() { _destroy(); };
	
	void _destroy();
	
	ParamPtr getParam() const;
	
	void reset(Napi::Object context, ParamPtr param);
	
	ParamPtr _impl;
	
};

template <typename T>
struct CommonCtx: public Common<T> {
	
	typedef std::shared_ptr<lab::AudioContext> CtxPtr;
	
	template <typename T>
	CommonCtx<T>(const Napi::CallbackInfo &info, const char *name):
	Common<T>(info, name) {
	};
	
	~CommonCtx() { _destroy(); };
	
	void _destroy();
	
	CtxPtr getCtx() const;
	
	void reset(CtxPtr ctx);
	
	CtxPtr _impl;
	
};

template <typename T>
struct CommonBus: public Common<T> {
	
	typedef std::shared_ptr<lab::AudioBus> BusPtr;
	
	template <typename T>
	CommonBus<T>(const Napi::CallbackInfo &info, const char *name):
	Common<T>(info, name) {
	};
	
	~CommonBus() { _destroy(); };
	
	void _destroy();
	
	BusPtr getBus() const;
	
	void reset(Napi::Object context, BusPtr ctx);
	
	BusPtr _impl;
	
};

template <typename T>
struct CommonListener: public Common<T> {
	
	typedef std::shared_ptr<lab::AudioListener> ListenerPtr;
	
	template <typename T>
	CommonListener<T>(const Napi::CallbackInfo &info, const char *name):
	Common<T>(info, name) {
	};
	
	~CommonListener() { _destroy(); };
	
	void _destroy();
	
	ListenerPtr getListener() const;
	
	void reset(Napi::Object context, ListenerPtr ctx);
	
	ListenerPtr _impl;
	
};

#endif // _COMMON_HPP_
