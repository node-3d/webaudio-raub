#include <cstdlib>
#include <iostream>

#include "constant-source-node.hpp"

using namespace v8;
using namespace node;
using namespace std;


#define THIS_CONSTANT_SOURCE_NODE                                                    \
	ConstantSourceNode *constantSourceNode = ObjectWrap::Unwrap<ConstantSourceNode>(info.This());

#define THIS_CHECK                                                            \
	if (constantSourceNode->_isDestroyed) return;

#define DES_CHECK                                                             \
	if (_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (constantSourceNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	constantSourceNode->CACHE = V;


Nan::Persistent<v8::Function> ConstantSourceNode::_constructor;


void ConstantSourceNode::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("ConstantSourceNode"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, offset);
	
	// -------- dynamic
	
	
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	
	
	
	_constructor.Reset(ctor);
	Nan::Set(target, JS_STR("ConstantSourceNode"), ctor);
	
	
}


NAN_METHOD(ConstantSourceNode::newCtor) {
	
	CTOR_CHECK("ConstantSourceNode");
	
	ConstantSourceNode *constantSourceNode = new ConstantSourceNode();
	constantSourceNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


ConstantSourceNode::ConstantSourceNode() {
	
	_isDestroyed = false;
	
}


ConstantSourceNode::~ConstantSourceNode() {
	
	_destroy();
	
}


void ConstantSourceNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	
	
}



NAN_METHOD(ConstantSourceNode::destroy) { THIS_CONSTANT_SOURCE_NODE; THIS_CHECK;
	
	constantSourceNode->_destroy();
	
}




NAN_GETTER(ConstantSourceNode::isDestroyedGetter) { THIS_CONSTANT_SOURCE_NODE;
	
	RET_VALUE(JS_BOOL(constantSourceNode->_isDestroyed));
	
}


NAN_GETTER(ConstantSourceNode::offsetGetter) { THIS_CONSTANT_SOURCE_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(constantSourceNode->_offset));
	
}


