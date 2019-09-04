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
	
	JS_DECLARE_METHOD(destroy);
	
	// JS_METHOD(connect);
	// JS_METHOD(disconnect);
	
	// JS_GETTER(context);
	
	JS_DECLARE_METHOD(setValueAtTime);
	JS_DECLARE_METHOD(linearRampToValueAtTime);
	JS_DECLARE_METHOD(exponentialRampToValueAtTime);
	JS_DECLARE_METHOD(setTargetAtTime);
	JS_DECLARE_METHOD(setValueCurveAtTime);
	JS_DECLARE_METHOD(cancelScheduledValues);
	JS_DECLARE_METHOD(cancelAndHoldAtTime);
	
	JS_DECLARE_GETTER(value);
	JS_DECLARE_SETTER(value);
	
	JS_DECLARE_GETTER(defaultValue);
	
	JS_DECLARE_GETTER(minValue);
	
	JS_DECLARE_GETTER(maxValue);
	
};


#endif // _AUDIO_PARAM_HPP_
