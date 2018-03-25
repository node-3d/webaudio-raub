#ifndef _AUDIO_PARAM_HPP_
#define _AUDIO_PARAM_HPP_


#include <memory>

#include <addon-tools.hpp>

namespace lab { class AudioParam; };


class AudioParam : public Nan::ObjectWrap {
	
	typedef std::shared_ptr<lab::AudioParam> ParamPtr;
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	// Make a new instance from C++ land
	static v8::Local<v8::Object> getNew(v8::Local<v8::Object> context, ParamPtr param);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	explicit AudioParam(v8::Local<v8::Object> context, ParamPtr param);
	virtual ~AudioParam();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoAudioParam;
	static Nan::Persistent<v8::Function> _ctorAudioParam;
	
	bool _isDestroyed;
	
	float _value;
	float _defaultValue;
	float _minValue;
	float _maxValue;
	
	ParamPtr _impl;
	Nan::Persistent<v8::Object> _context;
	
	
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
