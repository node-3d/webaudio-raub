#include <LabSound/LabSound.h>

#include "audio-listener.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"


// ------ Constructor and Destructor

AudioListener::AudioListener(Napi::Object context, ListenerPtr listener):
Napi::ObjectWrap<AudioListener>(info),
CommonListener(info.Env(), "AudioListener") {
	
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


JS_METHOD(AudioListener::setPosition) { THIS_CHECK;
	
	REQ_FLOAT_ARG(0, x);
	REQ_FLOAT_ARG(1, y);
	REQ_FLOAT_ARG(2, z);
	
	_impl->setPosition(x, y, z);
	
}


JS_METHOD(AudioListener::setOrientation) { THIS_CHECK;
	
	REQ_FLOAT_ARG(0, x);
	REQ_FLOAT_ARG(1, y);
	REQ_FLOAT_ARG(2, z);
	REQ_FLOAT_ARG(3, xUp);
	REQ_FLOAT_ARG(4, yUp);
	REQ_FLOAT_ARG(5, zUp);
	
	_impl->setOrientation(x, y, z, xUp, yUp, zUp);
	
}


PARAM_GETTER(AudioListener, positionX);
PARAM_GETTER(AudioListener, positionY);
PARAM_GETTER(AudioListener, positionZ);
PARAM_GETTER(AudioListener, forwardX);
PARAM_GETTER(AudioListener, forwardY);
PARAM_GETTER(AudioListener, forwardZ);
PARAM_GETTER(AudioListener, upX);
PARAM_GETTER(AudioListener, upY);
PARAM_GETTER(AudioListener, upZ);


// ------ System methods and props for Napi::ObjectWrap

Napi::FunctionReference AudioListener::_constructor;


void AudioListener::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "AudioListener", {
		ACCESSOR_M(AudioListener, setOrientation),
		ACCESSOR_M(AudioListener, setPosition),
		ACCESSOR_M(AudioListener, destroy),
		ACCESSOR_R(AudioListener, upZ),
		ACCESSOR_R(AudioListener, upY),
		ACCESSOR_R(AudioListener, upX),
		ACCESSOR_R(AudioListener, forwardZ),
		ACCESSOR_R(AudioListener, forwardY),
		ACCESSOR_R(AudioListener, forwardX),
		ACCESSOR_R(AudioListener, positionZ),
		ACCESSOR_R(AudioListener, positionY),
		ACCESSOR_R(AudioListener, positionX),
		ACCESSOR_R(AudioListener, isDestroyed)
	});
	
	_constructor = Napi::Persistent(ctor);
	_constructor.SuppressDestruct();
	
	exports.Set("AudioListener", ctor);
	
}


bool AudioListener::isAudioListener(Napi::Object obj) {
	return obj.InstanceOf(_constructor.Value());
}


Napi::Object AudioListener::getNew(Napi::Object context, ListenerPtr listener) {
	
	Napi::Function ctor = Nan::New(_constructor);
	V8_VAR_EXT extListener = JS_EXT(&listener);
	Napi::Value argv[] = { context, extListener };
	return Nan::NewInstance(ctor, 2, argv).ToLocalChecked();
	
}


AudioListener::AudioListener(const Napi::CallbackInfo &info): Napi::ObjectWrap<AudioListener>(info) {
	
	CTOR_CHECK("AudioListener");
	
	REQ_OBJ_ARG(0, context);
	REQ_EXT_ARG(1, extListener);
	
	ListenerPtr *listener = reinterpret_cast<ListenerPtr *>(extListener->Value());
	
	AudioListener *audioListener = new AudioListener(context, *listener);
	
}


JS_METHOD(AudioListener::destroy) { THIS_CHECK;
	
	_destroy();
	
}


JS_GETTER(AudioListener::isDestroyedGetter) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
