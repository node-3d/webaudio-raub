
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




// ------ System methods and props for Napi::ObjectWrap

Napi::FunctionReference ChannelSplitterNode::_constructor;


void ChannelSplitterNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_METHOD(destroy);
	JS_ASSIGN_GETTER(isDestroyed);
	
	exports.Set("ChannelSplitterNode", ctor);
	
}


bool ChannelSplitterNode::isChannelSplitterNode(Napi::Object obj) {
	return obj.InstanceOf(_constructor.Value());
}


Napi::Object ChannelSplitterNode::getNew() {
	
	Napi::Function ctor = Nan::New(_constructor);
	// Napi::Value argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


ChannelSplitterNode::ChannelSplitterNode(const Napi::CallbackInfo &info): Napi::ObjectWrap<ChannelSplitterNode>(info) {
	
	ChannelSplitterNode *channelSplitterNode = new ChannelSplitterNode();
	
}


JS_METHOD(ChannelSplitterNode::destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	
}


JS_GETTER(ChannelSplitterNode::isDestroyedGetter) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
