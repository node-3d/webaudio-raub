#include <cstdlib>
#include <iostream>

#include "audio-worklet-processor.hpp"

using namespace v8;
using namespace node;
using namespace std;


#define THIS_AUDIO_WORKLET_PROCESSOR                                                    \
	AudioWorkletProcessor *audioWorkletProcessor = ObjectWrap::Unwrap<AudioWorkletProcessor>(info.This());

#define THIS_CHECK                                                            \
	if (audioWorkletProcessor->_isDestroyed) return;

#define DES_CHECK                                                             \
	if (_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (audioWorkletProcessor->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	audioWorkletProcessor->CACHE = V;


Nan::Persistent<v8::Function> AudioWorkletProcessor::_constructor;


void AudioWorkletProcessor::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AudioWorkletProcessor"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, port);
	
	// -------- dynamic
	
	
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	
	
	
	_constructor.Reset(ctor);
	Nan::Set(target, JS_STR("AudioWorkletProcessor"), ctor);
	
	
}


NAN_METHOD(AudioWorkletProcessor::newCtor) {
	
	CTOR_CHECK("AudioWorkletProcessor");
	
	AudioWorkletProcessor *audioWorkletProcessor = new AudioWorkletProcessor();
	audioWorkletProcessor->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


AudioWorkletProcessor::AudioWorkletProcessor() {
	
	_isDestroyed = false;
	
}


AudioWorkletProcessor::~AudioWorkletProcessor() {
	
	_destroy();
	
}


void AudioWorkletProcessor::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	
	
}



NAN_METHOD(AudioWorkletProcessor::destroy) { THIS_AUDIO_WORKLET_PROCESSOR; THIS_CHECK;
	
	audioWorkletProcessor->_destroy();
	
}




NAN_GETTER(AudioWorkletProcessor::isDestroyedGetter) { THIS_AUDIO_WORKLET_PROCESSOR;
	
	RET_VALUE(JS_BOOL(audioWorkletProcessor->_isDestroyed));
	
}


NAN_GETTER(AudioWorkletProcessor::portGetter) { THIS_AUDIO_WORKLET_PROCESSOR; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(audioWorkletProcessor->_port));
	
}


