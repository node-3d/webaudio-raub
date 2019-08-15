
#include "offline-audio-context.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

OfflineAudioContext::OfflineAudioContext() :
BaseAudioContext() {
	
	_isDestroyed = false;
	
}


OfflineAudioContext::~OfflineAudioContext() {
	
	_destroy();
	
}


void OfflineAudioContext::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	BaseAudioContext::_destroy();
	
}


// ------ Methods and props


JS_METHOD(OfflineAudioContext::startRendering) { THIS_CHECK;
	
	// TODO: do something?
	
}


JS_METHOD(OfflineAudioContext::suspend) { THIS_CHECK;
	
	REQ_DOUBLE_ARG(0, suspendTime);
	
	// TODO: do something?
	
}


JS_GETTER(OfflineAudioContext::oncompleteGetter) { THIS_CHECK;
	
	RET_VALUE(JS_FUN(_oncomplete));
	
}

JS_SETTER(OfflineAudioContext::oncompleteSetter) { THIS_CHECK; SETTER_FUN_ARG;
	
	if (Nan::New(_oncomplete) == v) {
		return;
	}
	_oncomplete.Reset(v);
	
	// TODO: may be additional actions on change?
	
	emit("oncomplete", 1, &value);
	
}


JS_GETTER(OfflineAudioContext::lengthGetter) { THIS_CHECK;
	
	RET_NUM(_length);
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference OfflineAudioContext::_ctorOfflineAudioContext;


void OfflineAudioContext::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "OfflineAudioContext", {
		ACCESSOR_RW(OfflineAudioContext, oncomplete),
		ACCESSOR_M(OfflineAudioContext, suspend),
		ACCESSOR_M(OfflineAudioContext, startRendering),
		ACCESSOR_M(OfflineAudioContext, destroy),
		ACCESSOR_R(OfflineAudioContext, length),
		ACCESSOR_R(OfflineAudioContext, isDestroyed),
	
	});
	
	_ctorOfflineAudioContext = Napi::Persistent(ctor);
	_ctorOfflineAudioContext.SuppressDestruct();
	
	exports.Set("OfflineAudioContext", ctor);
	
}


bool OfflineAudioContext::isOfflineAudioContext(Napi::Object obj) {
	return obj.InstanceOf(_ctorOfflineAudioContext.Value());
}


Napi::Object OfflineAudioContext::getNew() {
	
	Napi::Function ctor = Nan::New(_ctorOfflineAudioContext);
	// Napi::Value argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


OfflineAudioContext::OfflineAudioContext(const Napi::CallbackInfo &info): Napi::ObjectWrap<OfflineAudioContext>(info) {
	
	CTOR_CHECK("OfflineAudioContext");
	
	OfflineAudioContext *offlineAudioContext = new OfflineAudioContext();
	
}


JS_METHOD(OfflineAudioContext::destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	
}


JS_GETTER(OfflineAudioContext::isDestroyedGetter) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
