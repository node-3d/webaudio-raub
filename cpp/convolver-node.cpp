#include <cstdlib>
//#include <iostream> // -> cout << "..." << endl;


#include "convolver-node.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_CONVOLVER_NODE                                                    \
	ConvolverNode *convolverNode = Nan::ObjectWrap::Unwrap<ConvolverNode>(info.This());

#define THIS_CHECK                                                            \
	if (convolverNode->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (convolverNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	convolverNode->CACHE = V;


// ------ Constructor and Destructor

ConvolverNode::ConvolverNode() : AudioNode() {
	
	_isDestroyed = false;
	
}


ConvolverNode::~ConvolverNode() {
	
	_destroy();
	
}


void ConvolverNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	AudioNode::_destroy();
	
}


// ------ Methods and props



NAN_GETTER(ConvolverNode::bufferGetter) { THIS_CONVOLVER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(convolverNode->_buffer));
	
}

NAN_SETTER(ConvolverNode::bufferSetter) { THIS_CONVOLVER_NODE; THIS_CHECK; SETTER_OBJ_ARG;
	
	if (Nan::New(convolverNode->_buffer) == v) {
		return;
	}
	convolverNode->_buffer.Reset(v);
	
	// TODO: may be additional actions on change?
	
	convolverNode->emit("buffer", 1, &value);
	
}


NAN_GETTER(ConvolverNode::normalizeGetter) { THIS_CONVOLVER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_BOOL(convolverNode->_normalize));
	
}

NAN_SETTER(ConvolverNode::normalizeSetter) { THIS_CONVOLVER_NODE; THIS_CHECK; SETTER_BOOL_ARG;
	
	CACHE_CAS(_normalize, v);
	
	// TODO: may be additional actions on change?
	
	convolverNode->emit("normalize", 1, &value);
	
}


// ------ System methods and props for ObjectWrap

V8_STORE_FT ConvolverNode::_protoConvolverNode;
V8_STORE_FUNC ConvolverNode::_ctorConvolverNode;


void ConvolverNode::init(V8_VAR_OBJ target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);
	
	// class ConvolverNode inherits AudioNode
	V8_VAR_FT parent = Nan::New(AudioNode::_protoAudioNode);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("ConvolverNode"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_RW(obj, buffer);
	ACCESSOR_RW(obj, normalize);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoConvolverNode.Reset(proto);
	_ctorConvolverNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("ConvolverNode"), ctor);
	
	
}


V8_VAR_OBJ ConvolverNode::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorConvolverNode);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


NAN_METHOD(ConvolverNode::newCtor) {
	
	CTOR_CHECK("ConvolverNode");
	
	ConvolverNode *convolverNode = new ConvolverNode();
	convolverNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(ConvolverNode::destroy) { THIS_CONVOLVER_NODE; THIS_CHECK;
	
	convolverNode->_destroy();
	
}


NAN_GETTER(ConvolverNode::isDestroyedGetter) { THIS_CONVOLVER_NODE;
	
	RET_VALUE(JS_BOOL(convolverNode->_isDestroyed));
	
}
