#include <cstdlib>


#include "constant-source-node.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_CONSTANT_SOURCE_NODE                                                    \
	ConstantSourceNode *constantSourceNode = Nan::ObjectWrap::Unwrap<ConstantSourceNode>(info.This());

#define THIS_CHECK                                                            \
	if (constantSourceNode->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (constantSourceNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	constantSourceNode->CACHE = V;


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



NAN_GETTER(ConstantSourceNode::offsetGetter) { THIS_CONSTANT_SOURCE_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(constantSourceNode->_offset));
	
}


// ------ System methods and props for ObjectWrap

V8_STORE_FT ConstantSourceNode::_protoConstantSourceNode;
V8_STORE_FUNC ConstantSourceNode::_ctorConstantSourceNode;


void ConstantSourceNode::init(Napi::Object target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);

	// class ConstantSourceNode inherits AudioScheduledSourceNode
	V8_VAR_FT parent = Nan::New(AudioScheduledSourceNode::_protoAudioScheduledSourceNode);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("ConstantSourceNode"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, offset);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoConstantSourceNode.Reset(proto);
	_ctorConstantSourceNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("ConstantSourceNode"), ctor);
	
	
}


bool ConstantSourceNode::isConstantSourceNode(Napi::Object obj) {
	return Nan::New(_protoConstantSourceNode)->HasInstance(obj);
}


Napi::Object ConstantSourceNode::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorConstantSourceNode);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


NAN_METHOD(ConstantSourceNode::newCtor) {
	
	CTOR_CHECK("ConstantSourceNode");
	
	ConstantSourceNode *constantSourceNode = new ConstantSourceNode();
	constantSourceNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(ConstantSourceNode::destroy) { THIS_CONSTANT_SOURCE_NODE; THIS_CHECK;
	
	constantSourceNode->emit("destroy");
	
	constantSourceNode->_destroy();
	
}


NAN_GETTER(ConstantSourceNode::isDestroyedGetter) { THIS_CONSTANT_SOURCE_NODE;
	
	RET_VALUE(JS_BOOL(constantSourceNode->_isDestroyed));
	
}
