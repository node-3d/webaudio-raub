#include <cstdlib>
//#include <iostream> // -> std::cout << "..." << std::endl;


#include "audio-context.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_AUDIO_CONTEXT                                                    \
	AudioContext *audioContext = Nan::ObjectWrap::Unwrap<AudioContext>(info.This());

#define THIS_CHECK                                                            \
	if (audioContext->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (audioContext->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	audioContext->CACHE = V;


// ------ Constructor and Destructor

AudioContext::AudioContext() : BaseAudioContext() {
	
	_isDestroyed = false;
	
}


AudioContext::AudioContext(float sampleRate) : BaseAudioContext(sampleRate) {
	
	_isDestroyed = false;
	
}


AudioContext::~AudioContext() {
	
	_destroy();
	
}


void AudioContext::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	BaseAudioContext::_destroy();
	
}


// ------ Methods and props


NAN_METHOD(AudioContext::suspend) { THIS_AUDIO_CONTEXT; THIS_CHECK;
	
	// TODO: do something?
	
}


NAN_METHOD(AudioContext::close) { THIS_AUDIO_CONTEXT; THIS_CHECK;
	
	// TODO: do something?
	
}


NAN_METHOD(AudioContext::getOutputTimestamp) { THIS_AUDIO_CONTEXT; THIS_CHECK;
	
	// TODO: do something?
	
}


NAN_METHOD(AudioContext::createMediaElementSource) { THIS_AUDIO_CONTEXT; THIS_CHECK;
	
	REQ_OBJ_ARG(0, mediaElement);
	
	// TODO: do something?
	
}


NAN_METHOD(AudioContext::createMediaStreamSource) { THIS_AUDIO_CONTEXT; THIS_CHECK;
	
	REQ_OBJ_ARG(0, mediaStream);
	
	// TODO: do something?
	
}


NAN_METHOD(AudioContext::createMediaStreamDestination) { THIS_AUDIO_CONTEXT; THIS_CHECK;
	
	// TODO: do something?
	
}


NAN_GETTER(AudioContext::baseLatencyGetter) { THIS_AUDIO_CONTEXT; THIS_CHECK;
	
	RET_VALUE(JS_DOUBLE(audioContext->_baseLatency));
	
}


// ------ System methods and props for ObjectWrap

Nan::Persistent<v8::FunctionTemplate> AudioContext::_protoAudioContext;
Nan::Persistent<v8::Function> AudioContext::_ctorAudioContext;


void AudioContext::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	// class AudioContext inherits BaseAudioContext
	Local<FunctionTemplate> parent = Nan::New(BaseAudioContext::_protoBaseAudioContext);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AudioContext"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, baseLatency);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	Nan::SetPrototypeMethod(proto, "suspend", suspend);
	Nan::SetPrototypeMethod(proto, "close", close);
	Nan::SetPrototypeMethod(proto, "getOutputTimestamp", getOutputTimestamp);
	Nan::SetPrototypeMethod(proto, "createMediaElementSource", createMediaElementSource);
	Nan::SetPrototypeMethod(proto, "createMediaStreamSource", createMediaStreamSource);
	Nan::SetPrototypeMethod(proto, "createMediaStreamDestination", createMediaStreamDestination);
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoAudioContext.Reset(proto);
	_ctorAudioContext.Reset(ctor);
	
	Nan::Set(target, JS_STR("AudioContext"), ctor);
	
	
}


NAN_METHOD(AudioContext::newCtor) {
	
	CTOR_CHECK("AudioContext");
	
	AudioContext *audioContext = nullptr;
	
	if (info.Length() > 0) {
		
		REQ_OBJ_ARG(0, opts);
		
		if (opts->Has(JS_STR("sampleRate"))) {
			
			if ( ! opts->Get(JS_STR("sampleRate"))->IsNumber() ) {
				return Nan::ThrowTypeError("Type of 'opts.sampleRate' must be 'number'.");
			}
			
			float sampleRate = static_cast<float>(opts->Get(JS_STR("sampleRate"))->NumberValue());
			audioContext = new AudioContext(sampleRate);
			
		}
		
	}
	
	if ( ! audioContext ) {
		audioContext = new AudioContext();
	}
	
	audioContext->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(AudioContext::destroy) { THIS_AUDIO_CONTEXT; THIS_CHECK;
	
	audioContext->_destroy();
	
}


NAN_GETTER(AudioContext::isDestroyedGetter) { THIS_AUDIO_CONTEXT;
	
	RET_VALUE(JS_BOOL(audioContext->_isDestroyed));
	
}
