#include <cstdlib>
#include <iostream>

#include "gain-node.hpp"

using namespace v8;
using namespace node;
using namespace std;


#define THIS_GAIN_NODE                                                    \
	GainNode *gainNode = ObjectWrap::Unwrap<GainNode>(info.This());

#define THIS_CHECK                                                            \
	if (gainNode->_isDestroyed) return;

#define DES_CHECK                                                             \
	if (_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (gainNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	gainNode->CACHE = V;


Nan::Persistent<v8::Function> GainNode::_constructor;


void GainNode::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("GainNode"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	
	// -------- dynamic
	
	
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	
	
	
	_constructor.Reset(ctor);
	Nan::Set(target, JS_STR("GainNode"), ctor);
	
	
}


NAN_METHOD(GainNode::newCtor) {
	
	CTOR_CHECK("GainNode");
	
	GainNode *gainNode = new GainNode();
	gainNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


GainNode::GainNode() {
	
	_isDestroyed = false;
	
}


GainNode::~GainNode() {
	
	_destroy();
	
}


void GainNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	
	
}



NAN_METHOD(GainNode::destroy) { THIS_GAIN_NODE; THIS_CHECK;
	
	gainNode->_destroy();
	
}




NAN_GETTER(GainNode::isDestroyedGetter) { THIS_GAIN_NODE;
	
	RET_VALUE(JS_BOOL(gainNode->_isDestroyed));
	
}


NAN_GETTER(GainNode::gainGetter) { THIS_GAIN_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(gainNode->_gain));
	
}

NAN_SETTER(GainNode::gainSetter) { THIS_GAIN_NODE; THIS_CHECK; SETTER_OBJ_ARG;
	
	if (Nan::New(gainNode->_gain) == v) {
		return;
	}
	gainNode->_gain.Reset(v);
	
	// TODO: may be additional actions on change?
	
}

