#ifndef _AUDIO_LISTENER_HPP_
#define _AUDIO_LISTENER_HPP_


#include <addon-tools.hpp>

namespace lab { class AudioListener; };


class AudioListener : public Napi::ObjectWrap<AudioListener> {
	
public:
	
	typedef std::shared_ptr<lab::AudioListener> ListenerPtr;
	
	~AudioListener();
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isAudioListener(Napi::Object obj);
	
	// Make a new instance from C++ land
	explicit AudioListener(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	explicit AudioListener(Napi::Object context, ListenerPtr listener);
	
	static Napi::FunctionReference _ctorAudioListener;
	
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
	
	
// JS methods and props, available through V8 APIs
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
