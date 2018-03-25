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

Nan::Persistent<FunctionTemplate> DelayNode::_protoDelayNode;
Nan::Persistent<Function> DelayNode::_ctorDelayNode;


void DelayNode::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	// class DelayNode inherits AudioNode
	Local<FunctionTemplate> parent = Nan::New(AudioNode::_protoAudioNode);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("DelayNode"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, delayTime);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoDelayNode.Reset(proto);
	_ctorDelayNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("DelayNode"), ctor);
	
	
}


Local<Object> DelayNode::getNew() {
	
	Local<Function> ctor = Nan::New(_ctorDelayNode);
	// Local<Value> argv[] = { /* arg1, arg2, ... */ };
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
