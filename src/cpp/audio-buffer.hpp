#ifndef _AUDIO_BUFFER_HPP_
#define _AUDIO_BUFFER_HPP_


#include <memory>

#include <addon-tools.hpp>

namespace lab { class AudioBus; };


class AudioBuffer : public Napi::ObjectWrap<AudioBuffer> {
	
public:
	
	typedef std::shared_ptr<lab::AudioBus> BusPtr;
	
	~AudioBuffer();
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	// Make a new instance from C++ land
	explicit AudioBuffer(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	BusPtr getBus() const;
	
	
// Methods and props, available for children
protected:
	
	AudioBuffer();
	explicit AudioBuffer(BusPtr bus);
	
	static Napi::FunctionReference _ctorAudioBuffer;
	
	bool _isDestroyed;
	
	int _length;
	double _duration;
	float _sampleRate;
	unsigned int _numberOfChannels;
	
	BusPtr _impl;
	
	
// JS methods and props, available through V8 APIs
private:
	
	JS_METHOD(newCtor);
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	JS_METHOD(getChannelData);
	JS_METHOD(copyFromChannel);
	JS_METHOD(copyToChannel);
	
	JS_GETTER(lengthGetter);
	
	JS_GETTER(durationGetter);
	
	JS_GETTER(sampleRateGetter);
	
	JS_GETTER(numberOfChannelsGetter);
	
};


#endif // _AUDIO_BUFFER_HPP_
