#ifndef _AUDIO_WORKLET_PROCESSOR_HPP_
#define _AUDIO_WORKLET_PROCESSOR_HPP_


#include <addon-tools.hpp>


class AudioWorkletProcessor : public Napi::ObjectWrap<AudioWorkletProcessor> {
	
public:
	
	~AudioWorkletProcessor();
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isAudioWorkletProcessor(Napi::Object obj);
	
	// Make a new instance from C++ land
	explicit AudioWorkletProcessor(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	AudioWorkletProcessor();
	
	static Napi::FunctionReference _ctorAudioWorkletProcessor;
	
	bool _isDestroyed;
	
	Napi::ObjectReference _port;
	
	
// JS methods and props, available through V8 APIs
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	
	
	JS_GETTER(portGetter);
	
};


#endif // _AUDIO_WORKLET_PROCESSOR_HPP_
