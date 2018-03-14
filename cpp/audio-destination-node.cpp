#include <cstdlib>
#include <iostream>

#include "audio-destination-node.hpp"

using namespace v8;
using namespace node;
using namespace std;


#define THIS_AUDIO_DESTINATION_NODE                                                    \
	AudioDestinationNode *audioDestinationNode = ObjectWrap::Unwrap<AudioDestinationNode>(info.This());

#define THIS_CHECK                                                            \
	if (audioDestinationNode->_isDestroyed) return;

#define DES_CHECK                                                             \
	if (_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (audioDestinationNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	audioDestinationNode->CACHE = V;


Nan::Persistent<v8::Function> AudioDestinationNode::_constructor;


void AudioDestinationNode::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
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
	
	
	
	
	_constructor.Reset(ctor);
	Nan::Set(target, JS_STR("AudioDestinationNode"), ctor);
	
	
}


NAN_METHOD(AudioDestinationNode::newCtor) {
	
	CTOR_CHECK("AudioDestinationNode");
	
	AudioDestinationNode *audioDestinationNode = new AudioDestinationNode();
	audioDestinationNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


AudioDestinationNode::AudioDestinationNode() {
	
	_isDestroyed = false;
	
}


AudioDestinationNode::~AudioDestinationNode() {
	
	_destroy();
	
}


void AudioDestinationNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	
	
}



NAN_METHOD(AudioDestinationNode::destroy) { THIS_AUDIO_DESTINATION_NODE; THIS_CHECK;
	
	audioDestinationNode->_destroy();
	
}




NAN_GETTER(AudioDestinationNode::isDestroyedGetter) { THIS_AUDIO_DESTINATION_NODE;
	
	RET_VALUE(JS_BOOL(audioDestinationNode->_isDestroyed));
	
}


NAN_GETTER(AudioDestinationNode::maxChannelCountGetter) { THIS_AUDIO_DESTINATION_NODE; THIS_CHECK;
	
	RET_VALUE(JS_UINT32(audioDestinationNode->_maxChannelCount));
	
}


