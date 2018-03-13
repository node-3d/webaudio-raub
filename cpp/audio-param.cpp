#include <cstdlib>
#include <iostream>

#include "audio-param.hpp"

using namespace v8;
using namespace node;
using namespace std;


#define THIS_AUDIO_PARAM                                                    \
	AudioParam *audioParam = ObjectWrap::Unwrap<AudioParam>(info.This());

#define THIS_CHECK                                                            \
	if (audioParam->_isDestroyed) return;

#define DES_CHECK                                                             \
	if (_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (audioParam->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	audioParam->CACHE = V;


Nan::Persistent<v8::Function> AudioParam::_constructor;


void AudioParam::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AudioParam"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	
	// -------- dynamic
	
	
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	
	
	
	_constructor.Reset(ctor);
	Nan::Set(target, JS_STR("AudioParam"), ctor);
	
	
}


NAN_METHOD(AudioParam::newCtor) {
	
	CTOR_CHECK("AudioParam");
	
	AudioParam *audioParam = new AudioParam();
	audioParam->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


AudioParam::AudioParam() {
	
	_isDestroyed = false;
	
}


AudioParam::~AudioParam() {
	
	_destroy();
	
}


void AudioParam::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	
	
}



NAN_METHOD(AudioParam::destroy) { THIS_AUDIO_PARAM; THIS_CHECK;
	
	audioParam->_destroy();
	
}


NAN_METHOD(AudioParam::setValueAtTime) { THIS_AUDIO_PARAM; THIS_CHECK;
	
	REQ_FLOAT_ARG(0, value);
	REQ_DOUBLE_ARG(1, time);
	
	// TODO: do something?
	
}


NAN_METHOD(AudioParam::linearRampToValueAtTime) { THIS_AUDIO_PARAM; THIS_CHECK;
	
	REQ_FLOAT_ARG(0, value);
	REQ_DOUBLE_ARG(1, time);
	
	// TODO: do something?
	
}


NAN_METHOD(AudioParam::exponentialRampToValueAtTime) { THIS_AUDIO_PARAM; THIS_CHECK;
	
	REQ_FLOAT_ARG(0, value);
	REQ_DOUBLE_ARG(1, time);
	
	// TODO: do something?
	
}


NAN_METHOD(AudioParam::setTargetAtTime) { THIS_AUDIO_PARAM; THIS_CHECK;
	
	REQ_FLOAT_ARG(0, target);
	REQ_DOUBLE_ARG(1, time);
	REQ_DOUBLE_ARG(2, timeConstant);
	
	// TODO: do something?
	
}


NAN_METHOD(AudioParam::setValueCurveAtTime) { THIS_AUDIO_PARAM; THIS_CHECK;
	
	REQ_OBJ_ARG(0, values);
	REQ_DOUBLE_ARG(1, time);
	REQ_DOUBLE_ARG(2, duration);
	
	// TODO: do something?
	
}


NAN_METHOD(AudioParam::cancelScheduledValues) { THIS_AUDIO_PARAM; THIS_CHECK;
	
	REQ_DOUBLE_ARG(0, startTime);
	
	// TODO: do something?
	
}


NAN_METHOD(AudioParam::cancelAndHoldAtTime) { THIS_AUDIO_PARAM; THIS_CHECK;
	
	REQ_DOUBLE_ARG(0, startTime);
	
	// TODO: do something?
	
}



NAN_GETTER(AudioParam::isDestroyedGetter) { THIS_AUDIO_PARAM;
	
	RET_VALUE(JS_BOOL(audioParam->_isDestroyed));
	
}


NAN_GETTER(AudioParam::valueGetter) { THIS_AUDIO_PARAM; THIS_CHECK;
	
	RET_VALUE(JS_FLOAT(audioParam->_value));
	
}

NAN_SETTER(AudioParam::valueSetter) { THIS_AUDIO_PARAM; THIS_CHECK; SETTER_FLOAT_ARG;
	
	CACHE_CAS(_value, v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(AudioParam::defaultValueGetter) { THIS_AUDIO_PARAM; THIS_CHECK;
	
	RET_VALUE(JS_FLOAT(audioParam->_defaultValue));
	
}

NAN_SETTER(AudioParam::defaultValueSetter) { THIS_AUDIO_PARAM; THIS_CHECK; SETTER_FLOAT_ARG;
	
	CACHE_CAS(_defaultValue, v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(AudioParam::minValueGetter) { THIS_AUDIO_PARAM; THIS_CHECK;
	
	RET_VALUE(JS_FLOAT(audioParam->_minValue));
	
}

NAN_SETTER(AudioParam::minValueSetter) { THIS_AUDIO_PARAM; THIS_CHECK; SETTER_FLOAT_ARG;
	
	CACHE_CAS(_minValue, v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(AudioParam::maxValueGetter) { THIS_AUDIO_PARAM; THIS_CHECK;
	
	RET_VALUE(JS_FLOAT(audioParam->_maxValue));
	
}

NAN_SETTER(AudioParam::maxValueSetter) { THIS_AUDIO_PARAM; THIS_CHECK; SETTER_FLOAT_ARG;
	
	CACHE_CAS(_maxValue, v);
	
	// TODO: may be additional actions on change?
	
}

