#ifndef _AUDIO_WORKLET_GLOBAL_SCOPE_HPP_
#define _AUDIO_WORKLET_GLOBAL_SCOPE_HPP_


#include <addon-tools.hpp>


class AudioWorkletGlobalScope : public Nan::ObjectWrap {
	
// Public V8 init
public:
	
	static void init(v8::Local<v8::Object> target);
	
	
// Public C++ methods: in-engine calls
public:
	
	
// Protected C++ methods: implementing JS calls
protected:
	
	AudioWorkletGlobalScope();
	virtual ~AudioWorkletGlobalScope();
	
	
// JS methods and props
protected:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	
	static NAN_METHOD(registerProcessor);
	
	
	static NAN_GETTER(isDestroyedGetter);
	
	
	static NAN_GETTER(currentFrameGetter);
	

	static NAN_GETTER(currentTimeGetter);
	

	static NAN_GETTER(sampleRateGetter);
	
	
// Actual destruction-handler
private:
	
	void _destroy();
	
	
// Stored JS constructor and helpers
private:
	
	static Nan::Persistent<v8::Function> _constructor;
	
	
// This-state storage
private:
	
	bool _isDestroyed;
	
	size_t _currentFrame;
	double _currentTime;
	float _sampleRate;
	
};


#endif // _AUDIO_WORKLET_GLOBAL_SCOPE_HPP_
