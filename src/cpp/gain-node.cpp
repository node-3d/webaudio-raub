#include <LabSound/core/GainNode.h>

#include "gain-node.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

GainNode::GainNode(Napi::Object context) :
AudioNode(context, NodePtr(new lab::GainNode())) {
	
	lab::GainNode *node = static_cast<lab::GainNode*>(_impl.get());
	
	_gain.Reset(AudioParam::getNew(context, node->gain()));
	
	_isDestroyed = false;
	
}


GainNode::~GainNode() {
	
	_destroy();
	
}


void GainNode::_destroy() { DES_CHECK;
	
	_gain.Reset();
	
	_isDestroyed = true;
	
	AudioNode::_destroy();
	
}


// ------ Methods and props


JS_GETTER(GainNode::gainGetter) { THIS_CHECK;
	
	RET_VALUE(_gain.Value());
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference GainNode::_ctorGainNode;


void GainNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "GainNode", {
		ACCESSOR_M(GainNode, destroy),
		ACCESSOR_R(GainNode, gain),
		ACCESSOR_R(GainNode, isDestroyed)
	});
	
	_ctorGainNode = Napi::Persistent(ctor);
	_ctorGainNode.SuppressDestruct();
	
	exports.Set("GainNode", ctor);
	
}


Napi::Object GainNode::getNew(Napi::Object context) {
	
	Napi::Function ctor = Nan::New(_ctorGainNode);
	Napi::Value argv[] = { context };
	return Nan::NewInstance(ctor, 1, argv).ToLocalChecked();
	
}


GainNode::GainNode(const Napi::CallbackInfo &info): Napi::ObjectWrap<GainNode>(info) {
	
	CTOR_CHECK("GainNode");
	
	REQ_OBJ_ARG(0, context);
	
	GainNode *gainNode = new GainNode(context);
	
}


JS_METHOD(GainNode::destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	
}


JS_GETTER(GainNode::isDestroyedGetter) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
