#ifndef _AUDIO_WORKLET_HPP_
#define _AUDIO_WORKLET_HPP_


#include <addon-tools.hpp>


class AudioWorklet : public Nan::ObjectWrap {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	// Make a new instance from C++ land
	static v8::Local<v8::Object> getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	AudioWorklet();
	virtual ~AudioWorklet();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoAudioWorklet;
	static Nan::Persistent<v8::Function> _ctorAudioWorklet;
	
	bool _isDestroyed;
	
	
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
};


#endif // _AUDIO_WORKLET_HPP_
