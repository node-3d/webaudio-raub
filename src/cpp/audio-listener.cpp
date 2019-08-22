#include <LabSound/LabSound.h>

#include "audio-listener.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"


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


Napi::Object AudioListener::create(Napi::Env env, Napi::Object context, ListenerPtr listener) {
	Napi::Function ctor = _constructor.Value().As<Napi::Function>();
	std::vector<napi_value> args;
	args.push_back(context);
	args.push_back(JS_EXT(&listener));
	return ctor.New(args);
}


AudioListener::AudioListener(const Napi::CallbackInfo &info):
Napi::ObjectWrap<AudioListener>(info),
CommonListener(info.Env(), "AudioListener") { NAPI_ENV;
	
	REQ_OBJ_ARG(0, context);
	REQ_EXT_ARG(1, extListener);
	
	ListenerPtr *param = reinterpret_cast<ListenerPtr *>(extListener.Data());
	
	reset(context, *param);
	
	_positionX.Reset(AudioParam::create(env, context, _impl->positionX()));
	_positionY.Reset(AudioParam::create(env, context, _impl->positionY()));
	_positionZ.Reset(AudioParam::create(env, context, _impl->positionZ()));
	_forwardX.Reset(AudioParam::create(env, context, _impl->forwardX()));
	_forwardY.Reset(AudioParam::create(env, context, _impl->forwardY()));
	_forwardZ.Reset(AudioParam::create(env, context, _impl->forwardZ()));
	_upX.Reset(AudioParam::create(env, context, _impl->upX()));
	_upY.Reset(AudioParam::create(env, context, _impl->upY()));
	_upZ.Reset(AudioParam::create(env, context, _impl->upZ()));
	
}


AudioListener::~AudioListener() {
	_destroy();
}


void AudioListener::_destroy() { DES_CHECK;
	CommonListener::_destroy();
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


JS_METHOD(AudioListener::destroy) { THIS_CHECK;
	
	_destroy();
	
}
