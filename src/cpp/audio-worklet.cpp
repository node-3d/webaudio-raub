#include <cstdlib>


#include "audio-worklet.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_AUDIO_WORKLET                                                    \
	AudioWorklet *audioWorklet = Nan::ObjectWrap::Unwrap<AudioWorklet>(info.This());

#define CACHE_CAS(CACHE, V)                                                   \
	if (this.CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	this.CACHE = V;


// ------ Constructor and Destructor

AudioWorklet::AudioWorklet() {
	
	_isDestroyed = false;
	
}


AudioWorklet::~AudioWorklet() {
	
	_destroy();
	
}


void AudioWorklet::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
}


// ------ Methods and props




// ------ System methods and props for ObjectWrap

V8_STORE_FT AudioWorklet::_protoAudioWorklet;
V8_STORE_FUNC AudioWorklet::_ctorAudioWorklet;


void AudioWorklet::init(Napi::Object target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);

	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AudioWorklet"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoAudioWorklet.Reset(proto);
	_ctorAudioWorklet.Reset(ctor);
	
	Nan::Set(target, JS_STR("AudioWorklet"), ctor);
	
	
}


bool AudioWorklet::isAudioWorklet(Napi::Object obj) {
	return Nan::New(_protoAudioWorklet)->HasInstance(obj);
}


Napi::Object AudioWorklet::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorAudioWorklet);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


NAN_METHOD(AudioWorklet::newCtor) {
	
	CTOR_CHECK("AudioWorklet");
	
	AudioWorklet *audioWorklet = new AudioWorklet();
	audioWorklet->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(AudioWorklet::destroy) { THIS_AUDIO_WORKLET; THIS_CHECK;
	
	audioWorklet->_destroy();
	
}


NAN_GETTER(AudioWorklet::isDestroyedGetter) { THIS_AUDIO_WORKLET;
	
	RET_BOOL(audioWorklet->_isDestroyed);
	
}
