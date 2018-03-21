#ifndef _AUDIO_PROCESSING_EVENT_HPP_
#define _AUDIO_PROCESSING_EVENT_HPP_


#include <addon-tools.hpp>


class AudioProcessingEvent : public Nan::ObjectWrap {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	void _destroy();
	
	
// Methods and props
protected:
	
	AudioProcessingEvent();
	virtual ~AudioProcessingEvent();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoAudioProcessingEvent; // for inheritance
	static Nan::Persistent<v8::Function> _ctorAudioProcessingEvent;
	
	
// System methods and props for ObjectWrap
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	static NAN_GETTER(playbackTimeGetter);
	
	static NAN_GETTER(inputBufferGetter);
	
	static NAN_GETTER(outputBufferGetter);
	
	
private:
	
	bool _isDestroyed;
	
	double _playbackTime;
	Nan::Persistent<v8::Object> _inputBuffer;
	Nan::Persistent<v8::Object> _outputBuffer;
	
};


#endif // _AUDIO_PROCESSING_EVENT_HPP_
