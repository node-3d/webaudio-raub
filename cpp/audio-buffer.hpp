#ifndef _AUDIO_BUFFER_HPP_
#define _AUDIO_BUFFER_HPP_


#include <addon-tools.hpp>


class AudioBuffer : public Nan::ObjectWrap {
	
// Public V8 init
public:
	
	static void init(v8::Local<v8::Object> target);
	
	
// Public C++ methods: in-engine calls
public:
	
	
// Protected C++ methods: implementing JS calls
protected:
	
	AudioBuffer();
	virtual ~AudioBuffer();
	
	
// JS methods and props
protected:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	
	static NAN_METHOD(getChannelData);
	static NAN_METHOD(copyFromChannel);
	static NAN_METHOD(copyToChannel);
	
	
	static NAN_GETTER(isDestroyedGetter);
	
	
	static NAN_GETTER(lengthGetter);
	

	static NAN_GETTER(durationGetter);
	

	static NAN_GETTER(sampleRateGetter);
	

	static NAN_GETTER(numberOfChannelsGetter);
	
	
// Actual destruction-handler
private:
	
	void _destroy();
	
	
// Stored JS constructor and helpers
private:
	
	static Nan::Persistent<v8::Function> _constructor;
	
	
// This-state storage
private:
	
	bool _isDestroyed;
	
	int _length;
	double _duration;
	float _sampleRate;
	unsigned int _numberOfChannels;
	
};


#endif // _AUDIO_BUFFER_HPP_
