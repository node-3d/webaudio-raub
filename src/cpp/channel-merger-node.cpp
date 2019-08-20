
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




// ------ System methods and props for Napi::ObjectWrap

Napi::FunctionReference ChannelMergerNode::_constructor;


void ChannelMergerNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "ChannelMergerNode", {
		ACCESSOR_M(ChannelMergerNode, destroy),
		ACCESSOR_R(ChannelMergerNode, isDestroyed)
	});
	
	_constructor = Napi::Persistent(ctor);
	_constructor.SuppressDestruct();
	
	exports.Set("ChannelMergerNode", ctor);
	
}


bool ChannelMergerNode::isChannelMergerNode(Napi::Object obj) {
	return obj.InstanceOf(_constructor.Value());
}


Napi::Object ChannelMergerNode::getNew() {
	
	Napi::Function ctor = Nan::New(_constructor);
	// Napi::Value argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


ChannelMergerNode::ChannelMergerNode(const Napi::CallbackInfo &info): Napi::ObjectWrap<ChannelMergerNode>(info) {
	
	CTOR_CHECK("ChannelMergerNode");
	
	ChannelMergerNode *channelMergerNode = new ChannelMergerNode();
	
}


JS_METHOD(ChannelMergerNode::destroy) { THIS_CHECK;
	
	emit(info, "destroy");
	
	_destroy();
	
}


JS_GETTER(ChannelMergerNode::isDestroyedGetter) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
