#ifndef _AUDIO_BUFFER_HPP_
#define _AUDIO_BUFFER_HPP_

#include "common.hpp"


class AudioBuffer : public CommonBus<AudioBuffer> {
	
public:
	
	static void init(Napi::Env env, Napi::Object exports);
	static Napi::Object create(Napi::Env env, Napi::Object context, BusPtr bus);
	
	explicit AudioBuffer(const Napi::CallbackInfo &info);
	~AudioBuffer();
	
	void _destroy();
	
private:
	
	static Napi::FunctionReference _constructor;
	
	int _length;
	double _duration;
	float _sampleRate;
	uint32_t _numberOfChannels;
	
	JS_DECLARE_METHOD(destroy);
	
	JS_DECLARE_METHOD(getChannelData);
	JS_DECLARE_METHOD(copyFromChannel);
	JS_DECLARE_METHOD(copyToChannel);
	
	JS_DECLARE_GETTER(length);
	
	JS_DECLARE_GETTER(duration);
	
	JS_DECLARE_GETTER(sampleRate);
	
	JS_DECLARE_GETTER(numberOfChannels);
	
};


#endif // _AUDIO_BUFFER_HPP_
