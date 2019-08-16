#ifndef _AUDIO_WORKLET_HPP_
#define _AUDIO_WORKLET_HPP_


#include <addon-tools.hpp>


class AudioWorklet : public Napi::ObjectWrap<AudioWorklet> {
	
public:
	
	~AudioWorklet();
	AudioWorklet(const Napi::CallbackInfo &info);
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isAudioWorklet(Napi::Object obj);
	
	// Make a new instance from C++ land
	explicit AudioWorklet(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
protected:
	
	AudioWorklet();
	
	static Napi::FunctionReference _constructor;
	
	bool _isDestroyed;
	
	
	
	
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	
	
};


#endif // _AUDIO_WORKLET_HPP_
