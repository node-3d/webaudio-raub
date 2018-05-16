#include <cstdlib>
//#include <iostream> // -> cout << "..." << endl;


#include <LabSound/core/AudioNode.h>
#include <LabSound/core/AudioDestinationNode.h>

#include "audio-destination-node.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_AUDIO_DESTINATION_NODE                                           \
	AudioDestinationNode *audioDestinationNode = Nan::ObjectWrap::Unwrap<AudioDestinationNode>(info.This());

#define THIS_CHECK                                                            \
	if (audioDestinationNode->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (audioDestinationNode->CACHE == V) {                                   \
		return;                                                               \
	}                                                                         \
	audioDestinationNode->CACHE = V;


// ------ Constructor and Destructor

AudioDestinationNode::AudioDestinationNode(V8_VAR_OBJ context, DestPtr node) :
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



NAN_GETTER(AudioDestinationNode::maxChannelCountGetter) { THIS_AUDIO_DESTINATION_NODE; THIS_CHECK;
	
	RET_VALUE(JS_UINT32(audioDestinationNode->_maxChannelCount));
	
}


// ------ System methods and props for ObjectWrap

V8_STORE_FT AudioDestinationNode::_protoAudioDestinationNode;
V8_STORE_FUNC AudioDestinationNode::_ctorAudioDestinationNode;


void AudioDestinationNode::init(V8_VAR_OBJ target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);
	
	// class AudioDestinationNode inherits AudioNode
	V8_VAR_FT parent = Nan::New(AudioNode::_protoAudioNode);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AudioDestinationNode"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, maxChannelCount);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoAudioDestinationNode.Reset(proto);
	_ctorAudioDestinationNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("AudioDestinationNode"), ctor);
	
	
}


V8_VAR_OBJ AudioDestinationNode::getNew(V8_VAR_OBJ context, DestPtr node) {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorAudioDestinationNode);
	V8_VAR_EXT extNode = JS_EXT(&node);
	V8_VAR_VAL argv[] = { context, extNode };
	return Nan::NewInstance(ctor, 2, argv).ToLocalChecked();
	
}


NAN_METHOD(AudioDestinationNode::newCtor) {
	
	CTOR_CHECK("AudioDestinationNode");
	
	REQ_OBJ_ARG(0, context);
	REQ_EXT_ARG(1, extNode);
	
	DestPtr *node = reinterpret_cast<DestPtr *>(extNode->Value());
	
	AudioDestinationNode *audioDestinationNode = new AudioDestinationNode(context, *node);
	audioDestinationNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
	
}


NAN_METHOD(AudioDestinationNode::destroy) { THIS_AUDIO_DESTINATION_NODE; THIS_CHECK;
	
	audioDestinationNode->emit("destroy");
	
	audioDestinationNode->_destroy();
	
}


NAN_GETTER(AudioDestinationNode::isDestroyedGetter) { THIS_AUDIO_DESTINATION_NODE;
	
	RET_VALUE(JS_BOOL(audioDestinationNode->_isDestroyed));
	
}
