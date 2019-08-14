
#include "iir-filter-node.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

IIRFilterNode::IIRFilterNode() :
AudioNode() {
	
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


JS_METHOD(IIRFilterNode::getFrequencyResponse) { THIS_IIR_FILTER_NODE; THIS_CHECK;
	
	REQ_OBJ_ARG(0, frequencyHz);
	REQ_OBJ_ARG(1, magResponse);
	REQ_OBJ_ARG(2, phaseResponse);
	
	// TODO: do something?
	
}



// ------ System methods and props for ObjectWrap

Napi::FunctionReference IIRFilterNode::_ctorIIRFilterNode;


void IIRFilterNode::init(Napi::Env env, Napi::Object exports) {
	
	
	ACCESSOR_R(obj, isDestroyed);
	
	
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	Nan::SetPrototypeMethod(proto, "getFrequencyResponse", getFrequencyResponse);
	
	// -------- static
	
	Napi::Function ctor = DefineClass(env, "IIRFilterNode", {
	
	});
	
	_ctorIIRFilterNode = Napi::Persistent(ctor);
	_ctorIIRFilterNode.SuppressDestruct();
	
	exports.Set("IIRFilterNode", ctor);
	
}


bool IIRFilterNode::isIIRFilterNode(Napi::Object obj) {
	return obj.InstanceOf(_ctorIIRFilterNode.Value());
}


Napi::Object IIRFilterNode::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorIIRFilterNode);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


JS_METHOD(IIRFilterNode::newCtor) {
	
	CTOR_CHECK("IIRFilterNode");
	
	IIRFilterNode *iIRFilterNode = new IIRFilterNode();
	iIRFilterNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


JS_METHOD(IIRFilterNode::destroy) { THIS_IIR_FILTER_NODE; THIS_CHECK;
	
	iIRFilterNode->emit("destroy");
	
	_destroy();
	
}


JS_GETTER(IIRFilterNode::isDestroyedGetter) { THIS_IIR_FILTER_NODE;
	
	RET_BOOL(_isDestroyed);
	
}
