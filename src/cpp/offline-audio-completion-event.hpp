#ifndef _OFFLINE_AUDIO_COMPLETION_EVENT_HPP_
#define _OFFLINE_AUDIO_COMPLETION_EVENT_HPP_


#include <addon-tools.hpp>


class OfflineAudioCompletionEvent : public Napi::ObjectWrap<OfflineAudioCompletionEvent> {
	
public:
	
	~OfflineAudioCompletionEvent();
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isOfflineAudioCompletionEvent(Napi::Object obj);
	
	// Make a new instance from C++ land
	explicit OfflineAudioCompletionEvent(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	OfflineAudioCompletionEvent();
	
	static Napi::FunctionReference _ctorOfflineAudioCompletionEvent;
	
	bool _isDestroyed;
	
	Napi::ObjectReference _renderedBuffer;
	
	
// JS methods and props, available through V8 APIs
private:
	
	JS_METHOD(newCtor);
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	
	
	JS_GETTER(renderedBufferGetter);
	
};


#endif // _OFFLINE_AUDIO_COMPLETION_EVENT_HPP_
