#include <LabSound/core/AudioNode.h>
#include <LabSound/core/AudioDestinationNode.h>

#include "audio-destination-node.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

AudioDestinationNode::AudioDestinationNode(Napi::Object context, DestPtr node):
Napi::ObjectWrap<AudioDestinationNode>(info),
CommonNode(info.Env(), "AudioDestinationNode") {
	
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



JS_GETTER(AudioDestinationNode::maxChannelCountGetter) { THIS_CHECK;
	
	RET_NUM(_maxChannelCount);
	
}


// ------ System methods and props for Napi::ObjectWrap

Napi::FunctionReference AudioDestinationNode::_constructor;


void AudioDestinationNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "AudioDestinationNode", {
		ACCESSOR_M(AudioDestinationNode, destroy),
		ACCESSOR_R(AudioDestinationNode, maxChannelCount),
		ACCESSOR_R(AudioDestinationNode, isDestroyed)
	});
	
	_constructor = Napi::Persistent(ctor);
	_constructor.SuppressDestruct();
	
	exports.Set("AudioDestinationNode", ctor);
	
}


Napi::Object AudioDestinationNode::getNew(Napi::Object context, DestPtr node) {
	
	Napi::Function ctor = Nan::New(_constructor);
	V8_VAR_EXT extNode = JS_EXT(&node);
	Napi::Value argv[] = { context, extNode };
	return Nan::NewInstance(ctor, 2, argv).ToLocalChecked();
	
}


AudioDestinationNode::AudioDestinationNode(const Napi::CallbackInfo &info): Napi::ObjectWrap<AudioDestinationNode>(info) {
	
	CTOR_CHECK("AudioDestinationNode");
	
	REQ_OBJ_ARG(0, context);
	REQ_EXT_ARG(1, extNode);
	
	DestPtr *node = reinterpret_cast<DestPtr *>(extNode->Value());
	
	AudioDestinationNode *audioDestinationNode = new AudioDestinationNode(context, *node);
	
}


JS_METHOD(AudioDestinationNode::destroy) { THIS_CHECK;
	
	emit(env, "destroy");
	
	_destroy();
	
}


JS_GETTER(AudioDestinationNode::isDestroyedGetter) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
