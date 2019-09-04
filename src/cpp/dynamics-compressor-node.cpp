
#include "dynamics-compressor-node.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

DynamicsCompressorNode::DynamicsCompressorNode() :
AudioNode() {
	
	_isDestroyed = false;
	
}


DynamicsCompressorNode::~DynamicsCompressorNode() {
	
	_destroy();
	
}


void DynamicsCompressorNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	AudioNode::_destroy();
	
}


// ------ Methods and props



JS_GETTER(DynamicsCompressorNode::thresholdGetter) { THIS_CHECK;
	
	RET_VALUE(_threshold.Value());
	
}


JS_GETTER(DynamicsCompressorNode::kneeGetter) { THIS_CHECK;
	
	RET_VALUE(_knee.Value());
	
}


JS_GETTER(DynamicsCompressorNode::ratioGetter) { THIS_CHECK;
	
	RET_VALUE(_ratio.Value());
	
}


JS_GETTER(DynamicsCompressorNode::reductionGetter) { THIS_CHECK;
	
	RET_NUM(_reduction);
	
}


JS_GETTER(DynamicsCompressorNode::attackGetter) { THIS_CHECK;
	
	RET_VALUE(_attack.Value());
	
}


JS_GETTER(DynamicsCompressorNode::releaseGetter) { THIS_CHECK;
	
	RET_VALUE(_release.Value());
	
}


// ------ System methods and props for Napi::ObjectWrap

Napi::FunctionReference DynamicsCompressorNode::_constructor;


void DynamicsCompressorNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_METHOD(destroy);
	JS_ASSIGN_GETTER(release);
	JS_ASSIGN_GETTER(attack);
	JS_ASSIGN_GETTER(reduction);
	JS_ASSIGN_GETTER(ratio);
	JS_ASSIGN_GETTER(knee);
	JS_ASSIGN_GETTER(threshold);
	JS_ASSIGN_GETTER(isDestroyed);
	
	exports.Set("DynamicsCompressorNode", ctor);
	
}


bool DynamicsCompressorNode::isDynamicsCompressorNode(Napi::Object obj) {
	return obj.InstanceOf(_constructor.Value());
}


Napi::Object DynamicsCompressorNode::getNew() {
	
	Napi::Function ctor = Nan::New(_constructor);
	// Napi::Value argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


DynamicsCompressorNode::DynamicsCompressorNode(const Napi::CallbackInfo &info): Napi::ObjectWrap<DynamicsCompressorNode>(info) {
	
	DynamicsCompressorNode *dynamicsCompressorNode = new DynamicsCompressorNode();
	
}


JS_METHOD(DynamicsCompressorNode::destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	
}


JS_GETTER(DynamicsCompressorNode::isDestroyedGetter) { NAPI_ENV;
	
	THIS_DYNAMICS_COMPRESSOR_NODE;
	
	RET_BOOL(_isDestroyed);
	
}
