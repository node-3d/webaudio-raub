#include <LabSound/LabSound.h>

#include "audio-listener.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"


IMPLEMENT_ES5_CLASS(AudioListener);

void AudioListener::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_METHOD(setOrientation);
	JS_ASSIGN_METHOD(setPosition);
	JS_ASSIGN_GETTER(upZ);
	JS_ASSIGN_GETTER(upY);
	JS_ASSIGN_GETTER(upX);
	JS_ASSIGN_GETTER(forwardZ);
	JS_ASSIGN_GETTER(forwardY);
	JS_ASSIGN_GETTER(forwardX);
	JS_ASSIGN_GETTER(positionZ);
	JS_ASSIGN_GETTER(positionY);
	JS_ASSIGN_GETTER(positionX);
	JS_ASSIGN_METHOD(destroy);
	
	exports.Set("AudioListener", ctor);
	
}


AudioListener::AudioListener(const Napi::CallbackInfo &info):
CommonListener(info.This(), "AudioListener") { NAPI_ENV;
	std::cout << "AudioListener() 1 " << info.Env().IsExceptionPending() << std::endl;
	super(info);
	std::cout << "AudioListener() 2 " << info.Env().IsExceptionPending() << std::endl;
	REQ_OBJ_ARG(0, context);
	REQ_EXT_ARG(1, extListener);
	
	ListenerPtr *param = reinterpret_cast<ListenerPtr *>(extListener.Data());
	
	reset(context, *param);
	std::cout << "AudioListener() 3 " << info.Env().IsExceptionPending() << std::endl;
	REQ_FUN_ARG(2, paramCtor);
	
	napi_value argv[2];
	argv[0] = context;
	
	argv[1] = JS_EXT(&_impl->positionX());
	_positionX.Reset(paramCtor.New(2, argv));
	std::cout << "AudioListener() 4 " << info.Env().IsExceptionPending() << std::endl;
	argv[1] = JS_EXT(&_impl->positionY());
	_positionY.Reset(paramCtor.New(2, argv));
	std::cout << "AudioListener() 4 " << info.Env().IsExceptionPending() << std::endl;
	
	argv[1] = JS_EXT(&_impl->positionZ());
	_positionZ.Reset(paramCtor.New(2, argv));
	std::cout << "AudioListener() 5 " << info.Env().IsExceptionPending() << std::endl;
	
	argv[1] = JS_EXT(&_impl->forwardX());
	_forwardX.Reset(paramCtor.New(2, argv));
	std::cout << "AudioListener() 6 " << info.Env().IsExceptionPending() << std::endl;
	
	argv[1] = JS_EXT(&_impl->forwardY());
	_forwardY.Reset(paramCtor.New(2, argv));
	std::cout << "AudioListener() 7 " << info.Env().IsExceptionPending() << std::endl;
	
	argv[1] = JS_EXT(&_impl->forwardZ());
	_forwardZ.Reset(paramCtor.New(2, argv));
	std::cout << "AudioListener() 8 " << info.Env().IsExceptionPending() << std::endl;
	
	argv[1] = JS_EXT(&_impl->upX());
	_upX.Reset(paramCtor.New(2, argv));
	std::cout << "AudioListener() 9 " << info.Env().IsExceptionPending() << std::endl;
	
	argv[1] = JS_EXT(&_impl->upY());
	_upY.Reset(paramCtor.New(2, argv));
	std::cout << "AudioListener() 10 " << info.Env().IsExceptionPending() << std::endl;
	
	argv[1] = JS_EXT(&_impl->upZ());
	_upZ.Reset(paramCtor.New(2, argv));
	std::cout << "AudioListener() 11 " << info.Env().IsExceptionPending() << std::endl;
}


AudioListener::~AudioListener() {
	_destroy();
}


void AudioListener::_destroy() { DES_CHECK;
	_positionX.Reset();
	_positionY.Reset();
	_positionZ.Reset();
	_forwardX.Reset();
	_forwardY.Reset();
	_forwardZ.Reset();
	_upX.Reset();
	_upY.Reset();
	_upZ.Reset();
	CommonListener::_destroy();
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


JS_IMPLEMENT_METHOD(AudioListener, setPosition) { THIS_CHECK;
	
	REQ_FLOAT_ARG(0, x);
	REQ_FLOAT_ARG(1, y);
	REQ_FLOAT_ARG(2, z);
	
	_impl->setPosition(x, y, z);
	RET_UNDEFINED;
	
}


JS_IMPLEMENT_METHOD(AudioListener, setOrientation) { THIS_CHECK;
	
	REQ_FLOAT_ARG(0, x);
	REQ_FLOAT_ARG(1, y);
	REQ_FLOAT_ARG(2, z);
	REQ_FLOAT_ARG(3, xUp);
	REQ_FLOAT_ARG(4, yUp);
	REQ_FLOAT_ARG(5, zUp);
	
	_impl->setOrientation(x, y, z, xUp, yUp, zUp);
	RET_UNDEFINED;
	
}

JS_IMPLEMENT_METHOD(AudioListener, destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	RET_UNDEFINED;
	
}
