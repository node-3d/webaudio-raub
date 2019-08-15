#ifndef _OFFLINE_AUDIO_COMPLETION_EVENT_HPP_
#define _OFFLINE_AUDIO_COMPLETION_EVENT_HPP_


#include <addon-tools.hpp>


class OfflineAudioCompletionEvent : public Napi::ObjectWrap<OfflineAudioCompletionEvent> {
	
public:
	
	~OfflineAudioCompletionEvent();
	OfflineAudioCompletionEvent(const Napi::CallbackInfo &info);
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isOfflineAudioCompletionEvent(Napi::Object obj);
	
	// Make a new instance from C++ land
	explicit OfflineAudioCompletionEvent(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
protected:
	
	OfflineAudioCompletionEvent();
	
	static Napi::FunctionReference _ctorOfflineAudioCompletionEvent;
	
	bool _isDestroyed;
	
	Napi::ObjectReference _renderedBuffer;
	
	
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	
	
	JS_GETTER(renderedBufferGetter);
	
};


#endif // _OFFLINE_AUDIO_COMPLETION_EVENT_HPP_
