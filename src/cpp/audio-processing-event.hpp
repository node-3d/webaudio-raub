#ifndef _AUDIO_PROCESSING_EVENT_HPP_
#define _AUDIO_PROCESSING_EVENT_HPP_


#include <addon-tools.hpp>


class AudioProcessingEvent : public Nan::ObjectWrap {
	
public:
	
	~AudioProcessingEvent();
	
	// Public V8 init
	static void init(Napi::Object target);
	
	static bool isAudioProcessingEvent(Napi::Object obj);
	
	// Make a new instance from C++ land
	static Napi::Object getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	AudioProcessingEvent();
	
	static V8_STORE_FT _protoAudioProcessingEvent;
	static V8_STORE_FUNC _ctorAudioProcessingEvent;
	
	bool _isDestroyed;
	
	double _playbackTime;
	V8_STORE_OBJ _inputBuffer;
	V8_STORE_OBJ _outputBuffer;
	
	
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
