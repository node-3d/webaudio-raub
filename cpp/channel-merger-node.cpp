#include <cstdlib>
#include <iostream>

#include "channel-merger-node.hpp"

using namespace v8;
using namespace node;
using namespace std;


#define THIS_CHANNEL_MERGER_NODE                                                    \
	ChannelMergerNode *channelMergerNode = ObjectWrap::Unwrap<ChannelMergerNode>(info.This());

#define THIS_CHECK                                                            \
	if (channelMergerNode->_isDestroyed) return;

#define DES_CHECK                                                             \
	if (_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (channelMergerNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	channelMergerNode->CACHE = V;


Nan::Persistent<v8::Function> ChannelMergerNode::_constructor;


void ChannelMergerNode::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("ChannelMergerNode"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	
	// -------- dynamic
	
	
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	
	
	
	_constructor.Reset(ctor);
	Nan::Set(target, JS_STR("ChannelMergerNode"), ctor);
	
	
}


NAN_METHOD(ChannelMergerNode::newCtor) {
	
	CTOR_CHECK("ChannelMergerNode");
	
	ChannelMergerNode *channelMergerNode = new ChannelMergerNode();
	channelMergerNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


ChannelMergerNode::ChannelMergerNode() {
	
	_isDestroyed = false;
	
}


ChannelMergerNode::~ChannelMergerNode() {
	
	_destroy();
	
}


void ChannelMergerNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	
	
}



NAN_METHOD(ChannelMergerNode::destroy) { THIS_CHANNEL_MERGER_NODE; THIS_CHECK;
	
	channelMergerNode->_destroy();
	
}




NAN_GETTER(ChannelMergerNode::isDestroyedGetter) { THIS_CHANNEL_MERGER_NODE;
	
	RET_VALUE(JS_BOOL(channelMergerNode->_isDestroyed));
	
}


