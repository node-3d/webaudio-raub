#include <LabSound/core/AudioContext.h>
#include <LabSound/core/AudioParam.h>
#include <LabSound/extended/AudioContextLock.h>

#include "audio-param.hpp"
#include "audio-context.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

AudioParam::AudioParam(Napi::Object context, ParamPtr param) {
	
	_impl = param;
	_context.Reset(context);
	
	_isDestroyed = false;
	
}


AudioParam::~AudioParam() {
	
	_destroy();
	
}


AudioParam::ParamPtr AudioParam::getParam() const {
	return _impl;
}


void AudioParam::_destroy() { DES_CHECK;
	
	_context.Reset();
	
	_isDestroyed = true;
	
}


// ------ Methods and props


JS_METHOD(AudioParam::setValueAtTime) { THIS_CHECK;
	
	REQ_FLOAT_ARG(0, value);
	REQ_FLOAT_ARG(1, time);
	
	_impl->setValueAtTime(value, time);
	
}


JS_METHOD(AudioParam::linearRampToValueAtTime) { THIS_CHECK;
	
	REQ_FLOAT_ARG(0, value);
	REQ_FLOAT_ARG(1, time);
	
	_impl->linearRampToValueAtTime(value, time);
	
}


JS_METHOD(AudioParam::exponentialRampToValueAtTime) { THIS_CHECK;
	
	REQ_FLOAT_ARG(0, value);
	REQ_FLOAT_ARG(1, time);
	
	_impl->exponentialRampToValueAtTime(value, time);
	
}


JS_METHOD(AudioParam::setTargetAtTime) { THIS_CHECK;
	
	REQ_FLOAT_ARG(0, target);
	REQ_FLOAT_ARG(1, time);
	REQ_FLOAT_ARG(2, timeConstant);
	
	_impl->setTargetAtTime(target, time, timeConstant);
	
}


JS_METHOD(AudioParam::setValueCurveAtTime) { THIS_CHECK;
	
	REQ_OBJ_ARG(0, values);
	REQ_FLOAT_ARG(1, time);
	REQ_FLOAT_ARG(2, duration);
	
	std::vector<float> curve;
	// TODO: read array
	
	_impl->setValueCurveAtTime(curve, time, duration);
	
}


JS_METHOD(AudioParam::cancelScheduledValues) { THIS_CHECK;
	
	REQ_FLOAT_ARG(0, startTime);
	
	_impl->cancelScheduledValues(startTime);
	
}


JS_METHOD(AudioParam::cancelAndHoldAtTime) { THIS_CHECK;
	
	REQ_FLOAT_ARG(0, startTime);
	
	// TODO: implement
	// _impl->cancelAndHoldAtTime(startTime);
	
}


JS_GETTER(AudioParam::valueGetter) { THIS_CHECK;
	
	Napi::Object context = JS_OBJ(_context);
	AudioContext *audioContext = ObjectWrap::Unwrap<AudioContext>(context);
	
	lab::ContextRenderLock renderLock(audioContext->getContext().get(), "AudioParam::valueGetter");
	
	RET_NUM(_impl->value(renderLock));
	
}

JS_SETTER(AudioParam::valueSetter) { THIS_CHECK; SETTER_FLOAT_ARG;
	
	_impl->setValue(v);
	
}


JS_GETTER(AudioParam::defaultValueGetter) { THIS_CHECK;
	
	RET_NUM(_impl->defaultValue());
	
}


JS_GETTER(AudioParam::minValueGetter) { THIS_CHECK;
	
	RET_NUM(_impl->minValue());
	
}


JS_GETTER(AudioParam::maxValueGetter) { THIS_CHECK;
	
	RET_NUM(_impl->maxValue());
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference AudioParam::_ctorAudioParam;


bool AudioParam::isAudioParam(Napi::Object obj) {
	return obj.InstanceOf(_ctorAudioParam.Value());
}


void AudioParam::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "AudioParam", {
		ACCESSOR_RW(AudioParam, value),
		ACCESSOR_M(AudioParam, cancelAndHoldAtTime),
		ACCESSOR_M(AudioParam, cancelScheduledValues),
		ACCESSOR_M(AudioParam, setValueCurveAtTime),
		ACCESSOR_M(AudioParam, setTargetAtTime),
		ACCESSOR_M(AudioParam, exponentialRampToValueAtTime),
		ACCESSOR_M(AudioParam, linearRampToValueAtTime),
		ACCESSOR_M(AudioParam, setValueAtTime),
		ACCESSOR_M(AudioParam, destroy),
		ACCESSOR_R(AudioParam, maxValue),
		ACCESSOR_R(AudioParam, minValue),
		ACCESSOR_R(AudioParam, defaultValue),
		ACCESSOR_R(AudioParam, isDestroyed)
	});
	
	_ctorAudioParam = Napi::Persistent(ctor);
	_ctorAudioParam.SuppressDestruct();
	
	exports.Set("AudioParam", ctor);
	
}


Napi::Object AudioParam::getNew(Napi::Object context, ParamPtr param) {
	
	Napi::Function ctor = Nan::New(_ctorAudioParam);
	V8_VAR_EXT extParam = JS_EXT(&param);
	Napi::Value argv[] = { context, extParam };
	return Nan::NewInstance(ctor, 2, argv).ToLocalChecked();
	
}


AudioParam::AudioParam(const Napi::CallbackInfo &info): Napi::ObjectWrap<AudioParam>(info) {
	
	CTOR_CHECK("AudioParam");
	
	REQ_OBJ_ARG(0, context);
	REQ_EXT_ARG(1, extParam);
	
	ParamPtr *param = reinterpret_cast<ParamPtr *>(extParam->Value());
	
	AudioParam *audioParam = new AudioParam(context, *param);
	
}


JS_METHOD(AudioParam::destroy) { THIS_CHECK;
	
	_destroy();
	
}


JS_GETTER(AudioParam::isDestroyedGetter) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
