#ifndef _AUDIO_BUFFER_HPP_
#define _AUDIO_BUFFER_HPP_

#include "common.hpp"


class AudioBuffer : public CommonBus {
DECLARE_ES5_CLASS(AudioBuffer, AudioBuffer);
	
public:
	
	static void init(Napi::Env env, Napi::Object exports);
	static Napi::Object create(Napi::Env env, Napi::Object context, BusPtr bus);
	
	explicit AudioBuffer(const Napi::CallbackInfo &info);
	~AudioBuffer();
	
	void _destroy();
	
private:
	
	int _length;
	double _duration;
	float _sampleRate;
	uint32_t _numberOfChannels;
	
	JS_DECLARE_METHOD(AudioBuffer, destroy);
	
	JS_DECLARE_METHOD(AudioBuffer, getChannelData);
	JS_DECLARE_METHOD(AudioBuffer, copyFromChannel);
	JS_DECLARE_METHOD(AudioBuffer, copyToChannel);
	
	JS_DECLARE_GETTER(AudioBuffer, length);
	
	JS_DECLARE_GETTER(AudioBuffer, duration);
	
	JS_DECLARE_GETTER(AudioBuffer, sampleRate);
	
	JS_DECLARE_GETTER(AudioBuffer, numberOfChannels);
	
};


#endif // _AUDIO_BUFFER_HPP_
