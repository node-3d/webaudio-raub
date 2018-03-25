#include <cstdlib>
//#include <iostream> // -> cout << "..." << endl;


#include "audio-worklet-processor.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_AUDIO_WORKLET_PROCESSOR                                                    \
	AudioWorkletProcessor *audioWorkletProcessor = Nan::ObjectWrap::Unwrap<AudioWorkletProcessor>(info.This());

#define THIS_CHECK                                                            \
	if (audioWorkletProcessor->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (audioWorkletProcessor->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	audioWorkletProcessor->CACHE = V;


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



NAN_GETTER(AudioWorkletProcessor::portGetter) { THIS_AUDIO_WORKLET_PROCESSOR; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(audioWorkletProcessor->_port));
	
}


// ------ System methods and props for ObjectWrap

Nan::Persistent<FunctionTemplate> AudioWorkletProcessor::_protoAudioWorkletProcessor;
Nan::Persistent<Function> AudioWorkletProcessor::_ctorAudioWorkletProcessor;


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
	
	_protoAudioWorkletProcessor.Reset(proto);
	_ctorAudioWorkletProcessor.Reset(ctor);
	
	Nan::Set(target, JS_STR("AudioWorkletProcessor"), ctor);
	
	
}


Local<Object> AudioWorkletProcessor::getNew() {
	
	Local<Function> ctor = Nan::New(_ctorAudioWorkletProcessor);
	// Local<Value> argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


NAN_METHOD(AudioWorkletProcessor::newCtor) {
	
	CTOR_CHECK("AudioWorkletProcessor");
	
	AudioWorkletProcessor *audioWorkletProcessor = new AudioWorkletProcessor();
	audioWorkletProcessor->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(AudioWorkletProcessor::destroy) { THIS_AUDIO_WORKLET_PROCESSOR; THIS_CHECK;
	
	audioWorkletProcessor->_destroy();
	
}


NAN_GETTER(AudioWorkletProcessor::isDestroyedGetter) { THIS_AUDIO_WORKLET_PROCESSOR;
	
	RET_VALUE(JS_BOOL(audioWorkletProcessor->_isDestroyed));
	
}
