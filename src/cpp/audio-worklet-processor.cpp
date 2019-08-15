
#include "audio-worklet-processor.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

AudioWorkletProcessor::AudioWorkletProcessor() {
	
	_isDestroyed = false;
	
}


AudioWorkletProcessor::~AudioWorkletProcessor() {
	
	_destroy();
	
}


void AudioWorkletProcessor::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
}


// ------ Methods and props



JS_GETTER(AudioWorkletProcessor::portGetter) { THIS_CHECK;
	
	RET_VALUE(_port.Value());
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference AudioWorkletProcessor::_ctorAudioWorkletProcessor;


void AudioWorkletProcessor::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "AudioWorkletProcessor", {
		ACCESSOR_M(AudioWorkletProcessor, destroy),
		ACCESSOR_R(AudioWorkletProcessor, port),
		ACCESSOR_R(AudioWorkletProcessor, isDestroyed),
	
	});
	
	_ctorAudioWorkletProcessor = Napi::Persistent(ctor);
	_ctorAudioWorkletProcessor.SuppressDestruct();
	
	exports.Set("AudioWorkletProcessor", ctor);
	
}


bool AudioWorkletProcessor::isAudioWorkletProcessor(Napi::Object obj) {
	return obj.InstanceOf(_ctorAudioWorkletProcessor.Value());
}


Napi::Object AudioWorkletProcessor::getNew() {
	
	Napi::Function ctor = Nan::New(_ctorAudioWorkletProcessor);
	// Napi::Value argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


AudioWorkletProcessor::AudioWorkletProcessor(const Napi::CallbackInfo &info): Napi::ObjectWrap<AudioWorkletProcessor>(info) {
	
	CTOR_CHECK("AudioWorkletProcessor");
	
	AudioWorkletProcessor *audioWorkletProcessor = new AudioWorkletProcessor();
	
}


JS_METHOD(AudioWorkletProcessor::destroy) { THIS_CHECK;
	
	_destroy();
	
}


JS_GETTER(AudioWorkletProcessor::isDestroyedGetter) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
