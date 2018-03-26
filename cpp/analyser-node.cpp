#include <cstdlib>
//#include <iostream> // -> cout << "..." << endl;


#include "analyser-node.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_ANALYSER_NODE                                                    \
	AnalyserNode *analyserNode = Nan::ObjectWrap::Unwrap<AnalyserNode>(info.This());

#define THIS_CHECK                                                            \
	if (analyserNode->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (analyserNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	analyserNode->CACHE = V;


// ------ Constructor and Destructor

AnalyserNode::AnalyserNode() : AudioNode() {
	
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


NAN_METHOD(AnalyserNode::getFloatFrequencyData) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	REQ_OBJ_ARG(0, array);
	
	// TODO: do something?
	
}


NAN_METHOD(AnalyserNode::getByteFrequencyData) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	REQ_OBJ_ARG(0, array);
	
	// TODO: do something?
	
}


NAN_METHOD(AnalyserNode::getFloatTimeDomainData) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	REQ_OBJ_ARG(0, array);
	
	// TODO: do something?
	
}


NAN_METHOD(AnalyserNode::getByteTimeDomainData) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	REQ_OBJ_ARG(0, array);
	
	// TODO: do something?
	
}


NAN_GETTER(AnalyserNode::frequencyBinCountGetter) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_UINT32(analyserNode->_frequencyBinCount));
	
}


NAN_GETTER(AnalyserNode::fftSizeGetter) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_UINT32(analyserNode->_fftSize));
	
}

NAN_SETTER(AnalyserNode::fftSizeSetter) { THIS_ANALYSER_NODE; THIS_CHECK; SETTER_UINT32_ARG;
	
	CACHE_CAS(_fftSize, v);
	
	// TODO: may be additional actions on change?
	
	analyserNode->emit("fftSize", 1, &value);
	
}


NAN_GETTER(AnalyserNode::minDecibelsGetter) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_DOUBLE(analyserNode->_minDecibels));
	
}

NAN_SETTER(AnalyserNode::minDecibelsSetter) { THIS_ANALYSER_NODE; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	CACHE_CAS(_minDecibels, v);
	
	// TODO: may be additional actions on change?
	
	analyserNode->emit("minDecibels", 1, &value);
	
}


NAN_GETTER(AnalyserNode::maxDecibelsGetter) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_DOUBLE(analyserNode->_maxDecibels));
	
}

NAN_SETTER(AnalyserNode::maxDecibelsSetter) { THIS_ANALYSER_NODE; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	CACHE_CAS(_maxDecibels, v);
	
	// TODO: may be additional actions on change?
	
	analyserNode->emit("maxDecibels", 1, &value);
	
}


NAN_GETTER(AnalyserNode::smoothingTimeConstantGetter) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_DOUBLE(analyserNode->_smoothingTimeConstant));
	
}

NAN_SETTER(AnalyserNode::smoothingTimeConstantSetter) { THIS_ANALYSER_NODE; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	CACHE_CAS(_smoothingTimeConstant, v);
	
	// TODO: may be additional actions on change?
	
	analyserNode->emit("smoothingTimeConstant", 1, &value);
	
}


// ------ System methods and props for ObjectWrap

V8_STORE_FT AnalyserNode::_protoAnalyserNode;
V8_STORE_FUNC AnalyserNode::_ctorAnalyserNode;


void AnalyserNode::init(V8_VAR_OBJ target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);

	// class AnalyserNode inherits AudioNode
	V8_VAR_FT parent = Nan::New(AudioNode::_protoAudioNode);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AnalyserNode"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
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
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoAnalyserNode.Reset(proto);
	_ctorAnalyserNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("AnalyserNode"), ctor);
	
	
}


V8_VAR_OBJ AnalyserNode::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorAnalyserNode);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


NAN_METHOD(AnalyserNode::newCtor) {
	
	CTOR_CHECK("AnalyserNode");
	
	AnalyserNode *analyserNode = new AnalyserNode();
	analyserNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(AnalyserNode::destroy) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	analyserNode->_destroy();
	
}


NAN_GETTER(AnalyserNode::isDestroyedGetter) { THIS_ANALYSER_NODE;
	
	RET_VALUE(JS_BOOL(analyserNode->_isDestroyed));
	
}
