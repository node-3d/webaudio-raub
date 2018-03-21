#ifndef _AUDIO_LISTENER_HPP_
#define _AUDIO_LISTENER_HPP_


#include <addon-tools.hpp>


class AudioListener : public Nan::ObjectWrap {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	void _destroy();
	
	
// Methods and props
protected:
	
	AudioListener();
	virtual ~AudioListener();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoAudioListener; // for inheritance
	static Nan::Persistent<v8::Function> _ctorAudioListener;
	
	
// System methods and props for ObjectWrap
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	static NAN_METHOD(setPosition);
	static NAN_METHOD(setOrientation);
	
	static NAN_GETTER(positionXGetter);
	
	static NAN_GETTER(positionYGetter);
	
	static NAN_GETTER(positionZGetter);
	
	static NAN_GETTER(forwardXGetter);
	
	static NAN_GETTER(forwardYGetter);
	
	static NAN_GETTER(forwardZGetter);
	
	static NAN_GETTER(upXGetter);
	
	static NAN_GETTER(upYGetter);
	
	static NAN_GETTER(upZGetter);
	
	
private:
	
	bool _isDestroyed;
	
	Nan::Persistent<v8::Object> _positionX;
	Nan::Persistent<v8::Object> _positionY;
	Nan::Persistent<v8::Object> _positionZ;
	Nan::Persistent<v8::Object> _forwardX;
	Nan::Persistent<v8::Object> _forwardY;
	Nan::Persistent<v8::Object> _forwardZ;
	Nan::Persistent<v8::Object> _upX;
	Nan::Persistent<v8::Object> _upY;
	Nan::Persistent<v8::Object> _upZ;
	
};


#endif // _AUDIO_LISTENER_HPP_
