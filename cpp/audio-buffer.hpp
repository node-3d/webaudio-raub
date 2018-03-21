#ifndef _AUDIO_BUFFER_HPP_
#define _AUDIO_BUFFER_HPP_


#include <addon-tools.hpp>


class AudioBuffer : public Nan::ObjectWrap {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	void _destroy();
	
	
// Methods and props
protected:
	
	AudioBuffer();
	virtual ~AudioBuffer();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoAudioBuffer; // for inheritance
	static Nan::Persistent<v8::Function> _ctorAudioBuffer;
	
	
// System methods and props for ObjectWrap
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
	
	
private:
	
	bool _isDestroyed;
	
	int _length;
	double _duration;
	float _sampleRate;
	unsigned int _numberOfChannels;
	
};


#endif // _AUDIO_BUFFER_HPP_
