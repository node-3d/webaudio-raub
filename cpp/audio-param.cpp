#include <cstdlib>
//#include <iostream> // -> cout << "..." << endl;


#include <LabSound/core/AudioContext.h>
#include <LabSound/core/AudioParam.h>
#include <LabSound/extended/AudioContextLock.h>

#include "audio-param.hpp"
#include "audio-context.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_AUDIO_PARAM                                                    \
	AudioParam *audioParam = Nan::ObjectWrap::Unwrap<AudioParam>(info.This());

#define THIS_CHECK                                                            \
	if (audioParam->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (audioParam->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	audioParam->CACHE = V;


// ------ Constructor and Destructor

AudioParam::AudioParam(V8_VAR_OBJ context, ParamPtr param) {
	
	_impl = param;
	_context.Reset(context);
	
	_isDestroyed = false;
	
}


AudioParam::~AudioParam() {
	
	_destroy();
	
}


void AudioParam::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
}


// ------ Methods and props


NAN_METHOD(AudioParam::setValueAtTime) { THIS_AUDIO_PARAM; THIS_CHECK;
	
	REQ_FLOAT_ARG(0, value);
	REQ_FLOAT_ARG(1, time);
	
	audioParam->_impl->setValueAtTime(value, time);
	
}


NAN_METHOD(AudioParam::linearRampToValueAtTime) { THIS_AUDIO_PARAM; THIS_CHECK;
	
	REQ_FLOAT_ARG(0, value);
	REQ_FLOAT_ARG(1, time);
	
	audioParam->_impl->linearRampToValueAtTime(value, time);
	
}


NAN_METHOD(AudioParam::exponentialRampToValueAtTime) { THIS_AUDIO_PARAM; THIS_CHECK;
	
	REQ_FLOAT_ARG(0, value);
	REQ_FLOAT_ARG(1, time);
	
	audioParam->_impl->exponentialRampToValueAtTime(value, time);
	
}


NAN_METHOD(AudioParam::setTargetAtTime) { THIS_AUDIO_PARAM; THIS_CHECK;
	
	REQ_FLOAT_ARG(0, target);
	REQ_FLOAT_ARG(1, time);
	REQ_FLOAT_ARG(2, timeConstant);
	
	audioParam->_impl->setTargetAtTime(target, time, timeConstant);
	
}


NAN_METHOD(AudioParam::setValueCurveAtTime) { THIS_AUDIO_PARAM; THIS_CHECK;
	
	REQ_OBJ_ARG(0, values);
	REQ_FLOAT_ARG(1, time);
	REQ_FLOAT_ARG(2, duration);
	
	std::vector<float> curve;
	// TODO: read array
	
	audioParam->_impl->setValueCurveAtTime(curve, time, duration);
	
}


NAN_METHOD(AudioParam::cancelScheduledValues) { THIS_AUDIO_PARAM; THIS_CHECK;
	
	REQ_FLOAT_ARG(0, startTime);
	
	audioParam->_impl->cancelScheduledValues(startTime);
	
}


NAN_METHOD(AudioParam::cancelAndHoldAtTime) { THIS_AUDIO_PARAM; THIS_CHECK;
	
	REQ_FLOAT_ARG(0, startTime);
	
	// TODO: implement
	// audioParam->_impl->cancelAndHoldAtTime(startTime);
	
}


NAN_GETTER(AudioParam::valueGetter) { THIS_AUDIO_PARAM; THIS_CHECK;
	
	V8_VAR_OBJ context = JS_OBJ(audioParam->_context);
	AudioContext *audioContext = ObjectWrap::Unwrap<AudioContext>(context);
	
	lab::ContextRenderLock renderLock(audioContext->getContext(), "AudioParam::valueGetter");
	
	RET_VALUE(JS_FLOAT(audioParam->_impl->value(renderLock)));
	
}

NAN_SETTER(AudioParam::valueSetter) { THIS_AUDIO_PARAM; THIS_CHECK; SETTER_FLOAT_ARG;
	
	audioParam->_impl->setValue(v);
	
}


NAN_GETTER(AudioParam::defaultValueGetter) { THIS_AUDIO_PARAM; THIS_CHECK;
	
	RET_VALUE(JS_FLOAT(audioParam->_impl->defaultValue()));
	
}


NAN_GETTER(AudioParam::minValueGetter) { THIS_AUDIO_PARAM; THIS_CHECK;
	
	RET_VALUE(JS_FLOAT(audioParam->_impl->minValue()));
	
}


NAN_GETTER(AudioParam::maxValueGetter) { THIS_AUDIO_PARAM; THIS_CHECK;
	
	RET_VALUE(JS_FLOAT(audioParam->_impl->maxValue()));
	
}


// ------ System methods and props for ObjectWrap

Nan::Persistent<FunctionTemplate> AudioParam::_protoAudioParam;
Nan::Persistent<Function> AudioParam::_ctorAudioParam;


void AudioParam::init(V8_VAR_OBJ target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AudioParam"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_RW(obj, value);
	ACCESSOR_R(obj, defaultValue);
	ACCESSOR_R(obj, minValue);
	ACCESSOR_R(obj, maxValue);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	Nan::SetPrototypeMethod(proto, "setValueAtTime", setValueAtTime);
	Nan::SetPrototypeMethod(proto, "linearRampToValueAtTime", linearRampToValueAtTime);
	Nan::SetPrototypeMethod(proto, "exponentialRampToValueAtTime", exponentialRampToValueAtTime);
	Nan::SetPrototypeMethod(proto, "setTargetAtTime", setTargetAtTime);
	Nan::SetPrototypeMethod(proto, "setValueCurveAtTime", setValueCurveAtTime);
	Nan::SetPrototypeMethod(proto, "cancelScheduledValues", cancelScheduledValues);
	Nan::SetPrototypeMethod(proto, "cancelAndHoldAtTime", cancelAndHoldAtTime);
	
	// -------- static
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoAudioParam.Reset(proto);
	_ctorAudioParam.Reset(ctor);
	
	Nan::Set(target, JS_STR("AudioParam"), ctor);
	
	
}


V8_VAR_OBJ AudioParam::getNew(V8_VAR_OBJ context, ParamPtr param) {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorAudioParam);
	Local<External> extParam = JS_EXT(&param);
	V8_VAR_VAL argv[] = { context, extParam };
	return Nan::NewInstance(ctor, 2, argv).ToLocalChecked();
	
}


NAN_METHOD(AudioParam::newCtor) {
	
	CTOR_CHECK("AudioParam");
	
	REQ_OBJ_ARG(0, context);
	REQ_EXT_ARG(1, extParam);
	
	ParamPtr *param = reinterpret_cast<ParamPtr *>(extParam->Value());
	
	AudioParam *audioParam = new AudioParam(context, *param);
	audioParam->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(AudioParam::destroy) { THIS_AUDIO_PARAM; THIS_CHECK;
	
	audioParam->_destroy();
	
}


NAN_GETTER(AudioParam::isDestroyedGetter) { THIS_AUDIO_PARAM;
	
	RET_VALUE(JS_BOOL(audioParam->_isDestroyed));
	
}
