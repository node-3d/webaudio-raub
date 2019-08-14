#ifndef _AUDIO_CONTEXT_HPP_
#define _AUDIO_CONTEXT_HPP_


#include <addon-tools.hpp>

#include "base-audio-context.hpp"


class AudioContext : public BaseAudioContext {
	
public:
	
	~AudioContext();
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	// Make a new instance from C++ land
	explicit AudioContext(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props
protected:
	
	AudioContext();
	explicit AudioContext(float sampleRate);
	
	static V8_STORE_FT _protoAudioContext; // for inheritance
	static Napi::FunctionReference _ctorAudioContext;
	
	bool _isDestroyed;
	
	double _baseLatency;
	
	
// System methods and props for ObjectWrap
private:
	
	JS_METHOD(newCtor);
	
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
