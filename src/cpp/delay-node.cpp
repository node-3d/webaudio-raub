#include <LabSound/core/AudioContext.h>
#include <LabSound/core/DelayNode.h>

#include "delay-node.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

DelayNode::DelayNode(Napi::Object context, float sampleRate, double delay) :
AudioNode(context, NodePtr(new lab::DelayNode(sampleRate, delay))) {
	
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



JS_GETTER(DelayNode::delayTimeGetter) { THIS_DELAY_NODE; THIS_CHECK;
	
	RET_VALUE(__delayTime.Value());
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference DelayNode::_ctorDelayNode;


void DelayNode::init(Napi::Env env, Napi::Object exports) {
	
	
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, delayTime);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Napi::Function ctor = DefineClass(env, "DelayNode", {
	
	});
	
	_ctorDelayNode = Napi::Persistent(ctor);
	_ctorDelayNode.SuppressDestruct();
	
	exports.Set("DelayNode", ctor);
	
}


bool DelayNode::isDelayNode(Napi::Object obj) {
	return obj.InstanceOf(_ctorDelayNode.Value());
}


Napi::Object DelayNode::getNew(Napi::Object context, double delay) {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorDelayNode);
	V8_VAR_VAL argv[] = { context, JS_NUM(delay) };
	return Nan::NewInstance(ctor, 2, argv).ToLocalChecked();
	
}


JS_METHOD(DelayNode::newCtor) {
	
	CTOR_CHECK("DelayNode");
	
	REQ_OBJ_ARG(0, context);
	REQ_DOUBLE_ARG(1, delay);
	
	AudioContext *audioContext = Nan::ObjectWrap::Unwrap<AudioContext>(context);
	
	DelayNode *delayNode = new DelayNode(context, audioContext->getContext()->sampleRate(), delay);
	delayNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


JS_METHOD(DelayNode::destroy) { THIS_DELAY_NODE; THIS_CHECK;
	
	delayNode->emit("destroy");
	
	_destroy();
	
}


JS_GETTER(DelayNode::isDestroyedGetter) { THIS_DELAY_NODE;
	
	RET_BOOL(_isDestroyed);
	
}
