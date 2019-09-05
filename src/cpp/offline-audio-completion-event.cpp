
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



JS_IMPLEMENT_GETTER(OfflineAudioCompletionEvent, renderedBuffer) { THIS_CHECK;
	
	RET_VALUE(_renderedBuffer.Value());
	
}


// ------ System methods and props for Napi::ObjectWrap

IMPLEMENT_ES5_CLASS(OfflineAudioCompletionEvent);


void OfflineAudioCompletionEvent::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_METHOD(destroy);
	JS_ASSIGN_GETTER(renderedBuffer);
	JS_ASSIGN_GETTER(isDestroyed);
	
	exports.Set("OfflineAudioCompletionEvent", ctor);
	
}


bool OfflineAudioCompletionEvent::isOfflineAudioCompletionEvent(Napi::Object obj) {
	return obj.InstanceOf(_ctorEs5.Value());
}


Napi::Object OfflineAudioCompletionEvent::getNew() {
	
	Napi::Function ctor = Nan::New(_constructor);
	// Napi::Value argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


OfflineAudioCompletionEvent::OfflineAudioCompletionEvent(const Napi::CallbackInfo &info): Napi::ObjectWrap<OfflineAudioCompletionEvent>(info) {
	
	OfflineAudioCompletionEvent *offlineAudioCompletionEvent = new OfflineAudioCompletionEvent();
	
}


JS_IMPLEMENT_METHOD(OfflineAudioCompletionEvent, destroy) { THIS_CHECK;
	
	_destroy();
	
}


JS_IMPLEMENT_GETTER(OfflineAudioCompletionEvent, isDestroyed) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
