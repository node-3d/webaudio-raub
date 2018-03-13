#include <cstdlib>
#include <iostream>

#include "delay-node.hpp"

using namespace v8;
using namespace node;
using namespace std;


#define THIS_DELAY_NODE                                                    \
	DelayNode *delayNode = ObjectWrap::Unwrap<DelayNode>(info.This());

#define THIS_CHECK                                                            \
	if (delayNode->_isDestroyed) return;

#define DES_CHECK                                                             \
	if (_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (delayNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	delayNode->CACHE = V;


Nan::Persistent<v8::Function> DelayNode::_constructor;


void DelayNode::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("DelayNode"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	
	// -------- dynamic
	
	
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	
	
	
	_constructor.Reset(ctor);
	Nan::Set(target, JS_STR("DelayNode"), ctor);
	
	
}


NAN_METHOD(DelayNode::newCtor) {
	
	CTOR_CHECK("DelayNode");
	
	DelayNode *delayNode = new DelayNode();
	delayNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


DelayNode::DelayNode() {
	
	_isDestroyed = false;
	
}


DelayNode::~DelayNode() {
	
	_destroy();
	
}


void DelayNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	
	
}



NAN_METHOD(DelayNode::destroy) { THIS_DELAY_NODE; THIS_CHECK;
	
	delayNode->_destroy();
	
}




NAN_GETTER(DelayNode::isDestroyedGetter) { THIS_DELAY_NODE;
	
	RET_VALUE(JS_BOOL(delayNode->_isDestroyed));
	
}


NAN_GETTER(DelayNode::delayTimeGetter) { THIS_DELAY_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(delayNode->_delayTime));
	
}

NAN_SETTER(DelayNode::delayTimeSetter) { THIS_DELAY_NODE; THIS_CHECK; SETTER_OBJ_ARG;
	
	if (Nan::New(delayNode->_delayTime) == v) {
		return;
	}
	delayNode->_delayTime.Reset(v);
	
	// TODO: may be additional actions on change?
	
}

