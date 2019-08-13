#ifndef _AUDIO_WORKLET_GLOBAL_SCOPE_HPP_
#define _AUDIO_WORKLET_GLOBAL_SCOPE_HPP_


#include <addon-tools.hpp>


class AudioWorkletGlobalScope : public Nan::ObjectWrap {
	
public:
	
	~AudioWorkletGlobalScope();
	
	// Public V8 init
	static void init(V8_VAR_OBJ target);
	
	static bool isAudioWorkletGlobalScope(V8_VAR_OBJ obj);
	
	// Make a new instance from C++ land
	static V8_VAR_OBJ getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	AudioWorkletGlobalScope();
	
	static V8_STORE_FT _protoAudioWorkletGlobalScope;
	static V8_STORE_FUNC _ctorAudioWorkletGlobalScope;
	
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
