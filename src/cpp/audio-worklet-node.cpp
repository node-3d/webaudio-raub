
#include "audio-worklet-node.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

AudioWorkletNode::AudioWorkletNode() {
	
	_isDestroyed = false;
	
}


AudioWorkletNode::~AudioWorkletNode() {
	
	_destroy();
	
}


void AudioWorkletNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
}


// ------ Methods and props



JS_GETTER(AudioWorkletNode::parametersGetter) { THIS_AUDIO_WORKLET_NODE; THIS_CHECK;
	
	RET_VALUE(__parameters.Value());
	
}


JS_GETTER(AudioWorkletNode::portGetter) { THIS_AUDIO_WORKLET_NODE; THIS_CHECK;
	
	RET_VALUE(__port.Value());
	
}


JS_GETTER(AudioWorkletNode::onprocessorerrorGetter) { THIS_AUDIO_WORKLET_NODE; THIS_CHECK;
	
	RET_VALUE(JS_FUN(_onprocessorerror));
	
}

JS_SETTER(AudioWorkletNode::onprocessorerrorSetter) { THIS_AUDIO_WORKLET_NODE; THIS_CHECK; SETTER_FUN_ARG;
	
	if (Nan::New(_onprocessorerror) == v) {
		return;
	}
	_onprocessorerror.Reset(v);
	
	// TODO: may be additional actions on change?
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference AudioWorkletNode::_ctorAudioWorkletNode;


void AudioWorkletNode::init(Napi::Env env, Napi::Object exports) {
	
	
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, parameters);
	ACCESSOR_R(obj, port);
	ACCESSOR_RW(obj, onprocessorerror);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Napi::Function ctor = DefineClass(env, "AudioWorkletNode", {
	
	});
	
	_ctorAudioWorkletNode = Napi::Persistent(ctor);
	_ctorAudioWorkletNode.SuppressDestruct();
	
	exports.Set("AudioWorkletNode", ctor);
	
}


bool AudioWorkletNode::isAudioWorkletNode(Napi::Object obj) {
	return obj.InstanceOf(_ctorAudioWorkletNode.Value());
}


Napi::Object AudioWorkletNode::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorAudioWorkletNode);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


JS_METHOD(AudioWorkletNode::newCtor) {
	
	CTOR_CHECK("AudioWorkletNode");
	
	AudioWorkletNode *audioWorkletNode = new AudioWorkletNode();
	audioWorkletNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


JS_METHOD(AudioWorkletNode::destroy) { THIS_AUDIO_WORKLET_NODE; THIS_CHECK;
	
	_destroy();
	
}


JS_GETTER(AudioWorkletNode::isDestroyedGetter) { THIS_AUDIO_WORKLET_NODE;
	
	RET_BOOL(_isDestroyed);
	
}
