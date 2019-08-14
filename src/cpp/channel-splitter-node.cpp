
#include "channel-splitter-node.hpp"

#include "common.hpp"


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

Napi::FunctionReference ChannelSplitterNode::_ctorChannelSplitterNode;


void ChannelSplitterNode::init(Napi::Env env, Napi::Object exports) {
	
	
	ACCESSOR_R(obj, isDestroyed);
	
	
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Napi::Function ctor = DefineClass(env, "ChannelSplitterNode", {
	
	});
	
	_ctorChannelSplitterNode = Napi::Persistent(ctor);
	_ctorChannelSplitterNode.SuppressDestruct();
	
	exports.Set("ChannelSplitterNode", ctor);
	
}


bool ChannelSplitterNode::isChannelSplitterNode(Napi::Object obj) {
	return obj.InstanceOf(_ctorChannelSplitterNode.Value());
}


Napi::Object ChannelSplitterNode::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorChannelSplitterNode);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


JS_METHOD(ChannelSplitterNode::newCtor) {
	
	CTOR_CHECK("ChannelSplitterNode");
	
	ChannelSplitterNode *channelSplitterNode = new ChannelSplitterNode();
	channelSplitterNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


JS_METHOD(ChannelSplitterNode::destroy) { THIS_CHANNEL_SPLITTER_NODE; THIS_CHECK;
	
	channelSplitterNode->emit("destroy");
	
	_destroy();
	
}


JS_GETTER(ChannelSplitterNode::isDestroyedGetter) { THIS_CHANNEL_SPLITTER_NODE;
	
	RET_BOOL(_isDestroyed);
	
}
