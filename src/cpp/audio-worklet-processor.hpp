#ifndef _AUDIO_WORKLET_PROCESSOR_HPP_
#define _AUDIO_WORKLET_PROCESSOR_HPP_


#include <addon-tools.hpp>


class AudioWorkletProcessor : public Nan::ObjectWrap {
	
public:
	
	~AudioWorkletProcessor();
	
	// Public V8 init
	static void init(Napi::Object target);
	
	static bool isAudioWorkletProcessor(Napi::Object obj);
	
	// Make a new instance from C++ land
	static Napi::Object getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	AudioWorkletProcessor();
	
	static V8_STORE_FT _protoAudioWorkletProcessor;
	static V8_STORE_FUNC _ctorAudioWorkletProcessor;
	
	bool _isDestroyed;
	
	V8_STORE_OBJ _port;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	static NAN_GETTER(portGetter);
	
};


#endif // _AUDIO_WORKLET_PROCESSOR_HPP_
