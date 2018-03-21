#ifndef _AUDIO_WORKLET_PROCESSOR_HPP_
#define _AUDIO_WORKLET_PROCESSOR_HPP_


#include <addon-tools.hpp>


class AudioWorkletProcessor : public Nan::ObjectWrap {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	void _destroy();
	
	
// Methods and props
protected:
	
	AudioWorkletProcessor();
	virtual ~AudioWorkletProcessor();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoAudioWorkletProcessor; // for inheritance
	static Nan::Persistent<v8::Function> _ctorAudioWorkletProcessor;
	
	
// System methods and props for ObjectWrap
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	static NAN_GETTER(portGetter);
	
	
private:
	
	bool _isDestroyed;
	
	Nan::Persistent<v8::Object> _port;
	
};


#endif // _AUDIO_WORKLET_PROCESSOR_HPP_
