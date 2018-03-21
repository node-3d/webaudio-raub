#ifndef _OFFLINE_AUDIO_COMPLETION_EVENT_HPP_
#define _OFFLINE_AUDIO_COMPLETION_EVENT_HPP_


#include <addon-tools.hpp>


class OfflineAudioCompletionEvent : public Nan::ObjectWrap {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	void _destroy();
	
	
// Methods and props
protected:
	
	OfflineAudioCompletionEvent();
	virtual ~OfflineAudioCompletionEvent();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoOfflineAudioCompletionEvent; // for inheritance
	static Nan::Persistent<v8::Function> _ctorOfflineAudioCompletionEvent;
	
	
// System methods and props for ObjectWrap
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	static NAN_GETTER(renderedBufferGetter);
	
	
private:
	
	bool _isDestroyed;
	
	Nan::Persistent<v8::Object> _renderedBuffer;
	
};


#endif // _OFFLINE_AUDIO_COMPLETION_EVENT_HPP_
