#include <cstdlib>
#include <iostream>

#include "offline-audio-completion-event.hpp"

using namespace v8;
using namespace node;
using namespace std;


#define THIS_OFFLINE_AUDIO_COMPLETION_EVENT                                                    \
	OfflineAudioCompletionEvent *offlineAudioCompletionEvent = ObjectWrap::Unwrap<OfflineAudioCompletionEvent>(info.This());

#define THIS_CHECK                                                            \
	if (offlineAudioCompletionEvent->_isDestroyed) return;

#define DES_CHECK                                                             \
	if (_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (offlineAudioCompletionEvent->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	offlineAudioCompletionEvent->CACHE = V;


Nan::Persistent<v8::Function> OfflineAudioCompletionEvent::_constructor;


void OfflineAudioCompletionEvent::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("OfflineAudioCompletionEvent"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, renderedBuffer);
	
	// -------- dynamic
	
	
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	
	
	
	_constructor.Reset(ctor);
	Nan::Set(target, JS_STR("OfflineAudioCompletionEvent"), ctor);
	
	
}


NAN_METHOD(OfflineAudioCompletionEvent::newCtor) {
	
	CTOR_CHECK("OfflineAudioCompletionEvent");
	
	OfflineAudioCompletionEvent *offlineAudioCompletionEvent = new OfflineAudioCompletionEvent();
	offlineAudioCompletionEvent->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


OfflineAudioCompletionEvent::OfflineAudioCompletionEvent() {
	
	_isDestroyed = false;
	
}


OfflineAudioCompletionEvent::~OfflineAudioCompletionEvent() {
	
	_destroy();
	
}


void OfflineAudioCompletionEvent::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	
	
}



NAN_METHOD(OfflineAudioCompletionEvent::destroy) { THIS_OFFLINE_AUDIO_COMPLETION_EVENT; THIS_CHECK;
	
	offlineAudioCompletionEvent->_destroy();
	
}




NAN_GETTER(OfflineAudioCompletionEvent::isDestroyedGetter) { THIS_OFFLINE_AUDIO_COMPLETION_EVENT;
	
	RET_VALUE(JS_BOOL(offlineAudioCompletionEvent->_isDestroyed));
	
}


NAN_GETTER(OfflineAudioCompletionEvent::renderedBufferGetter) { THIS_OFFLINE_AUDIO_COMPLETION_EVENT; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(offlineAudioCompletionEvent->_renderedBuffer));
	
}


