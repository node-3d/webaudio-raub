#include <cstdlib>
#include <iostream>

#include "oscillator-node.hpp"

using namespace v8;
using namespace node;
using namespace std;


#define THIS_OSCILLATOR_NODE                                                    \
	OscillatorNode *oscillatorNode = ObjectWrap::Unwrap<OscillatorNode>(info.This());

#define THIS_CHECK                                                            \
	if (oscillatorNode->_isDestroyed) return;

#define DES_CHECK                                                             \
	if (_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (oscillatorNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	oscillatorNode->CACHE = V;


Nan::Persistent<v8::Function> OscillatorNode::_constructor;


void OscillatorNode::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("OscillatorNode"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_RW(obj, type);
	ACCESSOR_R(obj, frequency);
	ACCESSOR_R(obj, detune);
	
	// -------- dynamic
	
	
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	Nan::SetPrototypeMethod(proto, "setPeriodicWave", setPeriodicWave);
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	
	
	
	_constructor.Reset(ctor);
	Nan::Set(target, JS_STR("OscillatorNode"), ctor);
	
	
}


NAN_METHOD(OscillatorNode::newCtor) {
	
	CTOR_CHECK("OscillatorNode");
	
	OscillatorNode *oscillatorNode = new OscillatorNode();
	oscillatorNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


OscillatorNode::OscillatorNode() {
	
	_isDestroyed = false;
	
}


OscillatorNode::~OscillatorNode() {
	
	_destroy();
	
}


void OscillatorNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	
	
}



NAN_METHOD(OscillatorNode::destroy) { THIS_OSCILLATOR_NODE; THIS_CHECK;
	
	oscillatorNode->_destroy();
	
}


NAN_METHOD(OscillatorNode::setPeriodicWave) { THIS_OSCILLATOR_NODE; THIS_CHECK;
	
	REQ_OBJ_ARG(0, periodicWave);
	
	// TODO: do something?
	
}



NAN_GETTER(OscillatorNode::isDestroyedGetter) { THIS_OSCILLATOR_NODE;
	
	RET_VALUE(JS_BOOL(oscillatorNode->_isDestroyed));
	
}


NAN_GETTER(OscillatorNode::typeGetter) { THIS_OSCILLATOR_NODE; THIS_CHECK;
	
	RET_VALUE(JS_UTF8(oscillatorNode->_type));
	
}

NAN_SETTER(OscillatorNode::typeSetter) { THIS_OSCILLATOR_NODE; THIS_CHECK; SETTER_UTF8_ARG;
	
	if (oscillatorNode->_type == *v) {
		return;
	}
	oscillatorNode->_type = *v;
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(OscillatorNode::frequencyGetter) { THIS_OSCILLATOR_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(oscillatorNode->_frequency));
	
}



NAN_GETTER(OscillatorNode::detuneGetter) { THIS_OSCILLATOR_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(oscillatorNode->_detune));
	
}


