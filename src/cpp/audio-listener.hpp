#ifndef _AUDIO_LISTENER_HPP_
#define _AUDIO_LISTENER_HPP_


#include "common.hpp"

namespace lab { class AudioListener; };


class AudioListener : public Napi::ObjectWrap<AudioListener>, private CommonNode {
	
public:
	
	typedef std::shared_ptr<lab::AudioListener> ListenerPtr;
	
	~AudioListener();
	explicit AudioListener(const Napi::CallbackInfo &info);
	
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isAudioListener(Napi::Object obj);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
protected:
	
	explicit AudioListener(Napi::Object context, ListenerPtr listener);
	
	static Napi::FunctionReference _constructor;
	
	bool _isDestroyed;
	
	Napi::ObjectReference _positionX;
	Napi::ObjectReference _positionY;
	Napi::ObjectReference _positionZ;
	Napi::ObjectReference _forwardX;
	Napi::ObjectReference _forwardY;
	Napi::ObjectReference _forwardZ;
	Napi::ObjectReference _upX;
	Napi::ObjectReference _upY;
	Napi::ObjectReference _upZ;
	
	ListenerPtr _impl;
	Napi::ObjectReference _context;
	
	
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
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
