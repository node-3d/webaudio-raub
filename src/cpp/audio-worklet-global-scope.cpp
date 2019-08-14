
#include "audio-worklet-global-scope.hpp"

#include "common.hpp"


// ------ Aux macros

	Nan::ObjectWrap::Unwrap<AudioWorkletGlobalScope>(info.This());


// ------ Constructor and Destructor

AudioWorkletGlobalScope::AudioWorkletGlobalScope() {
	
	_isDestroyed = false;
	
}


AudioWorkletGlobalScope::~AudioWorkletGlobalScope() {
	
	_destroy();
	
}


void AudioWorkletGlobalScope::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
}


// ------ Methods and props


JS_METHOD(AudioWorkletGlobalScope::registerProcessor) {
	
	THIS_AUDIO_WORKLET_GLOBAL_SCOPE; THIS_CHECK;
	
	REQ_UTF8_ARG(0, name);
	REQ_FUN_ARG(1, processorConstructor);
	
	// TODO: do something?
	
}


JS_GETTER(AudioWorkletGlobalScope::currentFrameGetter) {
	
	THIS_AUDIO_WORKLET_GLOBAL_SCOPE; THIS_CHECK;
	
	RET_VALUE(JS_OFFS(_currentFrame));
	
}


JS_GETTER(AudioWorkletGlobalScope::currentTimeGetter) {
	
	THIS_AUDIO_WORKLET_GLOBAL_SCOPE; THIS_CHECK;
	
	RET_NUM(_currentTime);
	
}


JS_GETTER(AudioWorkletGlobalScope::sampleRateGetter) {
	
	THIS_AUDIO_WORKLET_GLOBAL_SCOPE; THIS_CHECK;
	
	RET_NUM(_sampleRate);
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference AudioWorkletGlobalScope::_ctorAudioWorkletGlobalScope;


void AudioWorkletGlobalScope::init(Napi::Env env, Napi::Object exports) {
	
	
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, currentFrame);
	ACCESSOR_R(obj, currentTime);
	ACCESSOR_R(obj, sampleRate);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	Nan::SetPrototypeMethod(proto, "registerProcessor", registerProcessor);
	
	// -------- static
	
	Napi::Function ctor = DefineClass(env, "AudioWorkletGlobalScope", {
	
	});
	
	_ctorAudioWorkletGlobalScope = Napi::Persistent(ctor);
	_ctorAudioWorkletGlobalScope.SuppressDestruct();
	
	exports.Set("AudioWorkletGlobalScope", ctor);
	
}


bool AudioWorkletGlobalScope::isAudioWorkletGlobalScope(Napi::Object obj) {
	return obj.InstanceOf(_ctorAudioWorkletGlobalScope.Value());
}


Napi::Object AudioWorkletGlobalScope::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorAudioWorkletGlobalScope);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


JS_METHOD(AudioWorkletGlobalScope::newCtor) {
	
	CTOR_CHECK("AudioWorkletGlobalScope");
	
	AudioWorkletGlobalScope *audioWorkletGlobalScope = new AudioWorkletGlobalScope();
	audioWorkletGlobalScope->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


JS_METHOD(AudioWorkletGlobalScope::destroy) {
	
	THIS_AUDIO_WORKLET_GLOBAL_SCOPE; THIS_CHECK;
	
	_destroy();
	
}


JS_GETTER(AudioWorkletGlobalScope::isDestroyedGetter) {
	
	THIS_AUDIO_WORKLET_GLOBAL_SCOPE;
	
	RET_BOOL(_isDestroyed);
	
}
