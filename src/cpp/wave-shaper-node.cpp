#include "wave-shaper-node.hpp"


Napi::FunctionReference WaveShaperNode::_constructor;

void WaveShaperNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_SETTER(oversample);
	JS_ASSIGN_SETTER(curve);
	JS_ASSIGN_METHOD(destroy);
	JS_ASSIGN_GETTER(isDestroyed);
	
	exports.Set("WaveShaperNode", ctor);
	
}


WaveShaperNode::WaveShaperNode(const Napi::CallbackInfo &info) :
AudioNode() {
	
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
	
	emit("curve", 1, &value);
	
}


JS_GETTER(WaveShaperNode::oversampleGetter) { THIS_CHECK;
	
	RET_STR(_oversample);
	
}

JS_SETTER(WaveShaperNode::oversampleSetter) { THIS_CHECK; SETTER_STR_ARG;
	
	CACHE_CAS(_oversample, v)
	
	// TODO: may be additional actions on change?
	
	emit("oversample", 1, &value);
	
}
