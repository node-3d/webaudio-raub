#include <LabSound/LabSound.h>

#include "biquad-filter-node.hpp"
#include "audio-param.hpp"


Napi::FunctionReference BiquadFilterNode::_constructor;

void BiquadFilterNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "BiquadFilterNode", {
		ACCESSOR_RW(BiquadFilterNode, type),
		ACCESSOR_M(BiquadFilterNode, getFrequencyResponse),
		ACCESSOR_R(BiquadFilterNode, gain),
		ACCESSOR_R(BiquadFilterNode, Q),
		ACCESSOR_R(BiquadFilterNode, detune),
		ACCESSOR_R(BiquadFilterNode, frequency),
		ACCESSOR_M(BiquadFilterNode, destroy)
	});
	
	_constructor = Napi::Persistent(ctor);
	_constructor.SuppressDestruct();
	
	exports.Set("BiquadFilterNode", ctor);
	
}


BiquadFilterNode::BiquadFilterNode(const Napi::CallbackInfo &info): Napi::ObjectWrap<BiquadFilterNode>(info) {
	
	CTOR_CHECK("BiquadFilterNode");
	
	REQ_OBJ_ARG(0, context);
	
	BiquadFilterNode *biquadFilterNode = new BiquadFilterNode(context);
	
}

BiquadFilterNode::BiquadFilterNode(Napi::Object context):
Napi::ObjectWrap<BiquadFilterNode>(info),
CommonNode(info.Env(), "BiquadFilterNode") { NAPI_ENV;
	
	// AudioNode(context, NodePtr(new lab::BiquadFilterNode()))
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
	
	CommonNode::_destroy();
	
}


// ------ Methods and props


JS_METHOD(BiquadFilterNode::getFrequencyResponse) { THIS_CHECK;
	
	REQ_OBJ_ARG(0, frequencyHz);
	REQ_OBJ_ARG(1, magResponse);
	REQ_OBJ_ARG(2, phaseResponse);
	
	// TODO: do something?
	
}


JS_GETTER(BiquadFilterNode::typeGetter) { THIS_CHECK;
	
	RET_STR(_type);
	
}

JS_SETTER(BiquadFilterNode::typeSetter) { THIS_CHECK; SETTER_STR_ARG;
	
	CACHE_CAS(_type, v);
	
	// TODO: may be additional actions on change?
	
	emit(info, "type", 1, &value);
	
}


JS_GETTER(BiquadFilterNode::frequencyGetter) { THIS_CHECK;
	
	RET_VALUE(_frequency.Value());
	
}


JS_GETTER(BiquadFilterNode::detuneGetter) { THIS_CHECK;
	
	RET_VALUE(_detune.Value());
	
}


JS_GETTER(BiquadFilterNode::QGetter) { THIS_CHECK;
	
	RET_VALUE(_Q.Value());
	
}


JS_GETTER(BiquadFilterNode::gainGetter) { THIS_CHECK;
	
	RET_VALUE(_gain.Value());
	
}


JS_METHOD(BiquadFilterNode::destroy) { THIS_CHECK;
	
	emit(info, "destroy");
	
	_destroy();
	
}
