#include <cstdlib>
#include <iostream>

#include "convolver-node.hpp"

using namespace v8;
using namespace node;
using namespace std;


#define THIS_CONVOLVER_NODE                                                    \
	ConvolverNode *convolverNode = ObjectWrap::Unwrap<ConvolverNode>(info.This());

#define THIS_CHECK                                                            \
	if (convolverNode->_isDestroyed) return;

#define DES_CHECK                                                             \
	if (_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (convolverNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	convolverNode->CACHE = V;


Nan::Persistent<v8::Function> ConvolverNode::_constructor;


void ConvolverNode::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("ConvolverNode"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	
	// -------- dynamic
	
	
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	
	
	
	_constructor.Reset(ctor);
	Nan::Set(target, JS_STR("ConvolverNode"), ctor);
	
	
}


NAN_METHOD(ConvolverNode::newCtor) {
	
	CTOR_CHECK("ConvolverNode");
	
	ConvolverNode *convolverNode = new ConvolverNode();
	convolverNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


ConvolverNode::ConvolverNode() {
	
	_isDestroyed = false;
	
}


ConvolverNode::~ConvolverNode() {
	
	_destroy();
	
}


void ConvolverNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	
	
}



NAN_METHOD(ConvolverNode::destroy) { THIS_CONVOLVER_NODE; THIS_CHECK;
	
	convolverNode->_destroy();
	
}




NAN_GETTER(ConvolverNode::isDestroyedGetter) { THIS_CONVOLVER_NODE;
	
	RET_VALUE(JS_BOOL(convolverNode->_isDestroyed));
	
}


NAN_GETTER(ConvolverNode::bufferGetter) { THIS_CONVOLVER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(convolverNode->_buffer));
	
}

NAN_SETTER(ConvolverNode::bufferSetter) { THIS_CONVOLVER_NODE; THIS_CHECK; SETTER_OBJ_ARG;
	
	if (Nan::New(convolverNode->_buffer) == v) {
		return;
	}
	convolverNode->_buffer.Reset(v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(ConvolverNode::normalizeGetter) { THIS_CONVOLVER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_BOOL(convolverNode->_normalize));
	
}

NAN_SETTER(ConvolverNode::normalizeSetter) { THIS_CONVOLVER_NODE; THIS_CHECK; SETTER_BOOL_ARG;
	
	CACHE_CAS(_normalize, v);
	
	// TODO: may be additional actions on change?
	
}

