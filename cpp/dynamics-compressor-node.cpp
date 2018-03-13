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

NAN_SETTER(DynamicsCompressorNode::thresholdSetter) { THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK; SETTER_OBJ_ARG;
	
	if (Nan::New(dynamicsCompressorNode->_threshold) == v) {
		return;
	}
	dynamicsCompressorNode->_threshold.Reset(v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(DynamicsCompressorNode::kneeGetter) { THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(dynamicsCompressorNode->_knee));
	
}

NAN_SETTER(DynamicsCompressorNode::kneeSetter) { THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK; SETTER_OBJ_ARG;
	
	if (Nan::New(dynamicsCompressorNode->_knee) == v) {
		return;
	}
	dynamicsCompressorNode->_knee.Reset(v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(DynamicsCompressorNode::ratioGetter) { THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(dynamicsCompressorNode->_ratio));
	
}

NAN_SETTER(DynamicsCompressorNode::ratioSetter) { THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK; SETTER_OBJ_ARG;
	
	if (Nan::New(dynamicsCompressorNode->_ratio) == v) {
		return;
	}
	dynamicsCompressorNode->_ratio.Reset(v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(DynamicsCompressorNode::reductionGetter) { THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK;
	
	RET_VALUE(JS_FLOAT(dynamicsCompressorNode->_reduction));
	
}

NAN_SETTER(DynamicsCompressorNode::reductionSetter) { THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK; SETTER_FLOAT_ARG;
	
	CACHE_CAS(_reduction, v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(DynamicsCompressorNode::attackGetter) { THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(dynamicsCompressorNode->_attack));
	
}

NAN_SETTER(DynamicsCompressorNode::attackSetter) { THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK; SETTER_OBJ_ARG;
	
	if (Nan::New(dynamicsCompressorNode->_attack) == v) {
		return;
	}
	dynamicsCompressorNode->_attack.Reset(v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(DynamicsCompressorNode::releaseGetter) { THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(dynamicsCompressorNode->_release));
	
}

NAN_SETTER(DynamicsCompressorNode::releaseSetter) { THIS_DYNAMICS_COMPRESSOR_NODE; THIS_CHECK; SETTER_OBJ_ARG;
	
	if (Nan::New(dynamicsCompressorNode->_release) == v) {
		return;
	}
	dynamicsCompressorNode->_release.Reset(v);
	
	// TODO: may be additional actions on change?
	
}

