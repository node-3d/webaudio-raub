#ifndef _COMMON_HPP_
#define _COMMON_HPP_

#include <memory>
#include <LabSound/LabSound.h>
#include <addon-tools.hpp>


#define PARAM_GETTER(CLASS, NAME)                                             \
JS_IMPLEMENT_GETTER(CLASS, NAME) { THIS_CHECK;                      \
	RET_VALUE(_ ## NAME.Value());                                             \
}

typedef std::shared_ptr<lab::AudioNode> NodePtr;
typedef std::shared_ptr<lab::AudioParam> ParamPtr;
typedef std::shared_ptr<lab::AudioContext> CtxPtr;
typedef std::shared_ptr<lab::AudioBus> BusPtr;
typedef std::shared_ptr<lab::AudioListener> ListenerPtr;

void _disconnectNode(Napi::Object context, NodePtr node);
void _disconnectParam(Napi::Object context, ParamPtr node);


struct Common {
	
	Common(Napi::Value that, const char *name):
	asyncCtx(that.Env(), name) {
		_that.Reset(that.As<Napi::Object>());
		_isDestroyed = false;
	};
	~Common() { _destroy(); };
	
	void emit(
		const char* name,
		int argc = 0,
		const Napi::Value *argv = nullptr
	) { DES_CHECK;
		eventEmit(_that.Value(), name, argc, argv);
	}
	
	void emitAsync(
		const char* name,
		int argc = 0,
		const Napi::Value *argv = nullptr
	) { DES_CHECK;
		eventEmitAsync(_that.Value(), name, argc, argv, asyncCtx);
	}
	
	void _destroy() { DES_CHECK;
		_isDestroyed = true;
		_context.Reset();
		_that.Reset();
	};
	
	bool _isDestroyed;
	
	Napi::ObjectReference _that;
	Napi::ObjectReference _context;
	Napi::AsyncContext asyncCtx;
	
};


struct CommonNode: public Common {
	
	CommonNode(Napi::Value that, const char *name):
	Common(that, name) {
	};
	
	~CommonNode() { _destroy(); };
	
	void _destroy() { DES_CHECK;
		
		_disconnectNode(_context.Value(), _impl);
		
		_impl.reset();
		
		Common::_destroy();
		
	};
	
	NodePtr getNode() const { return _impl; };
	
	void reset(Napi::Object context, NodePtr node) {
		_context.Reset(context);
		_impl = node;
	};
	
	NodePtr _impl;
	
};


struct CommonParam: public Common {
	
	CommonParam(Napi::Value that, const char *name):
	Common(that, name) {
	};
	
	~CommonParam() { _destroy(); };
		
	void _destroy() { DES_CHECK;
		
		_disconnectParam(_context.Value(), _impl);
		
		_impl.reset();
		
		Common::_destroy();
		
	};
	
	ParamPtr getParam() const { return _impl; };
	
	void reset(Napi::Object context, ParamPtr param) {
		_context.Reset(context);
		_impl = param;
	};
	
	ParamPtr _impl;
	
};


struct CommonCtx: public Common {
	
	CommonCtx(Napi::Value that, const char *name):
	Common(that, name) {
	};
	
	~CommonCtx() { _destroy(); };
	
	void _destroy() { DES_CHECK;
		
		_impl.reset();
		
		Common::_destroy();
		
	};
	
	CtxPtr getCtx() const { return _impl; };
	
	void reset(CtxPtr ctx) {
		_impl = ctx;
	};
	
	CtxPtr _impl;
	
};


struct CommonBus: public Common {
	
	CommonBus(Napi::Value that, const char *name):
	Common(that, name) {
	};
	
	~CommonBus() { _destroy(); };
		
		void _destroy() { DES_CHECK;
		
		_impl.reset();
		
		Common::_destroy();
		
	};
	
	BusPtr getBus() const { return _impl; };
	
	void reset(Napi::Object context, BusPtr bus) {
		_context.Reset(context);
		_impl = bus;
	};
	
	BusPtr _impl;
	
};


struct CommonListener: public Common {
	
	CommonListener(Napi::Value that, const char *name):
	Common(that, name) {
	};
	
	~CommonListener() { _destroy(); };
		
		void _destroy() { DES_CHECK;
		
		_impl.reset();
		
		Common::_destroy();
		
	};
	
	ListenerPtr getListener() const { return _impl; };
	
	void reset(Napi::Object context, ListenerPtr listener) {
		_context.Reset(context);
		_impl = listener;
	};
	
	ListenerPtr _impl;
	
};

#endif // _COMMON_HPP_
