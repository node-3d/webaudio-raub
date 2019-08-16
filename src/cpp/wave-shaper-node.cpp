
#include "wave-shaper-node.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

WaveShaperNode::WaveShaperNode(const Napi::CallbackInfo &info) :
AudioNode() {
	
	CTOR_CHECK("WaveShaperNode");
	
	_isDestroyed = false;
	
}


WaveShaperNode::~WaveShaperNode() {
	
	_destroy();
	
}


void WaveShaperNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	AudioNode::_destroy();
	
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
	
	RET_STR(__oversample);
	
}

JS_SETTER(WaveShaperNode::oversampleSetter) { THIS_CHECK; SETTER_STR_ARG;
	
	CACHE_CAS(_oversample, v)
	
	// TODO: may be additional actions on change?
	
	emit("oversample", 1, &value);
	
}


// ------ System methods and props for ObjectWrap

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


bool WaveShaperNode::isWaveShaperNode(Napi::Object obj) {
	return obj.InstanceOf(_constructor.Value());
}


JS_METHOD(WaveShaperNode::destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	
}


JS_GETTER(WaveShaperNode::isDestroyedGetter) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
