#include <cstdlib>
#include <iostream>

#include "audio-listener.hpp"

using namespace v8;
using namespace node;
using namespace std;


#define THIS_AUDIO_LISTENER                                                    \
	AudioListener *audioListener = ObjectWrap::Unwrap<AudioListener>(info.This());

#define THIS_CHECK                                                            \
	if (audioListener->_isDestroyed) return;

#define DES_CHECK                                                             \
	if (_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (audioListener->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	audioListener->CACHE = V;


Nan::Persistent<v8::Function> AudioListener::_constructor;


void AudioListener::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AudioListener"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	
	// -------- dynamic
	
	
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	
	
	
	_constructor.Reset(ctor);
	Nan::Set(target, JS_STR("AudioListener"), ctor);
	
	
}


NAN_METHOD(AudioListener::newCtor) {
	
	CTOR_CHECK("AudioListener");
	
	AudioListener *audioListener = new AudioListener();
	audioListener->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


AudioListener::AudioListener() {
	
	_isDestroyed = false;
	
}


AudioListener::~AudioListener() {
	
	_destroy();
	
}


void AudioListener::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	
	
}



NAN_METHOD(AudioListener::destroy) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	audioListener->_destroy();
	
}


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



NAN_GETTER(AudioListener::isDestroyedGetter) { THIS_AUDIO_LISTENER;
	
	RET_VALUE(JS_BOOL(audioListener->_isDestroyed));
	
}


NAN_GETTER(AudioListener::positionXGetter) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	RET_VALUE(JS_FLOAT(audioListener->_positionX));
	
}

NAN_SETTER(AudioListener::positionXSetter) { THIS_AUDIO_LISTENER; THIS_CHECK; SETTER_FLOAT_ARG;
	
	CACHE_CAS(_positionX, v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(AudioListener::positionYGetter) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	RET_VALUE(JS_FLOAT(audioListener->_positionY));
	
}

NAN_SETTER(AudioListener::positionYSetter) { THIS_AUDIO_LISTENER; THIS_CHECK; SETTER_FLOAT_ARG;
	
	CACHE_CAS(_positionY, v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(AudioListener::positionZGetter) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	RET_VALUE(JS_FLOAT(audioListener->_positionZ));
	
}

NAN_SETTER(AudioListener::positionZSetter) { THIS_AUDIO_LISTENER; THIS_CHECK; SETTER_FLOAT_ARG;
	
	CACHE_CAS(_positionZ, v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(AudioListener::forwardXGetter) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	RET_VALUE(JS_FLOAT(audioListener->_forwardX));
	
}

NAN_SETTER(AudioListener::forwardXSetter) { THIS_AUDIO_LISTENER; THIS_CHECK; SETTER_FLOAT_ARG;
	
	CACHE_CAS(_forwardX, v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(AudioListener::forwardYGetter) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	RET_VALUE(JS_FLOAT(audioListener->_forwardY));
	
}

NAN_SETTER(AudioListener::forwardYSetter) { THIS_AUDIO_LISTENER; THIS_CHECK; SETTER_FLOAT_ARG;
	
	CACHE_CAS(_forwardY, v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(AudioListener::forwardZGetter) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	RET_VALUE(JS_FLOAT(audioListener->_forwardZ));
	
}

NAN_SETTER(AudioListener::forwardZSetter) { THIS_AUDIO_LISTENER; THIS_CHECK; SETTER_FLOAT_ARG;
	
	CACHE_CAS(_forwardZ, v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(AudioListener::upXGetter) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	RET_VALUE(JS_FLOAT(audioListener->_upX));
	
}

NAN_SETTER(AudioListener::upXSetter) { THIS_AUDIO_LISTENER; THIS_CHECK; SETTER_FLOAT_ARG;
	
	CACHE_CAS(_upX, v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(AudioListener::upYGetter) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	RET_VALUE(JS_FLOAT(audioListener->_upY));
	
}

NAN_SETTER(AudioListener::upYSetter) { THIS_AUDIO_LISTENER; THIS_CHECK; SETTER_FLOAT_ARG;
	
	CACHE_CAS(_upY, v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(AudioListener::upZGetter) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	RET_VALUE(JS_FLOAT(audioListener->_upZ));
	
}

NAN_SETTER(AudioListener::upZSetter) { THIS_AUDIO_LISTENER; THIS_CHECK; SETTER_FLOAT_ARG;
	
	CACHE_CAS(_upZ, v);
	
	// TODO: may be additional actions on change?
	
}

