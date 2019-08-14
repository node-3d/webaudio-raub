
#include "constant-source-node.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

ConstantSourceNode::ConstantSourceNode() :
AudioScheduledSourceNode() {
	
	_isDestroyed = false;
	
}


ConstantSourceNode::~ConstantSourceNode() {
	
	_destroy();
	
}


void ConstantSourceNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	AudioScheduledSourceNode::_destroy();
	
}


// ------ Methods and props



JS_GETTER(ConstantSourceNode::offsetGetter) { THIS_CHECK;
	
	RET_VALUE(__offset.Value());
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference ConstantSourceNode::_ctorConstantSourceNode;


void ConstantSourceNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "ConstantSourceNode", {
		ACCESSOR_M(ConstantSourceNode, destroy),
		ACCESSOR_R(ConstantSourceNode, offset),
		ACCESSOR_R(ConstantSourceNode, isDestroyed),
	
	});
	
	_ctorConstantSourceNode = Napi::Persistent(ctor);
	_ctorConstantSourceNode.SuppressDestruct();
	
	exports.Set("ConstantSourceNode", ctor);
	
}


bool ConstantSourceNode::isConstantSourceNode(Napi::Object obj) {
	return obj.InstanceOf(_ctorConstantSourceNode.Value());
}


Napi::Object ConstantSourceNode::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorConstantSourceNode);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


ConstantSourceNode::ConstantSourceNode(const Napi::CallbackInfo &info): Napi::ObjectWrap<ConstantSourceNode>(info) {
	
	CTOR_CHECK("ConstantSourceNode");
	
	ConstantSourceNode *constantSourceNode = new ConstantSourceNode();
	
}


JS_METHOD(ConstantSourceNode::destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	
}


JS_GETTER(ConstantSourceNode::isDestroyedGetter) {
	
	RET_BOOL(_isDestroyed);
	
}
