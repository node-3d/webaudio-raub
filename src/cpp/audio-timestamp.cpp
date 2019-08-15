
#include "audio-timestamp.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

AudioTimestamp::AudioTimestamp() {
	
	_isDestroyed = false;
	
}


AudioTimestamp::~AudioTimestamp() {
	
	_destroy();
	
}


void AudioTimestamp::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
}


// ------ Methods and props



JS_GETTER(AudioTimestamp::contextTimeGetter) { THIS_CHECK;
	
	RET_NUM(_contextTime);
	
}

JS_SETTER(AudioTimestamp::contextTimeSetter) { THIS_CHECK; SETTER_DOUBLE_ARG;
	
	CACHE_CAS(_contextTime, v);
	
	// TODO: may be additional actions on change?
	
}


JS_GETTER(AudioTimestamp::performanceTimeGetter) { THIS_CHECK;
	
	RET_NUM(_performanceTime);
	
}

JS_SETTER(AudioTimestamp::performanceTimeSetter) { THIS_CHECK; SETTER_DOUBLE_ARG;
	
	CACHE_CAS(_performanceTime, v);
	
	// TODO: may be additional actions on change?
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference AudioTimestamp::_ctorAudioTimestamp;


void AudioTimestamp::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "AudioTimestamp", {
		ACCESSOR_RW(AudioTimestamp, performanceTime),
		ACCESSOR_RW(AudioTimestamp, contextTime),
		ACCESSOR_M(AudioTimestamp, destroy),
		ACCESSOR_R(AudioTimestamp, isDestroyed)
	});
	
	_ctorAudioTimestamp = Napi::Persistent(ctor);
	_ctorAudioTimestamp.SuppressDestruct();
	
	exports.Set("AudioTimestamp", ctor);
	
}


bool AudioTimestamp::isAudioTimestamp(Napi::Object obj) {
	return obj.InstanceOf(_ctorAudioTimestamp.Value());
}


Napi::Object AudioTimestamp::getNew() {
	
	Napi::Function ctor = Nan::New(_ctorAudioTimestamp);
	// Napi::Value argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


AudioTimestamp::AudioTimestamp(const Napi::CallbackInfo &info): Napi::ObjectWrap<AudioTimestamp>(info) {
	
	CTOR_CHECK("AudioTimestamp");
	
	AudioTimestamp *audioTimestamp = new AudioTimestamp();
	
}


JS_METHOD(AudioTimestamp::destroy) { THIS_CHECK;
	
	_destroy();
	
}


JS_GETTER(AudioTimestamp::isDestroyedGetter) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
