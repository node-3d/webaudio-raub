
#include "audio-worklet.hpp"

#include "common.hpp"


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

Napi::FunctionReference AudioWorklet::_ctorAudioWorklet;


void AudioWorklet::init(Napi::Env env, Napi::Object exports) {
	
	
	ACCESSOR_R(obj, isDestroyed);
	
	
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Napi::Function ctor = DefineClass(env, "AudioWorklet", {
	
	});
	
	_ctorAudioWorklet = Napi::Persistent(ctor);
	_ctorAudioWorklet.SuppressDestruct();
	
	exports.Set("AudioWorklet", ctor);
	
}


bool AudioWorklet::isAudioWorklet(Napi::Object obj) {
	return obj.InstanceOf(_ctorAudioWorklet.Value());
}


Napi::Object AudioWorklet::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorAudioWorklet);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


JS_METHOD(AudioWorklet::newCtor) {
	
	CTOR_CHECK("AudioWorklet");
	
	AudioWorklet *audioWorklet = new AudioWorklet();
	audioWorklet->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


JS_METHOD(AudioWorklet::destroy) { THIS_AUDIO_WORKLET; THIS_CHECK;
	
	_destroy();
	
}


JS_GETTER(AudioWorklet::isDestroyedGetter) { THIS_AUDIO_WORKLET;
	
	RET_BOOL(_isDestroyed);
	
}
