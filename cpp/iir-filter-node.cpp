#include <cstdlib>
#include <iostream>

#include "iir-filter-node.hpp"

using namespace v8;
using namespace node;
using namespace std;


#define THIS_IIR_FILTER_NODE                                                    \
	IIRFilterNode *iIRFilterNode = ObjectWrap::Unwrap<IIRFilterNode>(info.This());

#define THIS_CHECK                                                            \
	if (iIRFilterNode->_isDestroyed) return;

#define DES_CHECK                                                             \
	if (_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (iIRFilterNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	iIRFilterNode->CACHE = V;


Nan::Persistent<v8::Function> IIRFilterNode::_constructor;


void IIRFilterNode::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("IIRFilterNode"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	
	
	// -------- dynamic
	
	
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	Nan::SetPrototypeMethod(proto, "getFrequencyResponse", getFrequencyResponse);
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	
	
	
	_constructor.Reset(ctor);
	Nan::Set(target, JS_STR("IIRFilterNode"), ctor);
	
	
}


NAN_METHOD(IIRFilterNode::newCtor) {
	
	CTOR_CHECK("IIRFilterNode");
	
	IIRFilterNode *iIRFilterNode = new IIRFilterNode();
	iIRFilterNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


IIRFilterNode::IIRFilterNode() {
	
	_isDestroyed = false;
	
}


IIRFilterNode::~IIRFilterNode() {
	
	_destroy();
	
}


void IIRFilterNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	
	
}



NAN_METHOD(IIRFilterNode::destroy) { THIS_IIR_FILTER_NODE; THIS_CHECK;
	
	iIRFilterNode->_destroy();
	
}


NAN_METHOD(IIRFilterNode::getFrequencyResponse) { THIS_IIR_FILTER_NODE; THIS_CHECK;
	
	REQ_OBJ_ARG(0, frequencyHz);
	REQ_OBJ_ARG(1, magResponse);
	REQ_OBJ_ARG(2, phaseResponse);
	
	// TODO: do something?
	
}



NAN_GETTER(IIRFilterNode::isDestroyedGetter) { THIS_IIR_FILTER_NODE;
	
	RET_VALUE(JS_BOOL(iIRFilterNode->_isDestroyed));
	
}


