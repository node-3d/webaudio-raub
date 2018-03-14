#include <cstdlib>
#include <iostream>

#include "dynamics-compressor-node.hpp"

using namespace v8;
using namespace node;
using namespace std;


#define THIS_DYNAMICS_COMPRESSOR_NODE                                                    \
	DynamicsCompressorNode *dynamicsCompressorNode = ObjectWrap::Unwrap<DynamicsCompressorNode>(info.This());

#define THIS_CHECK                                                            \
	if (dynamicsCompressorNode->_isDestroyed) return;

#define DES_CHECK                                                             \
	if (_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (dynamicsCompressorNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	dynamicsCompressorNode->CACHE = V;


Nan::Persistent<v8::Function> DynamicsCompressorNode::_constructor;


void DynamicsCompressorNode::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("DynamicsCompressorNode"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
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
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	
	
	
	_constructor.Reset(ctor);
	Nan::Set(target, JS_STR("DynamicsCompressorNode"), ctor);
	
	
}


NAN_METHOD(DynamicsCompressorNode::newCtor) {
	
	CTOR_CHECK("DynamicsCompressorNode");
	
	DynamicsCompressorNode *dynamicsCompressorNode = new DynamicsCompressorNode();
	dynamicsCompressorNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


DynamicsCompressorNode::DynamicsCompressorNode() {
	
	_isDestroyed = false;
	
}


DynamicsCompressorNode::~DynamicsCompressorNode() {
	
	_destroy();
	
}


void DynamicsCompressorNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	
	
}



NAN_METHOD(DynamicsCompressorNode::destroy) { THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK;
	
	dynamicsCompressorNode->_destroy();
	
}




NAN_GETTER(DynamicsCompressorNode::isDestroyedGetter) { THIS_DYNAMICS_COMPRESSOR_NODE;
	
	RET_VALUE(JS_BOOL(dynamicsCompressorNode->_isDestroyed));
	
}


NAN_GETTER(DynamicsCompressorNode::thresholdGetter) { THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(dynamicsCompressorNode->_threshold));
	
}



NAN_GETTER(DynamicsCompressorNode::kneeGetter) { THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(dynamicsCompressorNode->_knee));
	
}



NAN_GETTER(DynamicsCompressorNode::ratioGetter) { THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(dynamicsCompressorNode->_ratio));
	
}



NAN_GETTER(DynamicsCompressorNode::reductionGetter) { THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK;
	
	RET_VALUE(JS_FLOAT(dynamicsCompressorNode->_reduction));
	
}



NAN_GETTER(DynamicsCompressorNode::attackGetter) { THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(dynamicsCompressorNode->_attack));
	
}



NAN_GETTER(DynamicsCompressorNode::releaseGetter) { THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(dynamicsCompressorNode->_release));
	
}

