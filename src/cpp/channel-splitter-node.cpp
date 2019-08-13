#include <cstdlib>


#include "channel-splitter-node.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_CHANNEL_SPLITTER_NODE                                                    \
	ChannelSplitterNode *channelSplitterNode = Nan::ObjectWrap::Unwrap<ChannelSplitterNode>(info.This());

#define THIS_CHECK                                                            \
	if (channelSplitterNode->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (channelSplitterNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	channelSplitterNode->CACHE = V;


// ------ Constructor and Destructor

ChannelSplitterNode::ChannelSplitterNode() :
AudioNode() {
	
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

V8_STORE_FT ChannelSplitterNode::_protoChannelSplitterNode;
V8_STORE_FUNC ChannelSplitterNode::_ctorChannelSplitterNode;


void ChannelSplitterNode::init(Napi::Object target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);

	// class ChannelSplitterNode inherits AudioNode
	V8_VAR_FT parent = Nan::New(AudioNode::_protoAudioNode);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("ChannelSplitterNode"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoChannelSplitterNode.Reset(proto);
	_ctorChannelSplitterNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("ChannelSplitterNode"), ctor);
	
	
}


bool ChannelSplitterNode::isChannelSplitterNode(Napi::Object obj) {
	return Nan::New(_protoChannelSplitterNode)->HasInstance(obj);
}


Napi::Object ChannelSplitterNode::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorChannelSplitterNode);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


NAN_METHOD(ChannelSplitterNode::newCtor) {
	
	CTOR_CHECK("ChannelSplitterNode");
	
	ChannelSplitterNode *channelSplitterNode = new ChannelSplitterNode();
	channelSplitterNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(ChannelSplitterNode::destroy) { THIS_CHANNEL_SPLITTER_NODE; THIS_CHECK;
	
	channelSplitterNode->emit("destroy");
	
	channelSplitterNode->_destroy();
	
}


NAN_GETTER(ChannelSplitterNode::isDestroyedGetter) { THIS_CHANNEL_SPLITTER_NODE;
	
	RET_VALUE(JS_BOOL(channelSplitterNode->_isDestroyed));
	
}
