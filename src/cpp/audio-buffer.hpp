#ifndef _AUDIO_BUFFER_HPP_
#define _AUDIO_BUFFER_HPP_


#include <memory>

#include "common.hpp"

namespace lab { class AudioBus; };


class AudioBuffer : public Napi::ObjectWrap<AudioBuffer>, private CommonNode {
	
public:
	
	typedef std::shared_ptr<lab::AudioBus> BusPtr;
	
	~AudioBuffer();
	explicit AudioBuffer(const Napi::CallbackInfo &info);
	
	static void init(Napi::Env env, Napi::Object exports);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	BusPtr getBus() const;
	
	
protected:
	
	AudioBuffer();
	explicit AudioBuffer(BusPtr bus);
	
	int _length;
	double _duration;
	float _sampleRate;
	uint32_t _numberOfChannels;
	
	BusPtr _impl;
	
	
private:
	
	JS_METHOD(getChannelData);
	JS_METHOD(copyFromChannel);
	JS_METHOD(copyToChannel);
	
	JS_GETTER(lengthGetter);
	
	JS_GETTER(durationGetter);
	
	JS_GETTER(sampleRateGetter);
	
	JS_GETTER(numberOfChannelsGetter);
	
};


#endif // _AUDIO_BUFFER_HPP_
