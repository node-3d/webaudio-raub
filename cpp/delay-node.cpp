#include <cstdlib>
//#include <iostream> // -> cout << "..." << endl;


#include "delay-node.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_DELAY_NODE                                                    \
	DelayNode *delayNode = Nan::ObjectWrap::Unwrap<DelayNode>(info.This());

#define THIS_CHECK                                                            \
	if (delayNode->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (delayNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	delayNode->CACHE = V;


// ------ Constructor and Destructor

DelayNode::DelayNode() : AudioNode() {
	
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



NAN_GETTER(DelayNode::delayTimeGetter) { THIS_DELAY_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(delayNode->_delayTime));
	
}


// ------ System methods and props for ObjectWrap

V8_STORE_FT DelayNode::_protoDelayNode;
V8_STORE_FUNC DelayNode::_ctorDelayNode;


void DelayNode::init(V8_VAR_OBJ target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);

	// class DelayNode inherits AudioNode
	V8_VAR_FT parent = Nan::New(AudioNode::_protoAudioNode);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("DelayNode"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, delayTime);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoDelayNode.Reset(proto);
	_ctorDelayNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("DelayNode"), ctor);
	
	
}


bool DelayNode::isDelayNode(V8_VAR_OBJ obj) {
	return Nan::New(_protoDelayNode)->HasInstance(obj);
}


V8_VAR_OBJ DelayNode::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorDelayNode);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


NAN_METHOD(DelayNode::newCtor) {
	
	CTOR_CHECK("DelayNode");
	
	DelayNode *delayNode = new DelayNode();
	delayNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(DelayNode::destroy) { THIS_DELAY_NODE; THIS_CHECK;
	
	delayNode->_destroy();
	
}


NAN_GETTER(DelayNode::isDestroyedGetter) { THIS_DELAY_NODE;
	
	RET_VALUE(JS_BOOL(delayNode->_isDestroyed));
	
}
