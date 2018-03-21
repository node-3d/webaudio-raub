#include <cstdlib>
//#include <iostream> // -> std::cout << "..." << std::endl;


#include "audio-listener.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_AUDIO_LISTENER                                                    \
	AudioListener *audioListener = ObjectWrap::Unwrap<AudioListener>(info.This());

#define THIS_CHECK                                                            \
	if (audioListener->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (audioListener->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	audioListener->CACHE = V;


// ------ Constructor and Destructor

AudioListener::AudioListener() {
	
	_isDestroyed = false;
	
}


AudioListener::~AudioListener() {
	
	_destroy();
	
}


void AudioListener::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
}


// ------ Methods and props


NAN_METHOD(AudioListener::setPosition) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	REQ_FLOAT_ARG(0, x);
	REQ_FLOAT_ARG(1, y);
	REQ_FLOAT_ARG(2, z);
	
	// TODO: do something?
	
}


NAN_METHOD(AudioListener::setOrientation) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	REQ_FLOAT_ARG(0, x);
	REQ_FLOAT_ARG(1, y);
	REQ_FLOAT_ARG(2, z);
	REQ_FLOAT_ARG(3, xUp);
	REQ_FLOAT_ARG(4, yUp);
	REQ_FLOAT_ARG(5, zUp);
	
	// TODO: do something?
	
}


NAN_GETTER(AudioListener::positionXGetter) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(audioListener->_positionX));
	
}


NAN_GETTER(AudioListener::positionYGetter) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(audioListener->_positionY));
	
}


NAN_GETTER(AudioListener::positionZGetter) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(audioListener->_positionZ));
	
}


NAN_GETTER(AudioListener::forwardXGetter) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(audioListener->_forwardX));
	
}


NAN_GETTER(AudioListener::forwardYGetter) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(audioListener->_forwardY));
	
}


NAN_GETTER(AudioListener::forwardZGetter) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(audioListener->_forwardZ));
	
}


NAN_GETTER(AudioListener::upXGetter) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(audioListener->_upX));
	
}


NAN_GETTER(AudioListener::upYGetter) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(audioListener->_upY));
	
}


NAN_GETTER(AudioListener::upZGetter) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(audioListener->_upZ));
	
}


// ------ System methods and props for ObjectWrap

Nan::Persistent<v8::FunctionTemplate> AudioListener::_protoAudioListener;
Nan::Persistent<v8::Function> AudioListener::_ctorAudioListener;


void AudioListener::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AudioListener"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, positionX);
	ACCESSOR_R(obj, positionY);
	ACCESSOR_R(obj, positionZ);
	ACCESSOR_R(obj, forwardX);
	ACCESSOR_R(obj, forwardY);
	ACCESSOR_R(obj, forwardZ);
	ACCESSOR_R(obj, upX);
	ACCESSOR_R(obj, upY);
	ACCESSOR_R(obj, upZ);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	Nan::SetPrototypeMethod(proto, "setPosition", setPosition);
	Nan::SetPrototypeMethod(proto, "setOrientation", setOrientation);
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoAudioListener.Reset(proto);
	_ctorAudioListener.Reset(ctor);
	
	Nan::Set(target, JS_STR("AudioListener"), ctor);
	
	
}


NAN_METHOD(AudioListener::newCtor) {
	
	CTOR_CHECK("AudioListener");
	
	AudioListener *audioListener = new AudioListener();
	audioListener->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(AudioListener::destroy) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	audioListener->_destroy();
	
}


NAN_GETTER(AudioListener::isDestroyedGetter) { THIS_AUDIO_LISTENER;
	
	RET_VALUE(JS_BOOL(audioListener->_isDestroyed));
	
}
