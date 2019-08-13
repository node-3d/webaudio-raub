#include <cstdlib>


#include "offline-audio-completion-event.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_OFFLINE_AUDIO_COMPLETION_EVENT                                                    \
	OfflineAudioCompletionEvent *offlineAudioCompletionEvent = Nan::ObjectWrap::Unwrap<OfflineAudioCompletionEvent>(info.This());

#define THIS_CHECK                                                            \
	if (offlineAudioCompletionEvent->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (offlineAudioCompletionEvent->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	offlineAudioCompletionEvent->CACHE = V;


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



NAN_GETTER(OfflineAudioCompletionEvent::renderedBufferGetter) { THIS_OFFLINE_AUDIO_COMPLETION_EVENT; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(offlineAudioCompletionEvent->_renderedBuffer));
	
}


// ------ System methods and props for ObjectWrap

V8_STORE_FT OfflineAudioCompletionEvent::_protoOfflineAudioCompletionEvent;
V8_STORE_FUNC OfflineAudioCompletionEvent::_ctorOfflineAudioCompletionEvent;


void OfflineAudioCompletionEvent::init(Napi::Object target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);

	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("OfflineAudioCompletionEvent"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, renderedBuffer);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoOfflineAudioCompletionEvent.Reset(proto);
	_ctorOfflineAudioCompletionEvent.Reset(ctor);
	
	Nan::Set(target, JS_STR("OfflineAudioCompletionEvent"), ctor);
	
	
}


bool OfflineAudioCompletionEvent::isOfflineAudioCompletionEvent(Napi::Object obj) {
	return Nan::New(_protoOfflineAudioCompletionEvent)->HasInstance(obj);
}


Napi::Object OfflineAudioCompletionEvent::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorOfflineAudioCompletionEvent);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


NAN_METHOD(OfflineAudioCompletionEvent::newCtor) {
	
	CTOR_CHECK("OfflineAudioCompletionEvent");
	
	OfflineAudioCompletionEvent *offlineAudioCompletionEvent = new OfflineAudioCompletionEvent();
	offlineAudioCompletionEvent->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(OfflineAudioCompletionEvent::destroy) { THIS_OFFLINE_AUDIO_COMPLETION_EVENT; THIS_CHECK;
	
	offlineAudioCompletionEvent->_destroy();
	
}


NAN_GETTER(OfflineAudioCompletionEvent::isDestroyedGetter) { THIS_OFFLINE_AUDIO_COMPLETION_EVENT;
	
	RET_VALUE(JS_BOOL(offlineAudioCompletionEvent->_isDestroyed));
	
}
