#ifndef _AUDIO_PANNER_PARAM_HPP_
#define _AUDIO_PANNER_PARAM_HPP_


#include "audio-param.hpp"

class LabAudioPannerParam;


class AudioPannerParam : public AudioParam {
	
public:
	
	typedef std::shared_ptr<LabAudioPannerParam> ParamPtr;
	
	// Public V8 init
	static void init(V8_VAR_OBJ target);
	
	// Make a new instance from C++ land
	static V8_VAR_OBJ getNew(V8_VAR_OBJ context, ParamPtr param);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	ParamPtr getParam() const;
	
	static bool isAudioPannerParam(V8_VAR_OBJ obj);
	
	
protected:
	
	AudioPannerParam(V8_VAR_OBJ context, ParamPtr param);
	
	static V8_STORE_FT _protoAudioPannerParam;
	static V8_STORE_FUNC _ctorAudioPannerParam;
	
	bool _isDestroyed;
	
	
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	static NAN_GETTER(valueGetter);
	static NAN_SETTER(valueSetter);
	
	static NAN_METHOD(setValueAtTime);
	static NAN_METHOD(setTargetAtTime);
	
};


#endif // _AUDIO_PANNER_PARAM_HPP_
