
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
	
	RET_VALUE(_parameters.Value());
	
}


JS_GETTER(AudioWorkletNode::portGetter) { THIS_CHECK;
	
	RET_VALUE(_port.Value());
	
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


// ------ System methods and props for Napi::ObjectWrap

Napi::FunctionReference AudioWorkletNode::_constructor;


void AudioWorkletNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_SETTER(onprocessorerror);
	JS_ASSIGN_METHOD(destroy);
	JS_ASSIGN_GETTER(port);
	JS_ASSIGN_GETTER(parameters);
	JS_ASSIGN_GETTER(isDestroyed);
	
	exports.Set("AudioWorkletNode", ctor);
	
}


bool AudioWorkletNode::isAudioWorkletNode(Napi::Object obj) {
	return obj.InstanceOf(_constructor.Value());
}


Napi::Object AudioWorkletNode::getNew() {
	
	Napi::Function ctor = Nan::New(_constructor);
	// Napi::Value argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


AudioWorkletNode::AudioWorkletNode(const Napi::CallbackInfo &info): Napi::ObjectWrap<AudioWorkletNode>(info) {
	
	AudioWorkletNode *audioWorkletNode = new AudioWorkletNode();
	
}


JS_METHOD(AudioWorkletNode::destroy) { THIS_CHECK;
	
	_destroy();
	
}


JS_GETTER(AudioWorkletNode::isDestroyedGetter) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
