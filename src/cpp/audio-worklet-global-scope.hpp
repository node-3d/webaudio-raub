#ifndef _AUDIO_WORKLET_GLOBAL_SCOPE_HPP_
#define _AUDIO_WORKLET_GLOBAL_SCOPE_HPP_


#include <addon-tools.hpp>


class AudioWorkletGlobalScope : public Napi::ObjectWrap<AudioWorkletGlobalScope> {
	
public:
	
	~AudioWorkletGlobalScope();
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isAudioWorkletGlobalScope(Napi::Object obj);
	
	// Make a new instance from C++ land
	explicit AudioWorkletGlobalScope(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	AudioWorkletGlobalScope();
	
	static Napi::FunctionReference _ctorAudioWorkletGlobalScope;
	
	bool _isDestroyed;
	
	size_t _currentFrame;
	double _currentTime;
	float _sampleRate;
	
	
// JS methods and props, available through V8 APIs
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	JS_METHOD(registerProcessor);
	
	JS_GETTER(currentFrameGetter);
	
	JS_GETTER(currentTimeGetter);
	
	JS_GETTER(sampleRateGetter);
	
};


#endif // _AUDIO_WORKLET_GLOBAL_SCOPE_HPP_
