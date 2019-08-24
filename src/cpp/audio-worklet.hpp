#ifndef _AUDIO_WORKLET_HPP_
#define _AUDIO_WORKLET_HPP_


#include "common.hpp"


class AudioWorklet : public CommonNode<AudioWorklet> {
	
public:
	
	~AudioWorklet();
	explicit AudioWorklet(const Napi::CallbackInfo &info);
	
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isAudioWorklet(Napi::Object obj);
	
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
