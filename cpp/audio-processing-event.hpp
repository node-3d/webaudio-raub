#ifndef _AUDIO_PROCESSING_EVENT_HPP_
#define _AUDIO_PROCESSING_EVENT_HPP_


#include <addon-tools.hpp>


class AudioProcessingEvent : public Nan::ObjectWrap {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	// Make a new instance from C++ land
	static v8::Local<v8::Object> getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	AudioProcessingEvent();
	virtual ~AudioProcessingEvent();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoAudioProcessingEvent;
	static Nan::Persistent<v8::Function> _ctorAudioProcessingEvent;
	
	bool _isDestroyed;
	
	double _playbackTime;
	Nan::Persistent<v8::Object> _inputBuffer;
	Nan::Persistent<v8::Object> _outputBuffer;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	static NAN_GETTER(playbackTimeGetter);
	
	static NAN_GETTER(inputBufferGetter);
	
	static NAN_GETTER(outputBufferGetter);
	
};


#endif // _AUDIO_PROCESSING_EVENT_HPP_
