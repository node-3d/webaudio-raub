#include <LabSound/core/AudioContext.h>
#include <LabSound/core/DelayNode.h>

#include "delay-node.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"

#include "common.hpp"


// ------ Constructor and Destructor
// Napi::Object context, float sampleRate, double delay
DelayNode::DelayNode(const Napi::CallbackInfo &info) :
AudioNode(context, NodePtr(new lab::DelayNode(sampleRate, delay))) {
	
	CTOR_CHECK("DelayNode");
	
	REQ_OBJ_ARG(0, context);
	REQ_DOUBLE_ARG(1, delay);
	float sampleRate = audioContext->getCtx()->sampleRate();
	
	AudioContext *audioContext = Napi::ObjectWrap<AudioContext>::Unwrap(context);
	
	lab::DelayNode *node = static_cast<lab::DelayNode*>(_impl.get());
	
	_delayTime.Reset(AudioParam::getNew(context, node->delayTime()));
	
	_isDestroyed = false;
	
}


DelayNode::~DelayNode() {
	
	_destroy();
	
}


void DelayNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	AudioNode::_destroy();
	
}


// ------ Methods and props



JS_GETTER(DelayNode::delayTimeGetter) { THIS_CHECK;
	
	RET_VALUE(_delayTime.Value());
	
}


// ------ System methods and props for Napi::ObjectWrap

Napi::FunctionReference DelayNode::_constructor;


void DelayNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "DelayNode", {
		ACCESSOR_M(DelayNode, destroy),
		ACCESSOR_R(DelayNode, delayTime),
		ACCESSOR_R(DelayNode, isDestroyed)
	});
	
	_constructor = Napi::Persistent(ctor);
	_constructor.SuppressDestruct();
	
	exports.Set("DelayNode", ctor);
	
}


bool DelayNode::isDelayNode(Napi::Object obj) {
	return obj.InstanceOf(_constructor.Value());
}


DelayNode::DelayNode(const Napi::CallbackInfo &info): Napi::ObjectWrap<DelayNode>(info) {
	
	CTOR_CHECK("DelayNode");
	
	REQ_OBJ_ARG(0, context);
	REQ_DOUBLE_ARG(1, delay);
	
	AudioContext *audioContext = Napi::ObjectWrap<AudioContext>::Unwrap(context);
	
	DelayNode *delayNode = new DelayNode(context, audioContext->getCtx()->sampleRate(), delay);
	
}


JS_METHOD(DelayNode::destroy) { THIS_CHECK;
	
	emit(env, "destroy");
	
	_destroy();
	
}


JS_GETTER(DelayNode::isDestroyedGetter) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
