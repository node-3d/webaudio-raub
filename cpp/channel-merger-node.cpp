#include <cstdlib>
//#include <iostream> // -> cout << "..." << endl;


#include "channel-merger-node.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_CHANNEL_MERGER_NODE                                                    \
	ChannelMergerNode *channelMergerNode = Nan::ObjectWrap::Unwrap<ChannelMergerNode>(info.This());

#define THIS_CHECK                                                            \
	if (channelMergerNode->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (channelMergerNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	channelMergerNode->CACHE = V;


// ------ Constructor and Destructor

ChannelMergerNode::ChannelMergerNode() : AudioNode() {
	
	_isDestroyed = false;
	
}


ChannelMergerNode::~ChannelMergerNode() {
	
	_destroy();
	
}


void ChannelMergerNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	AudioNode::_destroy();
	
}


// ------ Methods and props




// ------ System methods and props for ObjectWrap

V8_STORE_FT ChannelMergerNode::_protoChannelMergerNode;
V8_STORE_FUNC ChannelMergerNode::_ctorChannelMergerNode;


void ChannelMergerNode::init(V8_VAR_OBJ target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);

	// class ChannelMergerNode inherits AudioNode
	V8_VAR_FT parent = Nan::New(AudioNode::_protoAudioNode);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("ChannelMergerNode"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoChannelMergerNode.Reset(proto);
	_ctorChannelMergerNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("ChannelMergerNode"), ctor);
	
	
}


V8_VAR_OBJ ChannelMergerNode::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorChannelMergerNode);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


NAN_METHOD(ChannelMergerNode::newCtor) {
	
	CTOR_CHECK("ChannelMergerNode");
	
	ChannelMergerNode *channelMergerNode = new ChannelMergerNode();
	channelMergerNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(ChannelMergerNode::destroy) { THIS_CHANNEL_MERGER_NODE; THIS_CHECK;
	
	channelMergerNode->_destroy();
	
}


NAN_GETTER(ChannelMergerNode::isDestroyedGetter) { THIS_CHANNEL_MERGER_NODE;
	
	RET_VALUE(JS_BOOL(channelMergerNode->_isDestroyed));
	
}
