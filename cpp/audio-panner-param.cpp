#include <cstdlib>
//#include <iostream> // -> cout << "..." << endl;


#include <LabSound/core/AudioContext.h>
#include <LabSound/core/PannerNode.h>
#include <LabSound/extended/AudioContextLock.h>

#include "audio-panner-param.hpp"
#include "lab-audio-panner-param.hpp"
#include "audio-context.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_AUDIO_PANNER_PARAM                                               \
	AudioPannerParam *audioPannerParam = Nan::ObjectWrap::Unwrap<AudioPannerParam>(info.This());

#define THIS_CHECK                                                            \
	if (audioPannerParam->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (audioPannerParam->CACHE == V) {                                       \
		return;                                                               \
	}                                                                         \
	audioPannerParam->CACHE = V;


// ------ Methods and props

AudioPannerParam::AudioPannerParam(V8_VAR_OBJ context, ParamPtr param) :
AudioParam(context, param) {
	
}


void AudioPannerParam::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	AudioParam::_destroy();
	
}


NAN_GETTER(AudioPannerParam::valueGetter) { THIS_AUDIO_PANNER_PARAM; THIS_CHECK;
	
	V8_VAR_OBJ context = JS_OBJ(audioPannerParam->_context);
	AudioContext *audioContext = ObjectWrap::Unwrap<AudioContext>(context);
	
	LabAudioPannerParam *param = static_cast<LabAudioPannerParam*>(audioPannerParam->_impl.get());
	RET_VALUE(JS_FLOAT(param->value()));
	
}


NAN_SETTER(AudioPannerParam::valueSetter) {
	THIS_AUDIO_PANNER_PARAM; THIS_CHECK; SETTER_FLOAT_ARG;
	
	LabAudioPannerParam *param = static_cast<LabAudioPannerParam*>(audioPannerParam->_impl.get());
	param->setValue(v);
	
}


// ------ System methods and props for ObjectWrap


Nan::Persistent<FunctionTemplate> AudioPannerParam::_protoAudioPannerParam;
Nan::Persistent<Function> AudioPannerParam::_ctorAudioPannerParam;


bool AudioPannerParam::isAudioPannerParam(V8_VAR_OBJ obj) {
	return Nan::New(_protoAudioPannerParam)->HasInstance(obj);
}


void AudioPannerParam::init(V8_VAR_OBJ target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AudioPannerParam"));
	
	// class AudioPannerParam inherits AudioParam
	V8_VAR_FT parent = Nan::New(AudioParam::_protoAudioParam);
	proto->Inherit(parent);
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_RW(obj, value);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	// -------- static
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoAudioPannerParam.Reset(proto);
	_ctorAudioPannerParam.Reset(ctor);
	
	Nan::Set(target, JS_STR("AudioPannerParam"), ctor);
	
	
}


V8_VAR_OBJ AudioPannerParam::getNew(V8_VAR_OBJ context, ParamPtr param) {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorAudioPannerParam);
	Local<External> extParam = JS_EXT(&param);
	V8_VAR_VAL argv[] = { context, extParam };
	return Nan::NewInstance(ctor, 2, argv).ToLocalChecked();
	
}


NAN_METHOD(AudioPannerParam::newCtor) {
	
	CTOR_CHECK("AudioPannerParam");
	
	REQ_OBJ_ARG(0, context);
	REQ_EXT_ARG(1, extParam);
	
	ParamPtr *param = reinterpret_cast<ParamPtr *>(extParam->Value());
	
	AudioPannerParam *audioPannerParam = new AudioPannerParam(context, *param);
	audioPannerParam->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(AudioPannerParam::destroy) { THIS_AUDIO_PANNER_PARAM; THIS_CHECK;
	
	audioPannerParam->_destroy();
	
}


NAN_GETTER(AudioPannerParam::isDestroyedGetter) { THIS_AUDIO_PANNER_PARAM;
	
	RET_VALUE(JS_BOOL(audioPannerParam->_isDestroyed));
	
}
