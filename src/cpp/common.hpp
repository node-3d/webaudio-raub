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
typedef lab::AudioListener* ListenerPtr;

void _disconnectNode(Napi::Object context, NodePtr node);
void _disconnectParam(Napi::Object context, ParamPtr node);


struct Common {
	
	Common(Napi::Value that, const char *name):
	_asyncCtx(that.Env(), name) {
		_that.Reset(that.As<Napi::Object>());
		_isDestroyed = false;
		std::cout << "xw 111 " << that.Env().IsExceptionPending() << std::endl;
		// Create a ThreadSafeFunction
		Napi::Object emitter = that.As<Napi::Object>();
		Napi::Function emit = emitter.Get("emit").As<Napi::Function>();
		
		std::cout << "xw 222 " << that.Env().IsExceptionPending() << std::endl;
		_tsEmit = Napi::ThreadSafeFunction::New(that.Env(), emit, name, 0, 1);
		std::cout << "xw 333 " << that.Env().IsExceptionPending() << std::endl;
	};
	~Common() { std::cout << "DES " << std::endl; _destroy(); };
	
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
	) {
		std::thread::id this_id = std::this_thread::get_id();
		
		std::cout << "ololo1 " << this_id << std::endl;
		_tsEmit.Acquire();
		
		std::cout << "ololo2 " << this_id << std::endl;
		
		Common *that = this;
		napi_status status = _tsEmit.NonBlockingCall(
			[that, name, argc, argv](
				Napi::Env env,
				Napi::Function emit
			) {
				std::cout << "ccc0 " << std::endl;
				std::vector<napi_value> args;
				args.push_back(JS_STR(name));
				for (int i = 0; i < argc; i++) {
					args.push_back(argv[i]);
				}
				
				
				std::cout << "ccc1 " << std::endl;
				emit.Call(that->_that.Value(), args);
				
				std::cout << "ccc2 " << std::endl;
				
			}
		);
		
		std::cout << "ololo3 " << this_id << std::endl;
		
		if ( status != napi_ok ) {
			std::cout << "call fail " << this_id << std::endl;
		}
		
		_tsEmit.Release();
		std::cout << "ololo4" << std::endl;
	}
	
	void _destroy() { DES_CHECK;
		_isDestroyed = true;
		_context.Reset();
		_that.Reset();
	};
	
	bool _isDestroyed;
	
	Napi::ObjectReference _that;
	Napi::ObjectReference _context;
	Napi::AsyncContext _asyncCtx;
	Napi::ThreadSafeFunction _tsEmit;
	
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
		
		_impl = nullptr;
		
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
