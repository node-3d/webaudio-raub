#ifndef _AUDIO_LISTENER_HPP_
#define _AUDIO_LISTENER_HPP_


#include <addon-tools.hpp>

namespace lab { class AudioListener; };


class AudioListener : public Nan::ObjectWrap {
	
public:
	
	typedef std::shared_ptr<lab::AudioListener> ListenerPtr;
	
	~AudioListener();
	
	// Public V8 init
	static void init(V8_VAR_OBJ target);
	
	static bool isAudioListener(V8_VAR_OBJ obj);
	
	// Make a new instance from C++ land
	static V8_VAR_OBJ getNew(V8_VAR_OBJ context, ListenerPtr listener);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	explicit AudioListener(V8_VAR_OBJ context, ListenerPtr listener);
	
	static V8_STORE_FT _protoAudioListener;
	static V8_STORE_FUNC _ctorAudioListener;
	
	bool _isDestroyed;
	
	V8_STORE_OBJ _positionX;
	V8_STORE_OBJ _positionY;
	V8_STORE_OBJ _positionZ;
	V8_STORE_OBJ _forwardX;
	V8_STORE_OBJ _forwardY;
	V8_STORE_OBJ _forwardZ;
	V8_STORE_OBJ _upX;
	V8_STORE_OBJ _upY;
	V8_STORE_OBJ _upZ;
	
	ListenerPtr _impl;
	V8_STORE_OBJ _context;
	
	
// JS methods and props, available through V8 APIs
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
	
};


#endif // _AUDIO_LISTENER_HPP_
