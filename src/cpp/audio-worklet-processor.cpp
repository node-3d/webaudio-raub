
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



JS_GETTER(AudioWorkletProcessor::portGetter) { THIS_AUDIO_WORKLET_PROCESSOR; THIS_CHECK;
	
	RET_VALUE(__port.Value());
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference AudioWorkletProcessor::_ctorAudioWorkletProcessor;


void AudioWorkletProcessor::init(Napi::Env env, Napi::Object exports) {
	
	
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, port);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Napi::Function ctor = DefineClass(env, "AudioWorkletProcessor", {
	
	});
	
	_ctorAudioWorkletProcessor = Napi::Persistent(ctor);
	_ctorAudioWorkletProcessor.SuppressDestruct();
	
	exports.Set("AudioWorkletProcessor", ctor);
	
}


bool AudioWorkletProcessor::isAudioWorkletProcessor(Napi::Object obj) {
	return obj.InstanceOf(_ctorAudioWorkletProcessor.Value());
}


Napi::Object AudioWorkletProcessor::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorAudioWorkletProcessor);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


JS_METHOD(AudioWorkletProcessor::newCtor) {
	
	CTOR_CHECK("AudioWorkletProcessor");
	
	AudioWorkletProcessor *audioWorkletProcessor = new AudioWorkletProcessor();
	audioWorkletProcessor->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


JS_METHOD(AudioWorkletProcessor::destroy) { THIS_AUDIO_WORKLET_PROCESSOR; THIS_CHECK;
	
	_destroy();
	
}


JS_GETTER(AudioWorkletProcessor::isDestroyedGetter) { THIS_AUDIO_WORKLET_PROCESSOR;
	
	RET_BOOL(_isDestroyed);
	
}
