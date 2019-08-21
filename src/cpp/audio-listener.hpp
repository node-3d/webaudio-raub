#ifndef _AUDIO_LISTENER_HPP_
#define _AUDIO_LISTENER_HPP_

#include "common.hpp"


class AudioListener : public Napi::ObjectWrap<AudioListener>, private CommonListener {
	
public:
	
	static void init(Napi::Env env, Napi::Object exports);
	static Napi::Object create(Napi::Env env, Napi::Object context, ListenerPtr listener);
	
	explicit ConvolverNode(const Napi::CallbackInfo &info);
	~ConvolverNode();
	
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
	
	JS_METHOD(destroy);
	
	JS_METHOD(setPosition);
	JS_METHOD(setOrientation);
	
	JS_GETTER(positionXGetter);
	JS_GETTER(positionYGetter);
	JS_GETTER(positionZGetter);
	
	JS_GETTER(forwardXGetter);
	JS_GETTER(forwardYGetter);
	JS_GETTER(forwardZGetter);
	
	JS_GETTER(upXGetter);
	JS_GETTER(upYGetter);
	JS_GETTER(upZGetter);
	
};


#endif // _AUDIO_LISTENER_HPP_
