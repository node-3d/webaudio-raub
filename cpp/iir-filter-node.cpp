#include <cstdlib>
//#include <iostream> // -> cout << "..." << endl;


#include "iir-filter-node.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_IIR_FILTER_NODE                                                    \
	IIRFilterNode *iIRFilterNode = Nan::ObjectWrap::Unwrap<IIRFilterNode>(info.This());

#define THIS_CHECK                                                            \
	if (iIRFilterNode->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (iIRFilterNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	iIRFilterNode->CACHE = V;


// ------ Constructor and Destructor

IIRFilterNode::IIRFilterNode() : AudioNode() {
	
	_isDestroyed = false;
	
}


IIRFilterNode::~IIRFilterNode() {
	
	_destroy();
	
}


void IIRFilterNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	AudioNode::_destroy();
	
}


// ------ Methods and props


NAN_METHOD(IIRFilterNode::getFrequencyResponse) { THIS_IIR_FILTER_NODE; THIS_CHECK;
	
	REQ_OBJ_ARG(0, frequencyHz);
	REQ_OBJ_ARG(1, magResponse);
	REQ_OBJ_ARG(2, phaseResponse);
	
	// TODO: do something?
	
}



// ------ System methods and props for ObjectWrap

V8_STORE_FT IIRFilterNode::_protoIIRFilterNode;
V8_STORE_FUNC IIRFilterNode::_ctorIIRFilterNode;


void IIRFilterNode::init(V8_VAR_OBJ target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);

	// class IIRFilterNode inherits AudioNode
	V8_VAR_FT parent = Nan::New(AudioNode::_protoAudioNode);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("IIRFilterNode"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	Nan::SetPrototypeMethod(proto, "getFrequencyResponse", getFrequencyResponse);
	
	// -------- static
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoIIRFilterNode.Reset(proto);
	_ctorIIRFilterNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("IIRFilterNode"), ctor);
	
	
}


bool IIRFilterNode::isIIRFilterNode(V8_VAR_OBJ obj) {
	return Nan::New(_protoIIRFilterNode)->HasInstance(obj);
}


V8_VAR_OBJ IIRFilterNode::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorIIRFilterNode);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


NAN_METHOD(IIRFilterNode::newCtor) {
	
	CTOR_CHECK("IIRFilterNode");
	
	IIRFilterNode *iIRFilterNode = new IIRFilterNode();
	iIRFilterNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(IIRFilterNode::destroy) { THIS_IIR_FILTER_NODE; THIS_CHECK;
	
	iIRFilterNode->_destroy();
	
}


NAN_GETTER(IIRFilterNode::isDestroyedGetter) { THIS_IIR_FILTER_NODE;
	
	RET_VALUE(JS_BOOL(iIRFilterNode->_isDestroyed));
	
}
