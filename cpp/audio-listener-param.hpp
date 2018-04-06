#ifndef _AUDIO_LISTENER_PARAM_HPP_
#define _AUDIO_LISTENER_PARAM_HPP_


#include "audio-param.hpp"

class LabAudioListenerParam;


class AudioListenerParam : public AudioParam {
	
public:
	
	typedef std::shared_ptr<LabAudioListenerParam> ParamPtr;
	
	// Public V8 init
	static void init(V8_VAR_OBJ target);
	
	// Make a new instance from C++ land
	static V8_VAR_OBJ getNew(V8_VAR_OBJ context, ParamPtr param);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	ParamPtr getParam() const;
	
	static bool isAudioListenerParam(V8_VAR_OBJ obj);
	
	
protected:
	
	AudioListenerParam(V8_VAR_OBJ context, ParamPtr param);
	
	static V8_STORE_FT _protoAudioListenerParam;
	static V8_STORE_FUNC _ctorAudioListenerParam;
	
	bool _isDestroyed;
	
	
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	static NAN_GETTER(valueGetter);
	static NAN_SETTER(valueSetter);
	
};


#endif // _AUDIO_LISTENER_PARAM_HPP_
