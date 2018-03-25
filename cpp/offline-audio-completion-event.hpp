#ifndef _OFFLINE_AUDIO_COMPLETION_EVENT_HPP_
#define _OFFLINE_AUDIO_COMPLETION_EVENT_HPP_


#include <addon-tools.hpp>


class OfflineAudioCompletionEvent : public Nan::ObjectWrap {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	// Make a new instance from C++ land
	static v8::Local<v8::Object> getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	OfflineAudioCompletionEvent();
	virtual ~OfflineAudioCompletionEvent();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoOfflineAudioCompletionEvent;
	static Nan::Persistent<v8::Function> _ctorOfflineAudioCompletionEvent;
	
	bool _isDestroyed;
	
	Nan::Persistent<v8::Object> _renderedBuffer;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	static NAN_GETTER(renderedBufferGetter);
	
};


#endif // _OFFLINE_AUDIO_COMPLETION_EVENT_HPP_
