#include <LabSound/core/AudioNode.h>
#include <LabSound/core/AudioDestinationNode.h>

#include "audio-destination-node.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

AudioDestinationNode::AudioDestinationNode(Napi::Object context, DestPtr node) :
AudioNode(context, node) {
	
	_isDestroyed = false;
	
}


AudioDestinationNode::~AudioDestinationNode() {
	
	_destroy();
	
}


void AudioDestinationNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	AudioNode::_destroy();
	
}


// ------ Methods and props



JS_GETTER(AudioDestinationNode::maxChannelCountGetter) { THIS_AUDIO_DESTINATION_NODE; THIS_CHECK;
	
	RET_NUM(_maxChannelCount);
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference AudioDestinationNode::_ctorAudioDestinationNode;


void AudioDestinationNode::init(Napi::Env env, Napi::Object exports) {
	
	
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, maxChannelCount);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Napi::Function ctor = DefineClass(env, "AudioDestinationNode", {
	
	});
	
	_ctorAudioDestinationNode = Napi::Persistent(ctor);
	_ctorAudioDestinationNode.SuppressDestruct();
	
	exports.Set("AudioDestinationNode", ctor);
	
}


Napi::Object AudioDestinationNode::getNew(Napi::Object context, DestPtr node) {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorAudioDestinationNode);
	V8_VAR_EXT extNode = JS_EXT(&node);
	V8_VAR_VAL argv[] = { context, extNode };
	return Nan::NewInstance(ctor, 2, argv).ToLocalChecked();
	
}


JS_METHOD(AudioDestinationNode::newCtor) {
	
	CTOR_CHECK("AudioDestinationNode");
	
	REQ_OBJ_ARG(0, context);
	REQ_EXT_ARG(1, extNode);
	
	DestPtr *node = reinterpret_cast<DestPtr *>(extNode->Value());
	
	AudioDestinationNode *audioDestinationNode = new AudioDestinationNode(context, *node);
	audioDestinationNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


JS_METHOD(AudioDestinationNode::destroy) { THIS_AUDIO_DESTINATION_NODE; THIS_CHECK;
	
	audioDestinationNode->emit("destroy");
	
	_destroy();
	
}


JS_GETTER(AudioDestinationNode::isDestroyedGetter) { THIS_AUDIO_DESTINATION_NODE;
	
	RET_BOOL(_isDestroyed);
	
}
