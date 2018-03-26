#ifndef _OFFLINE_AUDIO_COMPLETION_EVENT_HPP_
#define _OFFLINE_AUDIO_COMPLETION_EVENT_HPP_


#include <addon-tools.hpp>


class OfflineAudioCompletionEvent : public Nan::ObjectWrap {
	
public:
	
	// Public V8 init
	static void init(V8_VAR_OBJ target);
	
	// Make a new instance from C++ land
	static V8_VAR_OBJ getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	OfflineAudioCompletionEvent();
	virtual ~OfflineAudioCompletionEvent();
	
	static V8_STORE_FT _protoOfflineAudioCompletionEvent;
	static V8_STORE_FUNC _ctorOfflineAudioCompletionEvent;
	
	bool _isDestroyed;
	
	V8_STORE_OBJ _renderedBuffer;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	static NAN_GETTER(renderedBufferGetter);
	
};


#endif // _OFFLINE_AUDIO_COMPLETION_EVENT_HPP_
