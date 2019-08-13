#include <cstdlib>


#include "dynamics-compressor-node.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_DYNAMICS_COMPRESSOR_NODE                                         \
	DynamicsCompressorNode *dynamicsCompressorNode =                          \
	Nan::ObjectWrap::Unwrap<DynamicsCompressorNode>(info.This());

#define CACHE_CAS(CACHE, V)                                                   \
	if (this.CACHE == V) {                                 \
		return;                                                               \
	}                                                                         \
	this.CACHE = V;


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



NAN_GETTER(DynamicsCompressorNode::thresholdGetter) {
	
	THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(dynamicsCompressorNode->_threshold));
	
}


NAN_GETTER(DynamicsCompressorNode::kneeGetter) {
	
	THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(dynamicsCompressorNode->_knee));
	
}


NAN_GETTER(DynamicsCompressorNode::ratioGetter) {
	
	THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(dynamicsCompressorNode->_ratio));
	
}


NAN_GETTER(DynamicsCompressorNode::reductionGetter) {
	
	THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK;
	
	RET_NUM(dynamicsCompressorNode->_reduction);
	
}


NAN_GETTER(DynamicsCompressorNode::attackGetter) {
	
	THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(dynamicsCompressorNode->_attack));
	
}


NAN_GETTER(DynamicsCompressorNode::releaseGetter) {
	
	THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(dynamicsCompressorNode->_release));
	
}


// ------ System methods and props for ObjectWrap

V8_STORE_FT DynamicsCompressorNode::_protoDynamicsCompressorNode;
V8_STORE_FUNC DynamicsCompressorNode::_ctorDynamicsCompressorNode;


void DynamicsCompressorNode::init(Napi::Object target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);

	// class DynamicsCompressorNode inherits AudioNode
	V8_VAR_FT parent = Nan::New(AudioNode::_protoAudioNode);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("DynamicsCompressorNode"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
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
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoDynamicsCompressorNode.Reset(proto);
	_ctorDynamicsCompressorNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("DynamicsCompressorNode"), ctor);
	
	
}


bool DynamicsCompressorNode::isDynamicsCompressorNode(Napi::Object obj) {
	return Nan::New(_protoDynamicsCompressorNode)->HasInstance(obj);
}


Napi::Object DynamicsCompressorNode::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorDynamicsCompressorNode);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


NAN_METHOD(DynamicsCompressorNode::newCtor) {
	
	CTOR_CHECK("DynamicsCompressorNode");
	
	DynamicsCompressorNode *dynamicsCompressorNode = new DynamicsCompressorNode();
	dynamicsCompressorNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(DynamicsCompressorNode::destroy) {
	
	THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK;
	
	dynamicsCompressorNode->emit("destroy");
	
	dynamicsCompressorNode->_destroy();
	
}


NAN_GETTER(DynamicsCompressorNode::isDestroyedGetter) {
	
	THIS_DYNAMICS_COMPRESSOR_NODE;
	
	RET_BOOL(dynamicsCompressorNode->_isDestroyed);
	
}
