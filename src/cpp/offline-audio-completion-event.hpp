#ifndef _OFFLINE_AUDIO_COMPLETION_EVENT_HPP_
#define _OFFLINE_AUDIO_COMPLETION_EVENT_HPP_


#include "common.hpp"


class OfflineAudioCompletionEvent : public CommonNode<OfflineAudioCompletionEvent> {
	
public:
	
	~OfflineAudioCompletionEvent();
	explicit OfflineAudioCompletionEvent(const Napi::CallbackInfo &info);
	
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isOfflineAudioCompletionEvent(Napi::Object obj);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
protected:
	
	OfflineAudioCompletionEvent();
	
	static Napi::FunctionReference _constructor;
	
	bool _isDestroyed;
	
	Napi::ObjectReference _renderedBuffer;
	
	
private:
	
	JS_DECLARE_METHOD(destroy);
	JS_DECLARE_GETTER(isDestroyed);
	
	
	
	JS_DECLARE_GETTER(renderedBuffer);
	
};


#endif // _OFFLINE_AUDIO_COMPLETION_EVENT_HPP_
