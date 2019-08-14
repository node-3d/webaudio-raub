#include <LabSound/core/BiquadFilterNode.h>

#include "biquad-filter-node.hpp"
#include "audio-param.hpp"

#include "common.hpp"


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


JS_METHOD(BiquadFilterNode::getFrequencyResponse) { THIS_BIQUAD_FILTER_NODE; THIS_CHECK;
	
	REQ_OBJ_ARG(0, frequencyHz);
	REQ_OBJ_ARG(1, magResponse);
	REQ_OBJ_ARG(2, phaseResponse);
	
	// TODO: do something?
	
}


JS_GETTER(BiquadFilterNode::typeGetter) { THIS_BIQUAD_FILTER_NODE; THIS_CHECK;
	
	RET_STR(__type);
	
}

JS_SETTER(BiquadFilterNode::typeSetter) { THIS_BIQUAD_FILTER_NODE; THIS_CHECK; SETTER_UTF8_ARG;
	
	if (_type == *v) {
		return;
	}
	_type = *v;
	
	// TODO: may be additional actions on change?
	
	biquadFilterNode->emit("type", 1, &value);
	
}


JS_GETTER(BiquadFilterNode::frequencyGetter) { THIS_BIQUAD_FILTER_NODE; THIS_CHECK;
	
	RET_VALUE(__frequency.Value());
	
}


JS_GETTER(BiquadFilterNode::detuneGetter) { THIS_BIQUAD_FILTER_NODE; THIS_CHECK;
	
	RET_VALUE(__detune.Value());
	
}


JS_GETTER(BiquadFilterNode::QGetter) { THIS_BIQUAD_FILTER_NODE; THIS_CHECK;
	
	RET_VALUE(__Q.Value());
	
}


JS_GETTER(BiquadFilterNode::gainGetter) { THIS_BIQUAD_FILTER_NODE; THIS_CHECK;
	
	RET_VALUE(__gain.Value());
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference BiquadFilterNode::_ctorBiquadFilterNode;


void BiquadFilterNode::init(Napi::Env env, Napi::Object exports) {
	
	
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
	
	Napi::Function ctor = DefineClass(env, "BiquadFilterNode", {
	
	});
	
	_ctorBiquadFilterNode = Napi::Persistent(ctor);
	_ctorBiquadFilterNode.SuppressDestruct();
	
	exports.Set("BiquadFilterNode", ctor);
	
}


bool BiquadFilterNode::isBiquadFilterNode(Napi::Object obj) {
	return obj.InstanceOf(_ctorBiquadFilterNode.Value());
}


Napi::Object BiquadFilterNode::getNew(Napi::Object context) {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorBiquadFilterNode);
	V8_VAR_VAL argv[] = { context };
	return Nan::NewInstance(ctor, 1, argv).ToLocalChecked();
	
}


JS_METHOD(BiquadFilterNode::newCtor) {
	
	CTOR_CHECK("BiquadFilterNode");
	
	REQ_OBJ_ARG(0, context);
	
	BiquadFilterNode *biquadFilterNode = new BiquadFilterNode(context);
	biquadFilterNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


JS_METHOD(BiquadFilterNode::destroy) { THIS_BIQUAD_FILTER_NODE; THIS_CHECK;
	
	biquadFilterNode->emit("destroy");
	
	_destroy();
	
}


JS_GETTER(BiquadFilterNode::isDestroyedGetter) { THIS_BIQUAD_FILTER_NODE;
	
	RET_BOOL(_isDestroyed);
	
}
