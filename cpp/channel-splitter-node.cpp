#include <cstdlib>
//#include <iostream> // -> std::cout << "..." << std::endl;


#include "channel-splitter-node.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_CHANNEL_SPLITTER_NODE                                                    \
	ChannelSplitterNode *channelSplitterNode = ObjectWrap::Unwrap<ChannelSplitterNode>(info.This());

#define THIS_CHECK                                                            \
	if (channelSplitterNode->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (channelSplitterNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	channelSplitterNode->CACHE = V;


// ------ Constructor and Destructor

ChannelSplitterNode::ChannelSplitterNode() : AudioNode() {
	
	_isDestroyed = false;
	
}


ChannelSplitterNode::~ChannelSplitterNode() {
	
	_destroy();
	
}


void ChannelSplitterNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	AudioNode::_destroy();
	
}


// ------ Methods and props




// ------ System methods and props for ObjectWrap

Nan::Persistent<v8::FunctionTemplate> ChannelSplitterNode::_protoChannelSplitterNode;
Nan::Persistent<v8::Function> ChannelSplitterNode::_ctorChannelSplitterNode;


void ChannelSplitterNode::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	// class ChannelSplitterNode inherits AudioNode
	Local<FunctionTemplate> parent = Nan::New(AudioNode::_protoAudioNode);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("ChannelSplitterNode"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoChannelSplitterNode.Reset(proto);
	_ctorChannelSplitterNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("ChannelSplitterNode"), ctor);
	
	
}


NAN_METHOD(ChannelSplitterNode::newCtor) {
	
	CTOR_CHECK("ChannelSplitterNode");
	
	ChannelSplitterNode *channelSplitterNode = new ChannelSplitterNode();
	channelSplitterNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(ChannelSplitterNode::destroy) { THIS_CHANNEL_SPLITTER_NODE; THIS_CHECK;
	
	channelSplitterNode->_destroy();
	
}


NAN_GETTER(ChannelSplitterNode::isDestroyedGetter) { THIS_CHANNEL_SPLITTER_NODE;
	
	RET_VALUE(JS_BOOL(channelSplitterNode->_isDestroyed));
	
}
