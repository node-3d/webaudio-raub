#ifndef _AUDIO_PARAM_HPP_
#define _AUDIO_PARAM_HPP_


#include <addon-tools.hpp>


class AudioParam : public Nan::ObjectWrap {
	
// Public V8 init
public:
	
	static void init(v8::Local<v8::Object> target);
	
	
// Public C++ methods: in-engine calls
public:
	
	
// Protected C++ methods: implementing JS calls
protected:
	
	AudioParam();
	virtual ~AudioParam();
	
	
// JS methods and props
protected:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	
	static NAN_METHOD(setValueAtTime);
	static NAN_METHOD(linearRampToValueAtTime);
	static NAN_METHOD(exponentialRampToValueAtTime);
	static NAN_METHOD(setTargetAtTime);
	static NAN_METHOD(setValueCurveAtTime);
	static NAN_METHOD(cancelScheduledValues);
	static NAN_METHOD(cancelAndHoldAtTime);
	
	
	static NAN_GETTER(isDestroyedGetter);
	
	
	static NAN_GETTER(valueGetter);
	static NAN_SETTER(valueSetter);
	

	static NAN_GETTER(defaultValueGetter);
	

	static NAN_GETTER(minValueGetter);
	

	static NAN_GETTER(maxValueGetter);
	
	
// Actual destruction-handler
private:
	
	void _destroy();
	
	
// Stored JS constructor and helpers
private:
	
	static Nan::Persistent<v8::Function> _constructor;
	
	
// This-state storage
private:
	
	bool _isDestroyed;
	
	float _value;
	float _defaultValue;
	float _minValue;
	float _maxValue;
	
};


#endif // _AUDIO_PARAM_HPP_
