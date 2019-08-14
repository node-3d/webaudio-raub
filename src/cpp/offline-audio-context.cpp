
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


JS_METHOD(OfflineAudioContext::startRendering) { THIS_OFFLINE_AUDIO_CONTEXT; THIS_CHECK;
	
	// TODO: do something?
	
}


JS_METHOD(OfflineAudioContext::suspend) { THIS_OFFLINE_AUDIO_CONTEXT; THIS_CHECK;
	
	REQ_DOUBLE_ARG(0, suspendTime);
	
	// TODO: do something?
	
}


JS_GETTER(OfflineAudioContext::oncompleteGetter) { THIS_OFFLINE_AUDIO_CONTEXT; THIS_CHECK;
	
	RET_VALUE(JS_FUN(_oncomplete));
	
}

JS_SETTER(OfflineAudioContext::oncompleteSetter) { THIS_OFFLINE_AUDIO_CONTEXT; THIS_CHECK; SETTER_FUN_ARG;
	
	if (Nan::New(_oncomplete) == v) {
		return;
	}
	_oncomplete.Reset(v);
	
	// TODO: may be additional actions on change?
	
	offlineAudioContext->emit("oncomplete", 1, &value);
	
}


JS_GETTER(OfflineAudioContext::lengthGetter) { THIS_OFFLINE_AUDIO_CONTEXT; THIS_CHECK;
	
	RET_NUM(_length);
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference OfflineAudioContext::_ctorOfflineAudioContext;


void OfflineAudioContext::init(Napi::Env env, Napi::Object exports) {
	
	
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_RW(obj, oncomplete);
	ACCESSOR_R(obj, length);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	Nan::SetPrototypeMethod(proto, "startRendering", startRendering);
	Nan::SetPrototypeMethod(proto, "suspend", suspend);
	
	// -------- static
	
	Napi::Function ctor = DefineClass(env, "OfflineAudioContext", {
	
	});
	
	_ctorOfflineAudioContext = Napi::Persistent(ctor);
	_ctorOfflineAudioContext.SuppressDestruct();
	
	exports.Set("OfflineAudioContext", ctor);
	
}


bool OfflineAudioContext::isOfflineAudioContext(Napi::Object obj) {
	return obj.InstanceOf(_ctorOfflineAudioContext.Value());
}


Napi::Object OfflineAudioContext::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorOfflineAudioContext);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


JS_METHOD(OfflineAudioContext::newCtor) {
	
	CTOR_CHECK("OfflineAudioContext");
	
	OfflineAudioContext *offlineAudioContext = new OfflineAudioContext();
	offlineAudioContext->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


JS_METHOD(OfflineAudioContext::destroy) { THIS_OFFLINE_AUDIO_CONTEXT; THIS_CHECK;
	
	offlineAudioContext->emit("destroy");
	
	_destroy();
	
}


JS_GETTER(OfflineAudioContext::isDestroyedGetter) { THIS_OFFLINE_AUDIO_CONTEXT;
	
	RET_BOOL(_isDestroyed);
	
}
