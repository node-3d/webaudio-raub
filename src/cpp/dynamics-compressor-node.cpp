
#include "dynamics-compressor-node.hpp"

#include "common.hpp"


// ------ Aux macros

	Nan::ObjectWrap::Unwrap<DynamicsCompressorNode>(info.This());


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



JS_GETTER(DynamicsCompressorNode::thresholdGetter) {
	
	THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK;
	
	RET_VALUE(__threshold.Value());
	
}


JS_GETTER(DynamicsCompressorNode::kneeGetter) {
	
	THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK;
	
	RET_VALUE(__knee.Value());
	
}


JS_GETTER(DynamicsCompressorNode::ratioGetter) {
	
	THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK;
	
	RET_VALUE(__ratio.Value());
	
}


JS_GETTER(DynamicsCompressorNode::reductionGetter) {
	
	THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK;
	
	RET_NUM(_reduction);
	
}


JS_GETTER(DynamicsCompressorNode::attackGetter) {
	
	THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK;
	
	RET_VALUE(__attack.Value());
	
}


JS_GETTER(DynamicsCompressorNode::releaseGetter) {
	
	THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK;
	
	RET_VALUE(__release.Value());
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference DynamicsCompressorNode::_ctorDynamicsCompressorNode;


void DynamicsCompressorNode::init(Napi::Env env, Napi::Object exports) {
	
	
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, threshold);
	ACCESSOR_R(obj, knee);
	ACCESSOR_R(obj, ratio);
	ACCESSOR_R(obj, reduction);
	ACCESSOR_R(obj, attack);
	ACCESSOR_R(obj, release);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Napi::Function ctor = DefineClass(env, "DynamicsCompressorNode", {
	
	});
	
	_ctorDynamicsCompressorNode = Napi::Persistent(ctor);
	_ctorDynamicsCompressorNode.SuppressDestruct();
	
	exports.Set("DynamicsCompressorNode", ctor);
	
}


bool DynamicsCompressorNode::isDynamicsCompressorNode(Napi::Object obj) {
	return obj.InstanceOf(_ctorDynamicsCompressorNode.Value());
}


Napi::Object DynamicsCompressorNode::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorDynamicsCompressorNode);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


JS_METHOD(DynamicsCompressorNode::newCtor) {
	
	CTOR_CHECK("DynamicsCompressorNode");
	
	DynamicsCompressorNode *dynamicsCompressorNode = new DynamicsCompressorNode();
	dynamicsCompressorNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


JS_METHOD(DynamicsCompressorNode::destroy) {
	
	THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK;
	
	dynamicsCompressorNode->emit("destroy");
	
	_destroy();
	
}


JS_GETTER(DynamicsCompressorNode::isDestroyedGetter) {
	
	THIS_DYNAMICS_COMPRESSOR_NODE;
	
	RET_BOOL(_isDestroyed);
	
}
