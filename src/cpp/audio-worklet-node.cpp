
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



JS_GETTER(AudioWorkletNode::parametersGetter) { THIS_CHECK;
	
	RET_VALUE(__parameters.Value());
	
}


JS_GETTER(AudioWorkletNode::portGetter) { THIS_CHECK;
	
	RET_VALUE(__port.Value());
	
}


JS_GETTER(AudioWorkletNode::onprocessorerrorGetter) { THIS_CHECK;
	
	RET_VALUE(JS_FUN(_onprocessorerror));
	
}

JS_SETTER(AudioWorkletNode::onprocessorerrorSetter) { THIS_CHECK; SETTER_FUN_ARG;
	
	if (Nan::New(_onprocessorerror) == v) {
		return;
	}
	_onprocessorerror.Reset(v);
	
	// TODO: may be additional actions on change?
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference AudioWorkletNode::_ctorAudioWorkletNode;


void AudioWorkletNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "AudioWorkletNode", {
		ACCESSOR_RW(AudioWorkletNode, onprocessorerror),
		ACCESSOR_M(AudioWorkletNode, destroy),
		ACCESSOR_R(AudioWorkletNode, port),
		ACCESSOR_R(AudioWorkletNode, parameters),
		ACCESSOR_R(AudioWorkletNode, isDestroyed),
	
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


AudioWorkletNode::AudioWorkletNode(const Napi::CallbackInfo &info): Napi::ObjectWrap<AudioWorkletNode>(info) {
	
	CTOR_CHECK("AudioWorkletNode");
	
	AudioWorkletNode *audioWorkletNode = new AudioWorkletNode();
	
}


JS_METHOD(AudioWorkletNode::destroy) { THIS_CHECK;
	
	_destroy();
	
}


JS_GETTER(AudioWorkletNode::isDestroyedGetter) {
	
	RET_BOOL(_isDestroyed);
	
}
