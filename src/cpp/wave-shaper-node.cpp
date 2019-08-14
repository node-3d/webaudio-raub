
#include "wave-shaper-node.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

WaveShaperNode::WaveShaperNode() :
AudioNode() {
	
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



JS_GETTER(WaveShaperNode::curveGetter) { THIS_WAVE_SHAPER_NODE; THIS_CHECK;
	
	RET_VALUE(__curve.Value());
	
}

JS_SETTER(WaveShaperNode::curveSetter) { THIS_WAVE_SHAPER_NODE; THIS_CHECK; SETTER_OBJ_ARG;
	
	if (Nan::New(_curve) == v) {
		return;
	}
	_curve.Reset(v);
	
	// TODO: may be additional actions on change?
	
	waveShaperNode->emit("curve", 1, &value);
	
}


JS_GETTER(WaveShaperNode::oversampleGetter) { THIS_WAVE_SHAPER_NODE; THIS_CHECK;
	
	RET_STR(__oversample);
	
}

JS_SETTER(WaveShaperNode::oversampleSetter) { THIS_WAVE_SHAPER_NODE; THIS_CHECK; SETTER_UTF8_ARG;
	
	if (_oversample == *v) {
		return;
	}
	_oversample = *v;
	
	// TODO: may be additional actions on change?
	
	waveShaperNode->emit("oversample", 1, &value);
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference WaveShaperNode::_ctorWaveShaperNode;


void WaveShaperNode::init(Napi::Env env, Napi::Object exports) {
	
	
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_RW(obj, curve);
	ACCESSOR_RW(obj, oversample);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Napi::Function ctor = DefineClass(env, "WaveShaperNode", {
	
	});
	
	_ctorWaveShaperNode = Napi::Persistent(ctor);
	_ctorWaveShaperNode.SuppressDestruct();
	
	exports.Set("WaveShaperNode", ctor);
	
}


bool WaveShaperNode::isWaveShaperNode(Napi::Object obj) {
	return obj.InstanceOf(_ctorWaveShaperNode.Value());
}


Napi::Object WaveShaperNode::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorWaveShaperNode);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


JS_METHOD(WaveShaperNode::newCtor) {
	
	CTOR_CHECK("WaveShaperNode");
	
	WaveShaperNode *waveShaperNode = new WaveShaperNode();
	waveShaperNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


JS_METHOD(WaveShaperNode::destroy) { THIS_WAVE_SHAPER_NODE; THIS_CHECK;
	
	waveShaperNode->emit("destroy");
	
	_destroy();
	
}


JS_GETTER(WaveShaperNode::isDestroyedGetter) { THIS_WAVE_SHAPER_NODE;
	
	RET_BOOL(_isDestroyed);
	
}
