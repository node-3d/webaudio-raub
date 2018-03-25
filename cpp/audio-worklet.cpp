#include <cstdlib>
//#include <iostream> // -> cout << "..." << endl;


#include "audio-worklet.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_AUDIO_WORKLET                                                    \
	AudioWorklet *audioWorklet = Nan::ObjectWrap::Unwrap<AudioWorklet>(info.This());

#define THIS_CHECK                                                            \
	if (audioWorklet->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (audioWorklet->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	audioWorklet->CACHE = V;


// ------ Constructor and Destructor

AudioWorklet::AudioWorklet() {
	
	_isDestroyed = false;
	
}


AudioWorklet::~AudioWorklet() {
	
	_destroy();
	
}


void AudioWorklet::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
}


// ------ Methods and props




// ------ System methods and props for ObjectWrap

Nan::Persistent<FunctionTemplate> AudioWorklet::_protoAudioWorklet;
Nan::Persistent<Function> AudioWorklet::_ctorAudioWorklet;


void AudioWorklet::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AudioWorklet"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoAudioWorklet.Reset(proto);
	_ctorAudioWorklet.Reset(ctor);
	
	Nan::Set(target, JS_STR("AudioWorklet"), ctor);
	
	
}


Local<Object> AudioWorklet::getNew() {
	
	Local<Function> ctor = Nan::New(_ctorAudioWorklet);
	// Local<Value> argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


NAN_METHOD(AudioWorklet::newCtor) {
	
	CTOR_CHECK("AudioWorklet");
	
	AudioWorklet *audioWorklet = new AudioWorklet();
	audioWorklet->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(AudioWorklet::destroy) { THIS_AUDIO_WORKLET; THIS_CHECK;
	
	audioWorklet->_destroy();
	
}


NAN_GETTER(AudioWorklet::isDestroyedGetter) { THIS_AUDIO_WORKLET;
	
	RET_VALUE(JS_BOOL(audioWorklet->_isDestroyed));
	
}
