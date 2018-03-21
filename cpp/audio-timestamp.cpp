#include <cstdlib>
//#include <iostream> // -> std::cout << "..." << std::endl;


#include "audio-timestamp.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_AUDIO_TIMESTAMP                                                    \
	AudioTimestamp *audioTimestamp = ObjectWrap::Unwrap<AudioTimestamp>(info.This());

#define THIS_CHECK                                                            \
	if (audioTimestamp->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (audioTimestamp->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	audioTimestamp->CACHE = V;


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




NAN_GETTER(AudioTimestamp::contextTimeGetter) { THIS_AUDIO_TIMESTAMP; THIS_CHECK;
	
	RET_VALUE(JS_DOUBLE(audioTimestamp->_contextTime));
	
}

NAN_SETTER(AudioTimestamp::contextTimeSetter) { THIS_AUDIO_TIMESTAMP; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	CACHE_CAS(_contextTime, v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(AudioTimestamp::performanceTimeGetter) { THIS_AUDIO_TIMESTAMP; THIS_CHECK;
	
	RET_VALUE(JS_DOUBLE(audioTimestamp->_performanceTime));
	
}

NAN_SETTER(AudioTimestamp::performanceTimeSetter) { THIS_AUDIO_TIMESTAMP; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	CACHE_CAS(_performanceTime, v);
	
	// TODO: may be additional actions on change?
	
}



// ------ System methods and props for ObjectWrap

Nan::Persistent<v8::FunctionTemplate> AudioTimestamp::_protoAudioTimestamp;
Nan::Persistent<v8::Function> AudioTimestamp::_ctorAudioTimestamp;


void AudioTimestamp::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AudioTimestamp"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_RW(obj, contextTime);
	ACCESSOR_RW(obj, performanceTime);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoAudioTimestamp.Reset(proto);
	_ctorAudioTimestamp.Reset(ctor);
	
	Nan::Set(target, JS_STR("AudioTimestamp"), ctor);
	
	
}


NAN_METHOD(AudioTimestamp::newCtor) {
	
	CTOR_CHECK("AudioTimestamp");
	
	AudioTimestamp *audioTimestamp = new AudioTimestamp();
	audioTimestamp->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(AudioTimestamp::destroy) { THIS_AUDIO_TIMESTAMP; THIS_CHECK;
	
	audioTimestamp->_destroy();
	
}


NAN_GETTER(AudioTimestamp::isDestroyedGetter) { THIS_AUDIO_TIMESTAMP;
	
	RET_VALUE(JS_BOOL(audioTimestamp->_isDestroyed));
	
}
