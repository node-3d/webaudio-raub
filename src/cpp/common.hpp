#ifndef _COMMON_HPP_
#define _COMMON_HPP_

#include <memory>
#include <LabSound/LabSound.h>
#include <addon-tools.hpp>


#define PARAM_GETTER(CLASS, NAME)                                             \
JS_GETTER(CLASS::NAME ## Getter) { THIS_CHECK;                                \
	RET_VALUE(_ ## NAME.Value());                                             \
}

typedef std::shared_ptr<lab::AudioNode> NodePtr;
typedef std::shared_ptr<lab::AudioParam> ParamPtr;
typedef std::shared_ptr<lab::AudioContext> CtxPtr;
typedef std::shared_ptr<lab::AudioBus> BusPtr;
typedef std::shared_ptr<lab::AudioListener> ListenerPtr;

void _disconnectNode(Napi::Object context, NodePtr node);
void _disconnectParam(Napi::Object context, ParamPtr node);


template <typename T>
struct Common : public Napi::ObjectWrap<T> {
	
	Common(const Napi::CallbackInfo &info, const char *name):
	Napi::ObjectWrap<T>(info),
	asyncCtx(info.Env(), name) {
		_isDestroyed = false;
	};
	~Common() { _destroy(); };
	
	void emit(
		const char* name,
		int argc = 0,
		const Napi::Value *argv = nullptr
	) { DES_CHECK;
		Napi::Object that = Value().As<Napi::Object>();
		eventEmit(that, name, argc, argv);
	}
	
	void emitAsync(
		const char* name,
		int argc = 0,
		const Napi::Value *argv = nullptr
	) { DES_CHECK;
		Napi::Object that = Value().As<Napi::Object>();
		eventEmitAsync(that, name, argc, argv, asyncCtx);
	}
	
	void _destroy() { DES_CHECK;
		_isDestroyed = true;
	};
	
	bool _isDestroyed;
	
	Napi::ObjectReference _context;
	Napi::AsyncContext asyncCtx;
	
};


template <typename T>
struct CommonNode: public Common<T> {
	
	CommonNode(const Napi::CallbackInfo &info, const char *name):
	Common<T>(info, name) {
	};
	
	~CommonNode() { _destroy(); };
	
	void _destroy() { DES_CHECK;
		
		_disconnectNode(_context.Value(), _impl);
		
		_impl.reset();
		_context.Reset();
		
		Common<T>::_destroy();
		
	};
	
	NodePtr getNode() const { return _impl; };
	
	void reset(Napi::Object context, NodePtr node) {
		_context.Reset(context);
		_impl = node;
	};
	
	NodePtr _impl;
	
};


template <typename T>
struct CommonParam: public Common<T> {
	
	CommonParam(const Napi::CallbackInfo &info, const char *name):
	Common<T>(info, name) {
	};
	
	~CommonParam() { _destroy(); };
		
	void _destroy() { DES_CHECK;
		
		_disconnectParam(_context.Value(), _impl);
		
		_impl.reset();
		_context.Reset();
		
		Common<T>::_destroy();
		
	};
	
	ParamPtr getParam() const { return _impl; };
	
	void reset(Napi::Object context, ParamPtr param) {
		_context.Reset(context);
		_impl = param;
	};
	
	ParamPtr _impl;
	
};


template <typename T>
struct CommonCtx: public Common<T> {
	
	CommonCtx(const Napi::CallbackInfo &info, const char *name):
	Common<T>(info, name) {
	};
	
	~CommonCtx() { _destroy(); };
	
	void _destroy() { DES_CHECK;
		
		_impl.reset();
		
		Common<T>::_destroy();
		
	};
	
	CtxPtr getCtx() const { return _impl; };
	
	void reset(CtxPtr ctx) {
		_impl = ctx;
	};
	
	CtxPtr _impl;
	
};


template <typename T>
struct CommonBus: public Common<T> {
	
	CommonBus(const Napi::CallbackInfo &info, const char *name):
	Common<T>(info, name) {
	};
	
	~CommonBus() { _destroy(); };
		
		void _destroy() { DES_CHECK;
		
		_impl.reset();
		_context.Reset();
		
		Common<T>::_destroy();
		
	};
	
	BusPtr getBus() const { return _impl; };
	
	void reset(Napi::Object context, BusPtr bus) {
		_context.Reset(context);
		_impl = bus;
	};
	
	BusPtr _impl;
	
};


template <typename T>
struct CommonListener: public Common<T> {
	
	CommonListener(const Napi::CallbackInfo &info, const char *name):
	Common<T>(info, name) {
	};
	
	~CommonListener() { _destroy(); };
		
		void _destroy() { DES_CHECK;
		
		_impl.reset();
		_context.Reset();
		
		Common<T>::_destroy();
		
	};
	
	ListenerPtr getListener() const { return _impl; };
	
	void reset(Napi::Object context, ListenerPtr listener) {
		_context.Reset(context);
		_impl = listener;
	};
	
	ListenerPtr _impl;
	
};

#endif // _COMMON_HPP_
