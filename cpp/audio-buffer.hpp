#ifndef _AUDIO_BUFFER_HPP_
#define _AUDIO_BUFFER_HPP_


#include <addon-tools.hpp>


class AudioBuffer : public Nan::ObjectWrap {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	// Make a new instance from C++ land
	static v8::Local<v8::Object> getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	AudioBuffer();
	virtual ~AudioBuffer();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoAudioBuffer;
	static Nan::Persistent<v8::Function> _ctorAudioBuffer;
	
	bool _isDestroyed;
	
	int _length;
	double _duration;
	float _sampleRate;
	unsigned int _numberOfChannels;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	static NAN_METHOD(getChannelData);
	static NAN_METHOD(copyFromChannel);
	static NAN_METHOD(copyToChannel);
	
	static NAN_GETTER(lengthGetter);
	
	static NAN_GETTER(durationGetter);
	
	static NAN_GETTER(sampleRateGetter);
	
	static NAN_GETTER(numberOfChannelsGetter);
	
};


#endif // _AUDIO_BUFFER_HPP_
