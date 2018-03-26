#ifndef _AUDIO_WORKLET_NODE_HPP_
#define _AUDIO_WORKLET_NODE_HPP_


#include <addon-tools.hpp>


class AudioWorkletNode : public Nan::ObjectWrap {
	
public:
	
	// Public V8 init
	static void init(V8_VAR_OBJ target);
	
	// Make a new instance from C++ land
	static V8_VAR_OBJ getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	AudioWorkletNode();
	virtual ~AudioWorkletNode();
	
	static V8_STORE_FT _protoAudioWorkletNode;
	static V8_STORE_FUNC _ctorAudioWorkletNode;
	
	bool _isDestroyed;
	
	V8_STORE_OBJ _parameters;
	V8_STORE_OBJ _port;
	V8_STORE_FUNC _onprocessorerror;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	static NAN_GETTER(parametersGetter);
	
	static NAN_GETTER(portGetter);
	
	static NAN_GETTER(onprocessorerrorGetter);
	static NAN_SETTER(onprocessorerrorSetter);
	
};


#endif // _AUDIO_WORKLET_NODE_HPP_
