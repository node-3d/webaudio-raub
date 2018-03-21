#ifndef _AUDIO_WORKLET_HPP_
#define _AUDIO_WORKLET_HPP_


#include <addon-tools.hpp>


class AudioWorklet : public Nan::ObjectWrap {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	void _destroy();
	
	
// Methods and props
protected:
	
	AudioWorklet();
	virtual ~AudioWorklet();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoAudioWorklet; // for inheritance
	static Nan::Persistent<v8::Function> _ctorAudioWorklet;
	
	
// System methods and props for ObjectWrap
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	
private:
	
	bool _isDestroyed;
	
	
	
};


#endif // _AUDIO_WORKLET_HPP_
