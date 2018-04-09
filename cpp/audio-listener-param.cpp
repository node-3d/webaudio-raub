#include <cstdlib>
//#include <iostream> // -> cout << "..." << endl;


#include <LabSound/core/AudioContext.h>
#include <LabSound/core/AudioListener.h>
#include <LabSound/extended/AudioContextLock.h>

#include "audio-listener-param.hpp"
#include "lab-audio-listener-param.hpp"
#include "audio-context.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_AUDIO_LISTENER_PARAM                                               \
	AudioListenerParam *audioListenerParam = Nan::ObjectWrap::Unwrap<AudioListenerParam>(info.This());

#define THIS_CHECK                                                            \
	if (audioListenerParam->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (audioListenerParam->CACHE == V) {                                       \
		return;                                                               \
	}                                                                         \
	audioListenerParam->CACHE = V;


// ------ Methods and props

AudioListenerParam::AudioListenerParam(V8_VAR_OBJ context, ParamPtr param) :
AudioParam(context, param) {
	
}


void AudioListenerParam::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	AudioParam::_destroy();
	
}


NAN_GETTER(AudioListenerParam::valueGetter) { THIS_AUDIO_LISTENER_PARAM; THIS_CHECK;
	
	V8_VAR_OBJ context = JS_OBJ(audioListenerParam->_context);
	AudioContext *audioContext = ObjectWrap::Unwrap<AudioContext>(context);
	
	LabAudioListenerParam *param = static_cast<LabAudioListenerParam*>(audioListenerParam->_impl.get());
	RET_VALUE(JS_FLOAT(param->value()));
	
}


NAN_SETTER(AudioListenerParam::valueSetter) {
	THIS_AUDIO_LISTENER_PARAM; THIS_CHECK; SETTER_FLOAT_ARG;
	
	LabAudioListenerParam *param = static_cast<LabAudioListenerParam*>(audioListenerParam->_impl.get());
	param->setValue(v);
	
}


NAN_METHOD(AudioListenerParam::setValueAtTime) { THIS_AUDIO_LISTENER_PARAM; THIS_CHECK;
	
	REQ_FLOAT_ARG(0, v);
	
	LabAudioListenerParam *param = static_cast<LabAudioListenerParam*>(audioListenerParam->_impl.get());
	param->setValue(v);
	
}


NAN_METHOD(AudioListenerParam::setTargetAtTime) { THIS_AUDIO_LISTENER_PARAM; THIS_CHECK;
	
	REQ_FLOAT_ARG(0, v);
	
	LabAudioListenerParam *param = static_cast<LabAudioListenerParam*>(audioListenerParam->_impl.get());
	param->setValue(v);
	
}


// ------ System methods and props for ObjectWrap


Nan::Persistent<FunctionTemplate> AudioListenerParam::_protoAudioListenerParam;
Nan::Persistent<Function> AudioListenerParam::_ctorAudioListenerParam;


bool AudioListenerParam::isAudioListenerParam(V8_VAR_OBJ obj) {
	return Nan::New(_protoAudioListenerParam)->HasInstance(obj);
}


void AudioListenerParam::init(V8_VAR_OBJ target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AudioListenerParam"));
	
	// class AudioListenerParam inherits AudioParam
	V8_VAR_FT parent = Nan::New(AudioParam::_protoAudioParam);
	proto->Inherit(parent);
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_RW(obj, value);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	Nan::SetPrototypeMethod(proto, "setValueAtTime", setValueAtTime);
	Nan::SetPrototypeMethod(proto, "setTargetAtTime", setTargetAtTime);
	
	
	// -------- static
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoAudioListenerParam.Reset(proto);
	_ctorAudioListenerParam.Reset(ctor);
	
	Nan::Set(target, JS_STR("AudioListenerParam"), ctor);
	
}


V8_VAR_OBJ AudioListenerParam::getNew(V8_VAR_OBJ context, ParamPtr param) {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorAudioListenerParam);
	Local<External> extParam = JS_EXT(&param);
	V8_VAR_VAL argv[] = { context, extParam };
	return Nan::NewInstance(ctor, 2, argv).ToLocalChecked();
	
}


NAN_METHOD(AudioListenerParam::newCtor) {
	
	CTOR_CHECK("AudioListenerParam");
	
	REQ_OBJ_ARG(0, context);
	REQ_EXT_ARG(1, extParam);
	
	ParamPtr *param = reinterpret_cast<ParamPtr *>(extParam->Value());
	
	AudioListenerParam *audioListenerParam = new AudioListenerParam(context, *param);
	audioListenerParam->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(AudioListenerParam::destroy) { THIS_AUDIO_LISTENER_PARAM; THIS_CHECK;
	
	audioListenerParam->_destroy();
	
}


NAN_GETTER(AudioListenerParam::isDestroyedGetter) { THIS_AUDIO_LISTENER_PARAM;
	
	RET_VALUE(JS_BOOL(audioListenerParam->_isDestroyed));
	
}
