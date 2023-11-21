#ifndef _AUDIO_CONTEXT_HPP_
#define _AUDIO_CONTEXT_HPP_

#include "common.hpp"


class AudioContext : public CommonCtx {
DECLARE_ES5_CLASS(AudioContext, AudioContext);
public:
	static void init(Napi::Env env, Napi::Object exports);
	
	explicit AudioContext(const Napi::CallbackInfo &info);
	~AudioContext();
	
	void _destroy();
	
private:
	double _baseLatency;
	
	JS_DECLARE_METHOD(AudioContext, destroy);
	JS_DECLARE_METHOD(AudioContext, suspend);
	JS_DECLARE_METHOD(AudioContext, close);
	JS_DECLARE_METHOD(AudioContext, getOutputTimestamp);
	JS_DECLARE_GETTER(AudioContext, baseLatency);
};


#endif // _AUDIO_CONTEXT_HPP_
