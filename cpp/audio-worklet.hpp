#ifndef _AUDIO_WORKLET_HPP_
#define _AUDIO_WORKLET_HPP_


#include <addon-tools.hpp>


class AudioWorklet : public Nan::ObjectWrap {
	
public:
	
	// Public V8 init
	static void init(V8_VAR_OBJ target);
	
	static bool isAudioWorklet(V8_VAR_OBJ obj);
	
	// Make a new instance from C++ land
	static V8_VAR_OBJ getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	AudioWorklet();
	virtual ~AudioWorklet();
	
	static V8_STORE_FT _protoAudioWorklet;
	static V8_STORE_FUNC _ctorAudioWorklet;
	
	bool _isDestroyed;
	
	
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
};


#endif // _AUDIO_WORKLET_HPP_
