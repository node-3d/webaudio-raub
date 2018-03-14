#include <cstdlib>
#include <iostream>

#include "offline-audio-context.hpp"

using namespace v8;
using namespace node;
using namespace std;


#define THIS_OFFLINE_AUDIO_CONTEXT                                                    \
	OfflineAudioContext *offlineAudioContext = ObjectWrap::Unwrap<OfflineAudioContext>(info.This());

#define THIS_CHECK                                                            \
	if (offlineAudioContext->_isDestroyed) return;

#define DES_CHECK                                                             \
	if (_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (offlineAudioContext->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	offlineAudioContext->CACHE = V;


Nan::Persistent<v8::Function> OfflineAudioContext::_constructor;


void OfflineAudioContext::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("OfflineAudioContext"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_RW(obj, oncomplete);
	ACCESSOR_R(obj, length);
	
	// -------- dynamic
	
	
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	Nan::SetPrototypeMethod(proto, "startRendering", startRendering);
	Nan::SetPrototypeMethod(proto, "suspend", suspend);
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	
	
	
	_constructor.Reset(ctor);
	Nan::Set(target, JS_STR("OfflineAudioContext"), ctor);
	
	
}


NAN_METHOD(OfflineAudioContext::newCtor) {
	
	CTOR_CHECK("OfflineAudioContext");
	
	OfflineAudioContext *offlineAudioContext = new OfflineAudioContext();
	offlineAudioContext->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


OfflineAudioContext::OfflineAudioContext() {
	
	_isDestroyed = false;
	
}


OfflineAudioContext::~OfflineAudioContext() {
	
	_destroy();
	
}


void OfflineAudioContext::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	
	
}



NAN_METHOD(OfflineAudioContext::destroy) { THIS_OFFLINE_AUDIO_CONTEXT; THIS_CHECK;
	
	offlineAudioContext->_destroy();
	
}


NAN_METHOD(OfflineAudioContext::startRendering) { THIS_OFFLINE_AUDIO_CONTEXT; THIS_CHECK;
	
	
	
	// TODO: do something?
	
}


NAN_METHOD(OfflineAudioContext::suspend) { THIS_OFFLINE_AUDIO_CONTEXT; THIS_CHECK;
	
	REQ_DOUBLE_ARG(0, suspendTime);
	
	// TODO: do something?
	
}



NAN_GETTER(OfflineAudioContext::isDestroyedGetter) { THIS_OFFLINE_AUDIO_CONTEXT;
	
	RET_VALUE(JS_BOOL(offlineAudioContext->_isDestroyed));
	
}


NAN_GETTER(OfflineAudioContext::oncompleteGetter) { THIS_OFFLINE_AUDIO_CONTEXT; THIS_CHECK;
	
	RET_VALUE(JS_FUN(offlineAudioContext->_oncomplete));
	
}

NAN_SETTER(OfflineAudioContext::oncompleteSetter) { THIS_OFFLINE_AUDIO_CONTEXT; THIS_CHECK; SETTER_FUN_ARG;
	
	if (Nan::New(offlineAudioContext->_oncomplete) == v) {
		return;
	}
	offlineAudioContext->_oncomplete.Reset(v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(OfflineAudioContext::lengthGetter) { THIS_OFFLINE_AUDIO_CONTEXT; THIS_CHECK;
	
	RET_VALUE(JS_UINT32(offlineAudioContext->_length));
	
}

