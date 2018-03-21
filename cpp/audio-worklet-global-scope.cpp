#include <cstdlib>
//#include <iostream> // -> std::cout << "..." << std::endl;


#include "audio-worklet-global-scope.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_AUDIO_WORKLET_GLOBAL_SCOPE                                                    \
	AudioWorkletGlobalScope *audioWorkletGlobalScope = ObjectWrap::Unwrap<AudioWorkletGlobalScope>(info.This());

#define THIS_CHECK                                                            \
	if (audioWorkletGlobalScope->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (audioWorkletGlobalScope->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	audioWorkletGlobalScope->CACHE = V;


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


NAN_METHOD(AudioWorkletGlobalScope::registerProcessor) { THIS_AUDIO_WORKLET_GLOBAL_SCOPE; THIS_CHECK;
	
	REQ_UTF8_ARG(0, name);
	REQ_FUN_ARG(1, processorConstructor);
	
	// TODO: do something?
	
}


NAN_GETTER(AudioWorkletGlobalScope::currentFrameGetter) { THIS_AUDIO_WORKLET_GLOBAL_SCOPE; THIS_CHECK;
	
	RET_VALUE(JS_OFFS(audioWorkletGlobalScope->_currentFrame));
	
}


NAN_GETTER(AudioWorkletGlobalScope::currentTimeGetter) { THIS_AUDIO_WORKLET_GLOBAL_SCOPE; THIS_CHECK;
	
	RET_VALUE(JS_DOUBLE(audioWorkletGlobalScope->_currentTime));
	
}


NAN_GETTER(AudioWorkletGlobalScope::sampleRateGetter) { THIS_AUDIO_WORKLET_GLOBAL_SCOPE; THIS_CHECK;
	
	RET_VALUE(JS_FLOAT(audioWorkletGlobalScope->_sampleRate));
	
}


// ------ System methods and props for ObjectWrap

Nan::Persistent<v8::FunctionTemplate> AudioWorkletGlobalScope::_protoAudioWorkletGlobalScope;
Nan::Persistent<v8::Function> AudioWorkletGlobalScope::_ctorAudioWorkletGlobalScope;


void AudioWorkletGlobalScope::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AudioWorkletGlobalScope"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, currentFrame);
	ACCESSOR_R(obj, currentTime);
	ACCESSOR_R(obj, sampleRate);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	Nan::SetPrototypeMethod(proto, "registerProcessor", registerProcessor);
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoAudioWorkletGlobalScope.Reset(proto);
	_ctorAudioWorkletGlobalScope.Reset(ctor);
	
	Nan::Set(target, JS_STR("AudioWorkletGlobalScope"), ctor);
	
	
}


NAN_METHOD(AudioWorkletGlobalScope::newCtor) {
	
	CTOR_CHECK("AudioWorkletGlobalScope");
	
	AudioWorkletGlobalScope *audioWorkletGlobalScope = new AudioWorkletGlobalScope();
	audioWorkletGlobalScope->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(AudioWorkletGlobalScope::destroy) { THIS_AUDIO_WORKLET_GLOBAL_SCOPE; THIS_CHECK;
	
	audioWorkletGlobalScope->_destroy();
	
}


NAN_GETTER(AudioWorkletGlobalScope::isDestroyedGetter) { THIS_AUDIO_WORKLET_GLOBAL_SCOPE;
	
	RET_VALUE(JS_BOOL(audioWorkletGlobalScope->_isDestroyed));
	
}
