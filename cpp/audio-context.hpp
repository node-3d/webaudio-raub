#ifndef _AUDIO_CONTEXT_HPP_
#define _AUDIO_CONTEXT_HPP_


#include <addon-tools.hpp>

#include "base-audio-context.hpp"


class AudioContext : public BaseAudioContext {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	// Make a new instance from C++ land
	static v8::Local<v8::Object> getNew(v8::Local<v8::Object> context);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props
protected:
	
	AudioContext();
	explicit AudioContext(float sampleRate);
	virtual ~AudioContext();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoAudioContext; // for inheritance
	static Nan::Persistent<v8::Function> _ctorAudioContext;
	
	bool _isDestroyed;
	
	double _baseLatency;
	
	
// System methods and props for ObjectWrap
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	static NAN_METHOD(suspend);
	static NAN_METHOD(close);
	static NAN_METHOD(getOutputTimestamp);
	static NAN_METHOD(createMediaElementSource);
	static NAN_METHOD(createMediaStreamSource);
	static NAN_METHOD(createMediaStreamDestination);
	
	static NAN_GETTER(baseLatencyGetter);
	
};


#endif // _AUDIO_CONTEXT_HPP_
