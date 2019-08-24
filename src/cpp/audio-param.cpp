#include <LabSound/core/AudioContext.h>
#include <LabSound/core/AudioParam.h>
#include <LabSound/extended/AudioContextLock.h>

#include "audio-param.hpp"
#include "audio-context.hpp"

#include "common.hpp"


Napi::FunctionReference AudioParam::_constructor;

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
		ACCESSOR_R(AudioParam, maxValue),
		ACCESSOR_R(AudioParam, minValue),
		ACCESSOR_R(AudioParam, defaultValue),
		ACCESSOR_M(AudioParam, destroy)
	});
	
	_constructor = Napi::Persistent(ctor);
	_constructor.SuppressDestruct();
	
	exports.Set("AudioParam", ctor);
	
}


Napi::Object AudioParam::create(Napi::Env env, Napi::Object context, ParamPtr param) {
	Napi::Function ctor = _constructor.Value().As<Napi::Function>();
	std::vector<napi_value> args;
	args.push_back(context);
	args.push_back(JS_EXT(&param));
	return ctor.New(args);
}


bool AudioParam::isAudioParam(Napi::Object obj) {
	return obj.InstanceOf(_constructor.Value());
}


AudioParam::AudioParam(const Napi::CallbackInfo &info):
Napi::ObjectWrap<AudioParam>(info),
CommonParam(info, "AudioParam") { NAPI_ENV;
	
	REQ_OBJ_ARG(0, context);
	REQ_EXT_ARG(1, extParam);
	
	ParamPtr *param = reinterpret_cast<ParamPtr *>(extParam.Data());
	
	reset(context, *param);
	
}


AudioParam::~AudioParam() {
	_destroy();
}


void AudioParam::_destroy() { DES_CHECK;
	CommonParam::_destroy();
}


JS_METHOD(AudioParam::setValueAtTime) { THIS_CHECK;
	
	REQ_FLOAT_ARG(0, value);
	REQ_FLOAT_ARG(1, time);
	
	_impl->setValueAtTime(value, time);
	RET_UNDEFINED;
	
}


JS_METHOD(AudioParam::linearRampToValueAtTime) { THIS_CHECK;
	
	REQ_FLOAT_ARG(0, value);
	REQ_FLOAT_ARG(1, time);
	
	_impl->linearRampToValueAtTime(value, time);
	RET_UNDEFINED;
	
}


JS_METHOD(AudioParam::exponentialRampToValueAtTime) { THIS_CHECK;
	
	REQ_FLOAT_ARG(0, value);
	REQ_FLOAT_ARG(1, time);
	
	_impl->exponentialRampToValueAtTime(value, time);
	RET_UNDEFINED;
	
}


JS_METHOD(AudioParam::setTargetAtTime) { THIS_CHECK;
	
	REQ_FLOAT_ARG(0, target);
	REQ_FLOAT_ARG(1, time);
	REQ_FLOAT_ARG(2, timeConstant);
	
	_impl->setTargetAtTime(target, time, timeConstant);
	RET_UNDEFINED;
	
}


JS_METHOD(AudioParam::setValueCurveAtTime) { THIS_CHECK;
	
	REQ_OBJ_ARG(0, values);
	REQ_FLOAT_ARG(1, time);
	REQ_FLOAT_ARG(2, duration);
	
	std::vector<float> curve;
	// TODO: read array
	
	_impl->setValueCurveAtTime(curve, time, duration);
	RET_UNDEFINED;
	
}


JS_METHOD(AudioParam::cancelScheduledValues) { THIS_CHECK;
	
	REQ_FLOAT_ARG(0, startTime);
	
	_impl->cancelScheduledValues(startTime);
	RET_UNDEFINED;
	
}


JS_METHOD(AudioParam::cancelAndHoldAtTime) { THIS_CHECK;
	
	REQ_FLOAT_ARG(0, startTime);
	
	// TODO: implement
	// _impl->cancelAndHoldAtTime(startTime);
	RET_UNDEFINED;
	
}


JS_GETTER(AudioParam::valueGetter) { THIS_CHECK;
	
	Napi::Object context = _context.Value();
	AudioContext *audioContext = Napi::ObjectWrap<AudioContext>::Unwrap(context);
	
	lab::ContextRenderLock renderLock(audioContext->getCtx().get(), "AudioParam::valueGetter");
	
	RET_NUM(_impl->value(renderLock));
	
}

JS_SETTER(AudioParam::valueSetter) { THIS_SETTER_CHECK; SETTER_FLOAT_ARG;
	
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
