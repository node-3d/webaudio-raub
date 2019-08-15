
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
	
	Napi::Function ctor = DefineClass(env, "AudioWorklet", {
		ACCESSOR_M(AudioWorklet, destroy),
		ACCESSOR_R(AudioWorklet, isDestroyed),
	
	});
	
	_ctorAudioWorklet = Napi::Persistent(ctor);
	_ctorAudioWorklet.SuppressDestruct();
	
	exports.Set("AudioWorklet", ctor);
	
}


bool AudioWorklet::isAudioWorklet(Napi::Object obj) {
	return obj.InstanceOf(_ctorAudioWorklet.Value());
}


Napi::Object AudioWorklet::getNew() {
	
	Napi::Function ctor = Nan::New(_ctorAudioWorklet);
	// Napi::Value argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


AudioWorklet::AudioWorklet(const Napi::CallbackInfo &info): Napi::ObjectWrap<AudioWorklet>(info) {
	
	CTOR_CHECK("AudioWorklet");
	
	AudioWorklet *audioWorklet = new AudioWorklet();
	
}


JS_METHOD(AudioWorklet::destroy) { THIS_CHECK;
	
	_destroy();
	
}


JS_GETTER(AudioWorklet::isDestroyedGetter) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
