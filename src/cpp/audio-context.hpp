#ifndef _AUDIO_CONTEXT_HPP_
#define _AUDIO_CONTEXT_HPP_

#include "common.hpp"


class AudioContext : public CommonCtx<AudioContext> {
	
public:
	
	static void init(Napi::Env env, Napi::Object exports);
	
	explicit AudioContext(const Napi::CallbackInfo &info);
	~AudioContext();
	
	void _destroy();
	
private:
	
	static Napi::FunctionReference _constructor;
	
	double _baseLatency;
	
	JS_METHOD(destroy);
	
	JS_METHOD(suspend);
	JS_METHOD(close);
	JS_METHOD(getOutputTimestamp);
	JS_GETTER(baseLatencyGetter);
	
};


#endif // _AUDIO_CONTEXT_HPP_
