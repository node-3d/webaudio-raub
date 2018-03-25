#ifndef _AUDIO_WORKLET_GLOBAL_SCOPE_HPP_
#define _AUDIO_WORKLET_GLOBAL_SCOPE_HPP_


#include <addon-tools.hpp>


class AudioWorkletGlobalScope : public Nan::ObjectWrap {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	// Make a new instance from C++ land
	static v8::Local<v8::Object> getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	AudioWorkletGlobalScope();
	virtual ~AudioWorkletGlobalScope();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoAudioWorkletGlobalScope;
	static Nan::Persistent<v8::Function> _ctorAudioWorkletGlobalScope;
	
	bool _isDestroyed;
	
	size_t _currentFrame;
	double _currentTime;
	float _sampleRate;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	static NAN_METHOD(registerProcessor);
	
	static NAN_GETTER(currentFrameGetter);
	
	static NAN_GETTER(currentTimeGetter);
	
	static NAN_GETTER(sampleRateGetter);
	
};


#endif // _AUDIO_WORKLET_GLOBAL_SCOPE_HPP_
