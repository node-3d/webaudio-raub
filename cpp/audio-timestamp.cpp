#include <cstdlib>
//#include <iostream> // -> cout << "..." << endl;


#include "audio-timestamp.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_AUDIO_TIMESTAMP                                                    \
	AudioTimestamp *audioTimestamp = Nan::ObjectWrap::Unwrap<AudioTimestamp>(info.This());

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

V8_STORE_FT AudioTimestamp::_protoAudioTimestamp;
V8_STORE_FUNC AudioTimestamp::_ctorAudioTimestamp;


void AudioTimestamp::init(V8_VAR_OBJ target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AudioTimestamp"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_RW(obj, contextTime);
	ACCESSOR_RW(obj, performanceTime);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoAudioTimestamp.Reset(proto);
	_ctorAudioTimestamp.Reset(ctor);
	
	Nan::Set(target, JS_STR("AudioTimestamp"), ctor);
	
	
}


V8_VAR_OBJ AudioTimestamp::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorAudioTimestamp);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
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
