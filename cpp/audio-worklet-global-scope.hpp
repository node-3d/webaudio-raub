#ifndef _AUDIO_WORKLET_GLOBAL_SCOPE_HPP_
#define _AUDIO_WORKLET_GLOBAL_SCOPE_HPP_


#include <addon-tools.hpp>


class AudioWorkletGlobalScope : public Nan::ObjectWrap {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	void _destroy();
	
	
// Methods and props
protected:
	
	AudioWorkletGlobalScope();
	virtual ~AudioWorkletGlobalScope();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoAudioWorkletGlobalScope; // for inheritance
	static Nan::Persistent<v8::Function> _ctorAudioWorkletGlobalScope;
	
	
// System methods and props for ObjectWrap
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	static NAN_METHOD(registerProcessor);
	
	static NAN_GETTER(currentFrameGetter);
	
	static NAN_GETTER(currentTimeGetter);
	
	static NAN_GETTER(sampleRateGetter);
	
	
private:
	
	bool _isDestroyed;
	
	size_t _currentFrame;
	double _currentTime;
	float _sampleRate;
	
};


#endif // _AUDIO_WORKLET_GLOBAL_SCOPE_HPP_
