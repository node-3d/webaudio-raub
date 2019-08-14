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


JS_GETTER(GainNode::gainGetter) { THIS_GAIN_NODE; THIS_CHECK;
	
	RET_VALUE(__gain.Value());
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference GainNode::_ctorGainNode;


void GainNode::init(Napi::Env env, Napi::Object exports) {
	
	
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, gain);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	// -------- static
	
	Napi::Function ctor = DefineClass(env, "GainNode", {
	
	});
	
	_ctorGainNode = Napi::Persistent(ctor);
	_ctorGainNode.SuppressDestruct();
	
	exports.Set("GainNode", ctor);
	
}


Napi::Object GainNode::getNew(Napi::Object context) {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorGainNode);
	V8_VAR_VAL argv[] = { context };
	return Nan::NewInstance(ctor, 1, argv).ToLocalChecked();
	
}


JS_METHOD(GainNode::newCtor) {
	
	CTOR_CHECK("GainNode");
	
	REQ_OBJ_ARG(0, context);
	
	GainNode *gainNode = new GainNode(context);
	gainNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


JS_METHOD(GainNode::destroy) { THIS_GAIN_NODE; THIS_CHECK;
	
	gainNode->emit("destroy");
	
	_destroy();
	
}


JS_GETTER(GainNode::isDestroyedGetter) { THIS_GAIN_NODE;
	
	RET_BOOL(_isDestroyed);
	
}
