
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



JS_GETTER(AudioTimestamp::contextTimeGetter) { THIS_AUDIO_TIMESTAMP; THIS_CHECK;
	
	RET_NUM(_contextTime);
	
}

JS_SETTER(AudioTimestamp::contextTimeSetter) { THIS_AUDIO_TIMESTAMP; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	CACHE_CAS(_contextTime, v);
	
	// TODO: may be additional actions on change?
	
}


JS_GETTER(AudioTimestamp::performanceTimeGetter) { THIS_AUDIO_TIMESTAMP; THIS_CHECK;
	
	RET_NUM(_performanceTime);
	
}

JS_SETTER(AudioTimestamp::performanceTimeSetter) { THIS_AUDIO_TIMESTAMP; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	CACHE_CAS(_performanceTime, v);
	
	// TODO: may be additional actions on change?
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference AudioTimestamp::_ctorAudioTimestamp;


void AudioTimestamp::init(Napi::Env env, Napi::Object exports) {
	
	
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_RW(obj, contextTime);
	ACCESSOR_RW(obj, performanceTime);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Napi::Function ctor = DefineClass(env, "AudioTimestamp", {
	
	});
	
	_ctorAudioTimestamp = Napi::Persistent(ctor);
	_ctorAudioTimestamp.SuppressDestruct();
	
	exports.Set("AudioTimestamp", ctor);
	
}


bool AudioTimestamp::isAudioTimestamp(Napi::Object obj) {
	return obj.InstanceOf(_ctorAudioTimestamp.Value());
}


Napi::Object AudioTimestamp::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorAudioTimestamp);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


JS_METHOD(AudioTimestamp::newCtor) {
	
	CTOR_CHECK("AudioTimestamp");
	
	AudioTimestamp *audioTimestamp = new AudioTimestamp();
	audioTimestamp->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


JS_METHOD(AudioTimestamp::destroy) { THIS_AUDIO_TIMESTAMP; THIS_CHECK;
	
	_destroy();
	
}


JS_GETTER(AudioTimestamp::isDestroyedGetter) { THIS_AUDIO_TIMESTAMP;
	
	RET_BOOL(_isDestroyed);
	
}
