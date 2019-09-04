#ifndef _AUDIO_LISTENER_HPP_
#define _AUDIO_LISTENER_HPP_

#include "common.hpp"


class AudioListener : public CommonListener<AudioListener> {
	
public:
	
	static void init(Napi::Env env, Napi::Object exports);
	static Napi::Object create(Napi::Env env, Napi::Object context, ListenerPtr listener);
	
	explicit AudioListener(const Napi::CallbackInfo &info);
	~AudioListener();
	
	void _destroy();
	
private:
	
	static Napi::FunctionReference _constructor;
	
	Napi::ObjectReference _positionX;
	Napi::ObjectReference _positionY;
	Napi::ObjectReference _positionZ;
	Napi::ObjectReference _forwardX;
	Napi::ObjectReference _forwardY;
	Napi::ObjectReference _forwardZ;
	Napi::ObjectReference _upX;
	Napi::ObjectReference _upY;
	Napi::ObjectReference _upZ;
	
	JS_DECLARE_METHOD(destroy);
	
	JS_DECLARE_METHOD(setPosition);
	JS_DECLARE_METHOD(setOrientation);
	
	JS_DECLARE_GETTER(positionX);
	JS_DECLARE_GETTER(positionY);
	JS_DECLARE_GETTER(positionZ);
	
	JS_DECLARE_GETTER(forwardX);
	JS_DECLARE_GETTER(forwardY);
	JS_DECLARE_GETTER(forwardZ);
	
	JS_DECLARE_GETTER(upX);
	JS_DECLARE_GETTER(upY);
	JS_DECLARE_GETTER(upZ);
	
};


#endif // _AUDIO_LISTENER_HPP_
