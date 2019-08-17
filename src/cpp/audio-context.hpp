#ifndef _AUDIO_CONTEXT_HPP_
#define _AUDIO_CONTEXT_HPP_


#include "common.hpp"

#include "base-audio-context.hpp"


class AudioContext : public BaseAudioContext {
	
public:
	
	~AudioContext();
	explicit AudioContext(const Napi::CallbackInfo &info);
	
	static void init(Napi::Env env, Napi::Object exports);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props
protected:
	
	AudioContext();
	explicit AudioContext(float sampleRate);
	
	static Napi::FunctionReference _constructor;
	
	bool _isDestroyed;
	
	double _baseLatency;
	
	
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	JS_METHOD(suspend);
	JS_METHOD(close);
	JS_METHOD(getOutputTimestamp);
	JS_METHOD(createMediaElementSource);
	JS_METHOD(createMediaStreamSource);
	JS_METHOD(createMediaStreamDestination);
	
	JS_GETTER(baseLatencyGetter);
	
};


#endif // _AUDIO_CONTEXT_HPP_
