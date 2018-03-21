#include <cstdlib>
//#include <iostream> // -> std::cout << "..." << std::endl;


#include "audio-destination-node.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_AUDIO_DESTINATION_NODE                                                    \
	AudioDestinationNode *audioDestinationNode = ObjectWrap::Unwrap<AudioDestinationNode>(info.This());

#define THIS_CHECK                                                            \
	if (audioDestinationNode->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (audioDestinationNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	audioDestinationNode->CACHE = V;


// ------ Constructor and Destructor

AudioDestinationNode::AudioDestinationNode() : AudioNode() {
	
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

Nan::Persistent<v8::FunctionTemplate> AudioDestinationNode::_protoAudioDestinationNode;
Nan::Persistent<v8::Function> AudioDestinationNode::_ctorAudioDestinationNode;


void AudioDestinationNode::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	// class AudioDestinationNode inherits AudioNode
	Local<FunctionTemplate> parent = Nan::New(AudioNode::_protoAudioNode);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AudioDestinationNode"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, maxChannelCount);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoAudioDestinationNode.Reset(proto);
	_ctorAudioDestinationNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("AudioDestinationNode"), ctor);
	
	
}


NAN_METHOD(AudioDestinationNode::newCtor) {
	
	CTOR_CHECK("AudioDestinationNode");
	
	AudioDestinationNode *audioDestinationNode = new AudioDestinationNode();
	audioDestinationNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(AudioDestinationNode::destroy) { THIS_AUDIO_DESTINATION_NODE; THIS_CHECK;
	
	audioDestinationNode->_destroy();
	
}


NAN_GETTER(AudioDestinationNode::isDestroyedGetter) { THIS_AUDIO_DESTINATION_NODE;
	
	RET_VALUE(JS_BOOL(audioDestinationNode->_isDestroyed));
	
}
