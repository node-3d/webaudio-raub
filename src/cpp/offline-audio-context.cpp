#include <cstdlib>


#include "offline-audio-context.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_OFFLINE_AUDIO_CONTEXT                                                    \
	OfflineAudioContext *offlineAudioContext = Nan::ObjectWrap::Unwrap<OfflineAudioContext>(info.This());

#define CACHE_CAS(CACHE, V)                                                   \
	if (this.CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	this.CACHE = V;


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


NAN_METHOD(OfflineAudioContext::startRendering) { THIS_OFFLINE_AUDIO_CONTEXT; THIS_CHECK;
	
	// TODO: do something?
	
}


NAN_METHOD(OfflineAudioContext::suspend) { THIS_OFFLINE_AUDIO_CONTEXT; THIS_CHECK;
	
	REQ_DOUBLE_ARG(0, suspendTime);
	
	// TODO: do something?
	
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
	
	offlineAudioContext->emit("oncomplete", 1, &value);
	
}


NAN_GETTER(OfflineAudioContext::lengthGetter) { THIS_OFFLINE_AUDIO_CONTEXT; THIS_CHECK;
	
	RET_NUM(offlineAudioContext->_length);
	
}


// ------ System methods and props for ObjectWrap

V8_STORE_FT OfflineAudioContext::_protoOfflineAudioContext;
V8_STORE_FUNC OfflineAudioContext::_ctorOfflineAudioContext;


void OfflineAudioContext::init(Napi::Object target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);

	// class OfflineAudioContext inherits BaseAudioContext
	V8_VAR_FT parent = Nan::New(BaseAudioContext::_protoBaseAudioContext);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("OfflineAudioContext"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_RW(obj, oncomplete);
	ACCESSOR_R(obj, length);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	Nan::SetPrototypeMethod(proto, "startRendering", startRendering);
	Nan::SetPrototypeMethod(proto, "suspend", suspend);
	
	// -------- static
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoOfflineAudioContext.Reset(proto);
	_ctorOfflineAudioContext.Reset(ctor);
	
	Nan::Set(target, JS_STR("OfflineAudioContext"), ctor);
	
	
}


bool OfflineAudioContext::isOfflineAudioContext(Napi::Object obj) {
	return Nan::New(_protoOfflineAudioContext)->HasInstance(obj);
}


Napi::Object OfflineAudioContext::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorOfflineAudioContext);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


NAN_METHOD(OfflineAudioContext::newCtor) {
	
	CTOR_CHECK("OfflineAudioContext");
	
	OfflineAudioContext *offlineAudioContext = new OfflineAudioContext();
	offlineAudioContext->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(OfflineAudioContext::destroy) { THIS_OFFLINE_AUDIO_CONTEXT; THIS_CHECK;
	
	offlineAudioContext->emit("destroy");
	
	offlineAudioContext->_destroy();
	
}


NAN_GETTER(OfflineAudioContext::isDestroyedGetter) { THIS_OFFLINE_AUDIO_CONTEXT;
	
	RET_BOOL(offlineAudioContext->_isDestroyed);
	
}
