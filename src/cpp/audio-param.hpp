#ifndef _AUDIO_PARAM_HPP_
#define _AUDIO_PARAM_HPP_

#include "common.hpp"


class AudioParam : public CommonParam<AudioParam> {
	
public:
	
	static void init(Napi::Env env, Napi::Object exports);
	static Napi::Object create(Napi::Env env, Napi::Object context, ParamPtr param);
	static bool isAudioParam(Napi::Object obj);
	
	explicit AudioParam(const Napi::CallbackInfo &info);
	~AudioParam();
	
	void _destroy();
	
private:
	
	static Napi::FunctionReference _constructor;
	
	JS_METHOD(setValueAtTime);
	JS_METHOD(linearRampToValueAtTime);
	JS_METHOD(exponentialRampToValueAtTime);
	JS_METHOD(setTargetAtTime);
	JS_METHOD(setValueCurveAtTime);
	JS_METHOD(cancelScheduledValues);
	JS_METHOD(cancelAndHoldAtTime);
	
	JS_GETTER(valueGetter);
	JS_SETTER(valueSetter);
	
	JS_GETTER(defaultValueGetter);
	
	JS_GETTER(minValueGetter);
	
	JS_GETTER(maxValueGetter);
	
};


#endif // _AUDIO_PARAM_HPP_
