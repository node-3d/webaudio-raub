#ifndef _AUDIO_PROCESSING_EVENT_HPP_
#define _AUDIO_PROCESSING_EVENT_HPP_


#include <addon-tools.hpp>


class AudioProcessingEvent : public Napi::ObjectWrap<AudioProcessingEvent> {
	
public:
	
	~AudioProcessingEvent();
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isAudioProcessingEvent(Napi::Object obj);
	
	// Make a new instance from C++ land
	explicit AudioProcessingEvent(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	AudioProcessingEvent();
	
	static Napi::FunctionReference _ctorAudioProcessingEvent;
	
	bool _isDestroyed;
	
	double _playbackTime;
	Napi::ObjectReference _inputBuffer;
	Napi::ObjectReference _outputBuffer;
	
	
// JS methods and props, available through V8 APIs
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	
	
	JS_GETTER(playbackTimeGetter);
	
	JS_GETTER(inputBufferGetter);
	
	JS_GETTER(outputBufferGetter);
	
};


#endif // _AUDIO_PROCESSING_EVENT_HPP_
