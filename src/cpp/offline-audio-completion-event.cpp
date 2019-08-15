
#include "offline-audio-completion-event.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

OfflineAudioCompletionEvent::OfflineAudioCompletionEvent() {
	
	_isDestroyed = false;
	
}


OfflineAudioCompletionEvent::~OfflineAudioCompletionEvent() {
	
	_destroy();
	
}


void OfflineAudioCompletionEvent::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
}


// ------ Methods and props



JS_GETTER(OfflineAudioCompletionEvent::renderedBufferGetter) { THIS_CHECK;
	
	RET_VALUE(_renderedBuffer.Value());
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference OfflineAudioCompletionEvent::_ctorOfflineAudioCompletionEvent;


void OfflineAudioCompletionEvent::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "OfflineAudioCompletionEvent", {
		ACCESSOR_M(OfflineAudioCompletionEvent, destroy),
		ACCESSOR_R(OfflineAudioCompletionEvent, renderedBuffer),
		ACCESSOR_R(OfflineAudioCompletionEvent, isDestroyed),
	
	});
	
	_ctorOfflineAudioCompletionEvent = Napi::Persistent(ctor);
	_ctorOfflineAudioCompletionEvent.SuppressDestruct();
	
	exports.Set("OfflineAudioCompletionEvent", ctor);
	
}


bool OfflineAudioCompletionEvent::isOfflineAudioCompletionEvent(Napi::Object obj) {
	return obj.InstanceOf(_ctorOfflineAudioCompletionEvent.Value());
}


Napi::Object OfflineAudioCompletionEvent::getNew() {
	
	Napi::Function ctor = Nan::New(_ctorOfflineAudioCompletionEvent);
	// Napi::Value argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


OfflineAudioCompletionEvent::OfflineAudioCompletionEvent(const Napi::CallbackInfo &info): Napi::ObjectWrap<OfflineAudioCompletionEvent>(info) {
	
	CTOR_CHECK("OfflineAudioCompletionEvent");
	
	OfflineAudioCompletionEvent *offlineAudioCompletionEvent = new OfflineAudioCompletionEvent();
	
}


JS_METHOD(OfflineAudioCompletionEvent::destroy) { THIS_CHECK;
	
	_destroy();
	
}


JS_GETTER(OfflineAudioCompletionEvent::isDestroyedGetter) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
