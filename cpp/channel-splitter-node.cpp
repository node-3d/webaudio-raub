#include <cstdlib>
#include <iostream>

#include "channel-splitter-node.hpp"

using namespace v8;
using namespace node;
using namespace std;


#define THIS_CHANNEL_SPLITTER_NODE                                                    \
	ChannelSplitterNode *channelSplitterNode = ObjectWrap::Unwrap<ChannelSplitterNode>(info.This());

#define THIS_CHECK                                                            \
	if (channelSplitterNode->_isDestroyed) return;

#define DES_CHECK                                                             \
	if (_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (channelSplitterNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	channelSplitterNode->CACHE = V;


Nan::Persistent<v8::Function> ChannelSplitterNode::_constructor;


void ChannelSplitterNode::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("ChannelSplitterNode"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	
	// -------- dynamic
	
	
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	
	
	
	_constructor.Reset(ctor);
	Nan::Set(target, JS_STR("ChannelSplitterNode"), ctor);
	
	
}


NAN_METHOD(ChannelSplitterNode::newCtor) {
	
	CTOR_CHECK("ChannelSplitterNode");
	
	ChannelSplitterNode *channelSplitterNode = new ChannelSplitterNode();
	channelSplitterNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


ChannelSplitterNode::ChannelSplitterNode() {
	
	_isDestroyed = false;
	
}


ChannelSplitterNode::~ChannelSplitterNode() {
	
	_destroy();
	
}


void ChannelSplitterNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	
	
}



NAN_METHOD(ChannelSplitterNode::destroy) { THIS_CHANNEL_SPLITTER_NODE; THIS_CHECK;
	
	channelSplitterNode->_destroy();
	
}




NAN_GETTER(ChannelSplitterNode::isDestroyedGetter) { THIS_CHANNEL_SPLITTER_NODE;
	
	RET_VALUE(JS_BOOL(channelSplitterNode->_isDestroyed));
	
}


