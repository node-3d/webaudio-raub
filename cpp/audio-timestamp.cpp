#include <cstdlib>
#include <iostream>

#include "audio-timestamp.hpp"

using namespace v8;
using namespace node;
using namespace std;


#define THIS_AUDIO_TIMESTAMP                                                    \
	AudioTimestamp *audioTimestamp = ObjectWrap::Unwrap<AudioTimestamp>(info.This());

#define THIS_CHECK                                                            \
	if (audioTimestamp->_isDestroyed) return;

#define DES_CHECK                                                             \
	if (_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (audioTimestamp->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	audioTimestamp->CACHE = V;


Nan::Persistent<v8::Function> AudioTimestamp::_constructor;


void AudioTimestamp::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AudioTimestamp"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	
	// -------- dynamic
	
	
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	
	
	
	_constructor.Reset(ctor);
	Nan::Set(target, JS_STR("AudioTimestamp"), ctor);
	
	
}


NAN_METHOD(AudioTimestamp::newCtor) {
	
	CTOR_CHECK("AudioTimestamp");
	
	AudioTimestamp *audioTimestamp = new AudioTimestamp();
	audioTimestamp->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


AudioTimestamp::AudioTimestamp() {
	
	_isDestroyed = false;
	
}


AudioTimestamp::~AudioTimestamp() {
	
	_destroy();
	
}


void AudioTimestamp::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	
	
}



NAN_METHOD(AudioTimestamp::destroy) { THIS_AUDIO_TIMESTAMP; THIS_CHECK;
	
	audioTimestamp->_destroy();
	
}




NAN_GETTER(AudioTimestamp::isDestroyedGetter) { THIS_AUDIO_TIMESTAMP;
	
	RET_VALUE(JS_BOOL(audioTimestamp->_isDestroyed));
	
}


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

