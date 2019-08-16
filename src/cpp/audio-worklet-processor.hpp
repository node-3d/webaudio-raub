#ifndef _AUDIO_WORKLET_PROCESSOR_HPP_
#define _AUDIO_WORKLET_PROCESSOR_HPP_


#include <addon-tools.hpp>


class AudioWorkletProcessor : public Napi::ObjectWrap<AudioWorkletProcessor> {
	
public:
	
	~AudioWorkletProcessor();
	AudioWorkletProcessor(const Napi::CallbackInfo &info);
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isAudioWorkletProcessor(Napi::Object obj);
	
	// Make a new instance from C++ land
	explicit AudioWorkletProcessor(const Napi::CallbackInfo& info);
	
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
