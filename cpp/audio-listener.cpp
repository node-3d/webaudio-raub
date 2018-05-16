#include <cstdlib>
//#include <iostream> // -> cout << "..." << endl;


#include <LabSound/core/AudioListener.h>
#include <LabSound/core/AudioParam.h>
#include <LabSound/core/FloatPoint3D.h>

#include "audio-listener.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_AUDIO_LISTENER                                                   \
	AudioListener *audioListener = Nan::ObjectWrap::Unwrap<AudioListener>(info.This());

#define THIS_CHECK                                                            \
	if (audioListener->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (audioListener->CACHE == V) {                                          \
		return;                                                               \
	}                                                                         \
	audioListener->CACHE = V;

#define PARAM_GETTER(NAME)                                                    \
NAN_GETTER(AudioListener::NAME ## Getter) { THIS_AUDIO_LISTENER; THIS_CHECK;  \
	RET_VALUE(JS_OBJ(audioListener->_ ## NAME));                              \
}


// ------ Constructor and Destructor

AudioListener::AudioListener(V8_VAR_OBJ context, ListenerPtr listener) {
	
	_impl = listener;
	_context.Reset(context);
	
	_positionX.Reset(AudioParam::getNew(context, _impl->positionX()));
	_positionY.Reset(AudioParam::getNew(context, _impl->positionY()));
	_positionZ.Reset(AudioParam::getNew(context, _impl->positionZ()));
	_forwardX.Reset(AudioParam::getNew(context, _impl->forwardX()));
	_forwardY.Reset(AudioParam::getNew(context, _impl->forwardY()));
	_forwardZ.Reset(AudioParam::getNew(context, _impl->forwardZ()));
	_upX.Reset(AudioParam::getNew(context, _impl->upX()));
	_upY.Reset(AudioParam::getNew(context, _impl->upY()));
	_upZ.Reset(AudioParam::getNew(context, _impl->upZ()));
	
	_isDestroyed = false;
	
}


AudioListener::~AudioListener() {
	
	_destroy();
	
}


void AudioListener::_destroy() { DES_CHECK;
	
	_context.Reset();
	
	_positionX.Reset();
	_positionY.Reset();
	_positionZ.Reset();
	_forwardX.Reset();
	_forwardY.Reset();
	_forwardZ.Reset();
	_upX.Reset();
	_upY.Reset();
	_upZ.Reset();
	
	_isDestroyed = true;
	
}


// ------ Methods and props


NAN_METHOD(AudioListener::setPosition) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	REQ_FLOAT_ARG(0, x);
	REQ_FLOAT_ARG(1, y);
	REQ_FLOAT_ARG(2, z);
	
	audioListener->_impl->setPosition(x, y, z);
	
}


NAN_METHOD(AudioListener::setOrientation) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	REQ_FLOAT_ARG(0, x);
	REQ_FLOAT_ARG(1, y);
	REQ_FLOAT_ARG(2, z);
	REQ_FLOAT_ARG(3, xUp);
	REQ_FLOAT_ARG(4, yUp);
	REQ_FLOAT_ARG(5, zUp);
	
	audioListener->_impl->setOrientation(x, y, z, xUp, yUp, zUp);
	
}


PARAM_GETTER(positionX);
PARAM_GETTER(positionY);
PARAM_GETTER(positionZ);
PARAM_GETTER(forwardX);
PARAM_GETTER(forwardY);
PARAM_GETTER(forwardZ);
PARAM_GETTER(upX);
PARAM_GETTER(upY);
PARAM_GETTER(upZ);


// ------ System methods and props for ObjectWrap

V8_STORE_FT AudioListener::_protoAudioListener;
V8_STORE_FUNC AudioListener::_ctorAudioListener;


void AudioListener::init(V8_VAR_OBJ target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);

	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AudioListener"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
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
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoAudioListener.Reset(proto);
	_ctorAudioListener.Reset(ctor);
	
	Nan::Set(target, JS_STR("AudioListener"), ctor);
	
	
}


bool AudioListener::isAudioListener(V8_VAR_OBJ obj) {
	return Nan::New(_protoAudioListener)->HasInstance(obj);
}


V8_VAR_OBJ AudioListener::getNew(V8_VAR_OBJ context, ListenerPtr listener) {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorAudioListener);
	V8_VAR_EXT extListener = JS_EXT(&listener);
	V8_VAR_VAL argv[] = { context, extListener };
	return Nan::NewInstance(ctor, 2, argv).ToLocalChecked();
	
}


NAN_METHOD(AudioListener::newCtor) {
	
	CTOR_CHECK("AudioListener");
	
	REQ_OBJ_ARG(0, context);
	REQ_EXT_ARG(1, extListener);
	
	ListenerPtr *listener = reinterpret_cast<ListenerPtr *>(extListener->Value());
	
	AudioListener *audioListener = new AudioListener(context, *listener);
	audioListener->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(AudioListener::destroy) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	audioListener->_destroy();
	
}


NAN_GETTER(AudioListener::isDestroyedGetter) { THIS_AUDIO_LISTENER;
	
	RET_VALUE(JS_BOOL(audioListener->_isDestroyed));
	
}
