#ifndef _AUDIO_WORKLET_PROCESSOR_HPP_
#define _AUDIO_WORKLET_PROCESSOR_HPP_


#include "common.hpp"


class AudioWorkletProcessor : public Napi::ObjectWrap<AudioWorkletProcessor>, private CommonNode {
	
public:
	
	~AudioWorkletProcessor();
	explicit AudioWorkletProcessor(const Napi::CallbackInfo &info);
	
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isAudioWorkletProcessor(Napi::Object obj);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
protected:
	
	AudioWorkletProcessor();
	
	static Napi::FunctionReference _constructor;
	
	bool _isDestroyed;
	
	Napi::ObjectReference _port;
	
	
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	
	
	JS_GETTER(portGetter);
	
};


#endif // _AUDIO_WORKLET_PROCESSOR_HPP_
