
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


JS_METHOD(IIRFilterNode::getFrequencyResponse) { THIS_CHECK;
	
	REQ_OBJ_ARG(0, frequencyHz);
	REQ_OBJ_ARG(1, magResponse);
	REQ_OBJ_ARG(2, phaseResponse);
	
	// TODO: do something?
	
}



// ------ System methods and props for ObjectWrap

Napi::FunctionReference IIRFilterNode::_ctorIIRFilterNode;


void IIRFilterNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "IIRFilterNode", {
		ACCESSOR_M(IIRFilterNode, getFrequencyResponse),
		ACCESSOR_M(IIRFilterNode, destroy),
		ACCESSOR_R(IIRFilterNode, isDestroyed),
	
	});
	
	_ctorIIRFilterNode = Napi::Persistent(ctor);
	_ctorIIRFilterNode.SuppressDestruct();
	
	exports.Set("IIRFilterNode", ctor);
	
}


bool IIRFilterNode::isIIRFilterNode(Napi::Object obj) {
	return obj.InstanceOf(_ctorIIRFilterNode.Value());
}


Napi::Object IIRFilterNode::getNew() {
	
	Napi::Function ctor = Nan::New(_ctorIIRFilterNode);
	// Napi::Value argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


IIRFilterNode::IIRFilterNode(const Napi::CallbackInfo &info): Napi::ObjectWrap<IIRFilterNode>(info) {
	
	CTOR_CHECK("IIRFilterNode");
	
	IIRFilterNode *iIRFilterNode = new IIRFilterNode();
	
}


JS_METHOD(IIRFilterNode::destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	
}


JS_GETTER(IIRFilterNode::isDestroyedGetter) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
