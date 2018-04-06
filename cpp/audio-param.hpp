#ifndef _AUDIO_PARAM_HPP_
#define _AUDIO_PARAM_HPP_


#include <memory>

#include <addon-tools.hpp>

namespace lab { class AudioParam; };


class AudioParam : public Nan::ObjectWrap {
	
public:
	
	typedef std::shared_ptr<lab::AudioParam> ParamPtr;
	
	// Public V8 init
	static void init(V8_VAR_OBJ target);
	
	// Make a new instance from C++ land
	static V8_VAR_OBJ getNew(V8_VAR_OBJ context, ParamPtr param);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	ParamPtr getParam() const;
	
	static bool isAudioParam(V8_VAR_OBJ obj);
	
	
// Methods and props, available for children
protected:
	
	AudioParam(V8_VAR_OBJ context, ParamPtr param);
	virtual ~AudioParam();
	
	static V8_STORE_FT _protoAudioParam;
	static V8_STORE_FUNC _ctorAudioParam;
	
	bool _isDestroyed;
	
	ParamPtr _impl;
	V8_STORE_OBJ _context;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	static NAN_METHOD(setValueAtTime);
	static NAN_METHOD(linearRampToValueAtTime);
	static NAN_METHOD(exponentialRampToValueAtTime);
	static NAN_METHOD(setTargetAtTime);
	static NAN_METHOD(setValueCurveAtTime);
	static NAN_METHOD(cancelScheduledValues);
	static NAN_METHOD(cancelAndHoldAtTime);
	
	static NAN_GETTER(valueGetter);
	static NAN_SETTER(valueSetter);
	
	static NAN_GETTER(defaultValueGetter);
	
	static NAN_GETTER(minValueGetter);
	
	static NAN_GETTER(maxValueGetter);
	
};


#endif // _AUDIO_PARAM_HPP_
