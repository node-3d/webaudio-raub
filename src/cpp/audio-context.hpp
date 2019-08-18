#ifndef _AUDIO_CONTEXT_HPP_
#define _AUDIO_CONTEXT_HPP_

#include "common.hpp"


class AudioContext : public Napi::ObjectWrap<AudioContext>, public CommonCtx {
	
public:
	
	static void init(Napi::Env env, Napi::Object exports);
	
	explicit AudioContext(const Napi::CallbackInfo &info);
	~AudioContext();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
private:
	
	static Napi::FunctionReference _constructor;
	
	double _baseLatency;
	
	JS_METHOD(suspend);
	JS_METHOD(close);
	JS_METHOD(getOutputTimestamp);
	JS_METHOD(createMediaElementSource);
	JS_METHOD(createMediaStreamSource);
	JS_METHOD(createMediaStreamDestination);
	
	JS_GETTER(baseLatencyGetter);
	
};


#endif // _AUDIO_CONTEXT_HPP_
