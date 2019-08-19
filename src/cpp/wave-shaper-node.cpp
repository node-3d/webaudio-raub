#include "wave-shaper-node.hpp"


Napi::FunctionReference WaveShaperNode::_constructor;

void WaveShaperNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "WaveShaperNode", {
		ACCESSOR_RW(WaveShaperNode, oversample),
		ACCESSOR_RW(WaveShaperNode, curve),
		ACCESSOR_M(WaveShaperNode, destroy),
		ACCESSOR_R(WaveShaperNode, isDestroyed)
	});
	
	_constructor = Napi::Persistent(ctor);
	_constructor.SuppressDestruct();
	
	exports.Set("WaveShaperNode", ctor);
	
}


WaveShaperNode::WaveShaperNode(const Napi::CallbackInfo &info) :
AudioNode() {
	
	CTOR_CHECK("WaveShaperNode");
	
	_isDestroyed = false;
	
}


// ------ Methods and props



JS_GETTER(WaveShaperNode::curveGetter) { THIS_CHECK;
	
	RET_VALUE(_curve.Value());
	
}

JS_SETTER(WaveShaperNode::curveSetter) { THIS_CHECK; SETTER_OBJ_ARG;
	
	if (Nan::New(_curve) == v) {
		return;
	}
	_curve.Reset(v);
	
	// TODO: may be additional actions on change?
	
	emit(env, "curve", 1, &value);
	
}


JS_GETTER(WaveShaperNode::oversampleGetter) { THIS_CHECK;
	
	RET_STR(_oversample);
	
}

JS_SETTER(WaveShaperNode::oversampleSetter) { THIS_CHECK; SETTER_STR_ARG;
	
	CACHE_CAS(_oversample, v)
	
	// TODO: may be additional actions on change?
	
	emit(env, "oversample", 1, &value);
	
}
