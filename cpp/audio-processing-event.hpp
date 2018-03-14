#ifndef _AUDIO_PROCESSING_EVENT_HPP_
#define _AUDIO_PROCESSING_EVENT_HPP_


#include <addon-tools.hpp>


class AudioProcessingEvent : public Nan::ObjectWrap {
	
// Public V8 init
public:
	
	static void init(v8::Local<v8::Object> target);
	
	
// Public C++ methods: in-engine calls
public:
	
	
// Protected C++ methods: implementing JS calls
protected:
	
	AudioProcessingEvent();
	virtual ~AudioProcessingEvent();
	
	
// JS methods and props
protected:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	
	
	
	
	static NAN_GETTER(isDestroyedGetter);
	
	
	static NAN_GETTER(playbackTimeGetter);
	

	static NAN_GETTER(inputBufferGetter);
	

	static NAN_GETTER(outputBufferGetter);
	
	
// Actual destruction-handler
private:
	
	void _destroy();
	
	
// Stored JS constructor and helpers
private:
	
	static Nan::Persistent<v8::Function> _constructor;
	
	
// This-state storage
private:
	
	bool _isDestroyed;
	
	double _playbackTime;
	Nan::Persistent<v8::Object> _inputBuffer;
	Nan::Persistent<v8::Object> _outputBuffer;
	
};


#endif // _AUDIO_PROCESSING_EVENT_HPP_
