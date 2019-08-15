
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
	
	Napi::Function ctor = DefineClass(env, "ChannelSplitterNode", {
		ACCESSOR_M(ChannelSplitterNode, destroy),
		ACCESSOR_R(ChannelSplitterNode, isDestroyed),
	
	});
	
	_ctorChannelSplitterNode = Napi::Persistent(ctor);
	_ctorChannelSplitterNode.SuppressDestruct();
	
	exports.Set("ChannelSplitterNode", ctor);
	
}


bool ChannelSplitterNode::isChannelSplitterNode(Napi::Object obj) {
	return obj.InstanceOf(_ctorChannelSplitterNode.Value());
}


Napi::Object ChannelSplitterNode::getNew() {
	
	Napi::Function ctor = Nan::New(_ctorChannelSplitterNode);
	// Napi::Value argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


ChannelSplitterNode::ChannelSplitterNode(const Napi::CallbackInfo &info): Napi::ObjectWrap<ChannelSplitterNode>(info) {
	
	CTOR_CHECK("ChannelSplitterNode");
	
	ChannelSplitterNode *channelSplitterNode = new ChannelSplitterNode();
	
}


JS_METHOD(ChannelSplitterNode::destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	
}


JS_GETTER(ChannelSplitterNode::isDestroyedGetter) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
