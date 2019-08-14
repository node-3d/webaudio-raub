
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



JS_GETTER(OfflineAudioCompletionEvent::renderedBufferGetter) { THIS_OFFLINE_AUDIO_COMPLETION_EVENT; THIS_CHECK;
	
	RET_VALUE(__renderedBuffer.Value());
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference OfflineAudioCompletionEvent::_ctorOfflineAudioCompletionEvent;


void OfflineAudioCompletionEvent::init(Napi::Env env, Napi::Object exports) {
	
	
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, renderedBuffer);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Napi::Function ctor = DefineClass(env, "OfflineAudioCompletionEvent", {
	
	});
	
	_ctorOfflineAudioCompletionEvent = Napi::Persistent(ctor);
	_ctorOfflineAudioCompletionEvent.SuppressDestruct();
	
	exports.Set("OfflineAudioCompletionEvent", ctor);
	
}


bool OfflineAudioCompletionEvent::isOfflineAudioCompletionEvent(Napi::Object obj) {
	return obj.InstanceOf(_ctorOfflineAudioCompletionEvent.Value());
}


Napi::Object OfflineAudioCompletionEvent::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorOfflineAudioCompletionEvent);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


JS_METHOD(OfflineAudioCompletionEvent::newCtor) {
	
	CTOR_CHECK("OfflineAudioCompletionEvent");
	
	OfflineAudioCompletionEvent *offlineAudioCompletionEvent = new OfflineAudioCompletionEvent();
	offlineAudioCompletionEvent->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


JS_METHOD(OfflineAudioCompletionEvent::destroy) { THIS_OFFLINE_AUDIO_COMPLETION_EVENT; THIS_CHECK;
	
	_destroy();
	
}


JS_GETTER(OfflineAudioCompletionEvent::isDestroyedGetter) { THIS_OFFLINE_AUDIO_COMPLETION_EVENT;
	
	RET_BOOL(_isDestroyed);
	
}
