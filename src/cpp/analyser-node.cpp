
#include "analyser-node.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

AnalyserNode::AnalyserNode() :
AudioNode() {
	
	_isDestroyed = false;
	
}


AnalyserNode::~AnalyserNode() {
	
	_destroy();
	
}


void AnalyserNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	AudioNode::_destroy();
	
}


// ------ Methods and props


JS_METHOD(AnalyserNode::getFloatFrequencyData) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	REQ_OBJ_ARG(0, array);
	
	// TODO: do something?
	
}


JS_METHOD(AnalyserNode::getByteFrequencyData) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	REQ_OBJ_ARG(0, array);
	
	// TODO: do something?
	
}


JS_METHOD(AnalyserNode::getFloatTimeDomainData) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	REQ_OBJ_ARG(0, array);
	
	// TODO: do something?
	
}


JS_METHOD(AnalyserNode::getByteTimeDomainData) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	REQ_OBJ_ARG(0, array);
	
	// TODO: do something?
	
}


JS_GETTER(AnalyserNode::frequencyBinCountGetter) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	RET_NUM(_frequencyBinCount);
	
}


JS_GETTER(AnalyserNode::fftSizeGetter) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	RET_NUM(_fftSize);
	
}

JS_SETTER(AnalyserNode::fftSizeSetter) { THIS_ANALYSER_NODE; THIS_CHECK; SETTER_UINT32_ARG;
	
	CACHE_CAS(_fftSize, v);
	
	// TODO: may be additional actions on change?
	
	analyserNode->emit("fftSize", 1, &value);
	
}


JS_GETTER(AnalyserNode::minDecibelsGetter) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	RET_NUM(_minDecibels);
	
}

JS_SETTER(AnalyserNode::minDecibelsSetter) { THIS_ANALYSER_NODE; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	CACHE_CAS(_minDecibels, v);
	
	// TODO: may be additional actions on change?
	
	analyserNode->emit("minDecibels", 1, &value);
	
}


JS_GETTER(AnalyserNode::maxDecibelsGetter) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	RET_NUM(_maxDecibels);
	
}

JS_SETTER(AnalyserNode::maxDecibelsSetter) { THIS_ANALYSER_NODE; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	CACHE_CAS(_maxDecibels, v);
	
	// TODO: may be additional actions on change?
	
	analyserNode->emit("maxDecibels", 1, &value);
	
}


JS_GETTER(AnalyserNode::smoothingTimeConstantGetter) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	RET_NUM(_smoothingTimeConstant);
	
}

JS_SETTER(AnalyserNode::smoothingTimeConstantSetter) { THIS_ANALYSER_NODE; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	CACHE_CAS(_smoothingTimeConstant, v);
	
	// TODO: may be additional actions on change?
	
	analyserNode->emit("smoothingTimeConstant", 1, &value);
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference AnalyserNode::_ctorAnalyserNode;


void AnalyserNode::init(Napi::Env env, Napi::Object exports) {
	
	
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, frequencyBinCount);
	ACCESSOR_RW(obj, fftSize);
	ACCESSOR_RW(obj, minDecibels);
	ACCESSOR_RW(obj, maxDecibels);
	ACCESSOR_RW(obj, smoothingTimeConstant);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	Nan::SetPrototypeMethod(proto, "getFloatFrequencyData", getFloatFrequencyData);
	Nan::SetPrototypeMethod(proto, "getByteFrequencyData", getByteFrequencyData);
	Nan::SetPrototypeMethod(proto, "getFloatTimeDomainData", getFloatTimeDomainData);
	Nan::SetPrototypeMethod(proto, "getByteTimeDomainData", getByteTimeDomainData);
	
	// -------- static
	
	Napi::Function ctor = DefineClass(env, "AnalyserNode", {
	
	});
	
	_ctorAnalyserNode = Napi::Persistent(ctor);
	_ctorAnalyserNode.SuppressDestruct();
	
	exports.Set("AnalyserNode", ctor);
	
}


bool AnalyserNode::isAnalyserNode(Napi::Object obj) {
	return obj.InstanceOf(_ctorAnalyserNode.Value());
}


Napi::Object AnalyserNode::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorAnalyserNode);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


JS_METHOD(AnalyserNode::newCtor) {
	
	CTOR_CHECK("AnalyserNode");
	
	AnalyserNode *analyserNode = new AnalyserNode();
	analyserNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


JS_METHOD(AnalyserNode::destroy) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	analyserNode->emit("destroy");
	
	_destroy();
	
}


JS_GETTER(AnalyserNode::isDestroyedGetter) { THIS_ANALYSER_NODE;
	
	RET_BOOL(_isDestroyed);
	
}
