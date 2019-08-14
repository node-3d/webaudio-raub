
#include "channel-merger-node.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

ChannelMergerNode::ChannelMergerNode() :
AudioNode() {
	
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

Napi::FunctionReference ChannelMergerNode::_ctorChannelMergerNode;


void ChannelMergerNode::init(Napi::Env env, Napi::Object exports) {
	
	
	ACCESSOR_R(obj, isDestroyed);
	
	
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Napi::Function ctor = DefineClass(env, "ChannelMergerNode", {
	
	});
	
	_ctorChannelMergerNode = Napi::Persistent(ctor);
	_ctorChannelMergerNode.SuppressDestruct();
	
	exports.Set("ChannelMergerNode", ctor);
	
}


bool ChannelMergerNode::isChannelMergerNode(Napi::Object obj) {
	return obj.InstanceOf(_ctorChannelMergerNode.Value());
}


Napi::Object ChannelMergerNode::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorChannelMergerNode);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


JS_METHOD(ChannelMergerNode::newCtor) {
	
	CTOR_CHECK("ChannelMergerNode");
	
	ChannelMergerNode *channelMergerNode = new ChannelMergerNode();
	channelMergerNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


JS_METHOD(ChannelMergerNode::destroy) { THIS_CHANNEL_MERGER_NODE; THIS_CHECK;
	
	channelMergerNode->emit("destroy");
	
	_destroy();
	
}


JS_GETTER(ChannelMergerNode::isDestroyedGetter) { THIS_CHANNEL_MERGER_NODE;
	
	RET_BOOL(_isDestroyed);
	
}
