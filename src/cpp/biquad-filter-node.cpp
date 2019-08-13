#include <cstdlib>

#include <LabSound/core/BiquadFilterNode.h>

#include "biquad-filter-node.hpp"
#include "audio-param.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_BIQUAD_FILTER_NODE                                                    \
	BiquadFilterNode *biquadFilterNode = Nan::ObjectWrap::Unwrap<BiquadFilterNode>(info.This());

#define THIS_CHECK                                                            \
	if (biquadFilterNode->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (biquadFilterNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	biquadFilterNode->CACHE = V;


// ------ Constructor and Destructor

BiquadFilterNode::BiquadFilterNode(Napi::Object context) :
AudioNode(context, NodePtr(new lab::BiquadFilterNode())) {
	
	lab::BiquadFilterNode *node = static_cast<lab::BiquadFilterNode*>(_impl.get());
	
	_frequency.Reset(AudioParam::getNew(context, node->frequency()));
	_detune.Reset(AudioParam::getNew(context, node->detune()));
	_Q.Reset(AudioParam::getNew(context, node->q()));
	_gain.Reset(AudioParam::getNew(context, node->gain()));
	
	_isDestroyed = false;
	
}


BiquadFilterNode::~BiquadFilterNode() {
	
	_destroy();
	
}


void BiquadFilterNode::_destroy() { DES_CHECK;
	
	_frequency.Reset();
	_detune.Reset();
	_Q.Reset();
	_gain.Reset();
	
	_isDestroyed = true;
	
	AudioNode::_destroy();
	
}


// ------ Methods and props


NAN_METHOD(BiquadFilterNode::getFrequencyResponse) { THIS_BIQUAD_FILTER_NODE; THIS_CHECK;
	
	REQ_OBJ_ARG(0, frequencyHz);
	REQ_OBJ_ARG(1, magResponse);
	REQ_OBJ_ARG(2, phaseResponse);
	
	// TODO: do something?
	
}


NAN_GETTER(BiquadFilterNode::typeGetter) { THIS_BIQUAD_FILTER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_UTF8(biquadFilterNode->_type));
	
}

NAN_SETTER(BiquadFilterNode::typeSetter) { THIS_BIQUAD_FILTER_NODE; THIS_CHECK; SETTER_UTF8_ARG;
	
	if (biquadFilterNode->_type == *v) {
		return;
	}
	biquadFilterNode->_type = *v;
	
	// TODO: may be additional actions on change?
	
	biquadFilterNode->emit("type", 1, &value);
	
}


NAN_GETTER(BiquadFilterNode::frequencyGetter) { THIS_BIQUAD_FILTER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(biquadFilterNode->_frequency));
	
}


NAN_GETTER(BiquadFilterNode::detuneGetter) { THIS_BIQUAD_FILTER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(biquadFilterNode->_detune));
	
}


NAN_GETTER(BiquadFilterNode::QGetter) { THIS_BIQUAD_FILTER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(biquadFilterNode->_Q));
	
}


NAN_GETTER(BiquadFilterNode::gainGetter) { THIS_BIQUAD_FILTER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(biquadFilterNode->_gain));
	
}


// ------ System methods and props for ObjectWrap

V8_STORE_FT BiquadFilterNode::_protoBiquadFilterNode;
V8_STORE_FUNC BiquadFilterNode::_ctorBiquadFilterNode;


void BiquadFilterNode::init(Napi::Object target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);

	// class BiquadFilterNode inherits AudioNode
	V8_VAR_FT parent = Nan::New(AudioNode::_protoAudioNode);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("BiquadFilterNode"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_RW(obj, type);
	ACCESSOR_R(obj, frequency);
	ACCESSOR_R(obj, detune);
	ACCESSOR_R(obj, Q);
	ACCESSOR_R(obj, gain);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	Nan::SetPrototypeMethod(proto, "getFrequencyResponse", getFrequencyResponse);
	
	// -------- static
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoBiquadFilterNode.Reset(proto);
	_ctorBiquadFilterNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("BiquadFilterNode"), ctor);
	
	
}


bool BiquadFilterNode::isBiquadFilterNode(Napi::Object obj) {
	return Nan::New(_protoBiquadFilterNode)->HasInstance(obj);
}


Napi::Object BiquadFilterNode::getNew(Napi::Object context) {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorBiquadFilterNode);
	V8_VAR_VAL argv[] = { context };
	return Nan::NewInstance(ctor, 1, argv).ToLocalChecked();
	
}


NAN_METHOD(BiquadFilterNode::newCtor) {
	
	CTOR_CHECK("BiquadFilterNode");
	
	REQ_OBJ_ARG(0, context);
	
	BiquadFilterNode *biquadFilterNode = new BiquadFilterNode(context);
	biquadFilterNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(BiquadFilterNode::destroy) { THIS_BIQUAD_FILTER_NODE; THIS_CHECK;
	
	biquadFilterNode->emit("destroy");
	
	biquadFilterNode->_destroy();
	
}


NAN_GETTER(BiquadFilterNode::isDestroyedGetter) { THIS_BIQUAD_FILTER_NODE;
	
	RET_VALUE(JS_BOOL(biquadFilterNode->_isDestroyed));
	
}
