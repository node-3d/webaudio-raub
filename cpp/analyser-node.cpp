#include <cstdlib>
#include <iostream>

#include "analyser-node.hpp"

#include <LabSound/core/AnalyserNode.h>

using namespace v8;
using namespace node;
using namespace std;


#define THIS_ANALYSER_NODE                                                    \
	AnalyserNode *analyserNode = ObjectWrap::Unwrap<AnalyserNode>(info.This());

#define THIS_CHECK                                                            \
	if (analyserNode->_isDestroyed) return;

#define DES_CHECK                                                             \
	if (_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (analyserNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	analyserNode->CACHE = V;


Nan::Persistent<v8::Function> AnalyserNode::_constructor;


void AnalyserNode::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AnalyserNode"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
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
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	
	
	
	_constructor.Reset(ctor);
	Nan::Set(target, JS_STR("AnalyserNode"), ctor);
	
	
}


NAN_METHOD(AnalyserNode::newCtor) {
	
	CTOR_CHECK("AnalyserNode");
	
	REQ_OFFS_ARG(0, fftSize);
	
	AnalyserNode *analyserNode = new AnalyserNode(fftSize);
	analyserNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


AnalyserNode::AnalyserNode(size_t fftSize) {
	
	_isDestroyed = false;
	
	_fftSize = fftSize;
	
	_impl = new lab::AnalyserNode(_fftSize);
	
	
	
}


AnalyserNode::~AnalyserNode() {
	
	_destroy();
	
}


void AnalyserNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	delete _impl;
	_impl = NULL;
	
}



NAN_METHOD(AnalyserNode::destroy) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	analyserNode->_destroy();
	
}


NAN_METHOD(AnalyserNode::getFloatFrequencyData) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	REQ_OBJ_ARG(0, array);
	
	std::vector<float> arrayVec;
	
	if ( ! array->Has(JS_STR("length")) ) {
		return Nan::ThrowError("Argument should be array-like. Property 'length' is expected.");
	}
	
	int length = static_cast<int>(array->Get(JS_STR("length"))->NumberValue());
	for (int i = 0; i < length; i++) {
		arrayVec.push_back(static_cast<float>(array->Get(JS_INT(i))->NumberValue()));
	}
	
	analyserNode->_impl->getFloatFrequencyData(arrayVec);
	
}


NAN_METHOD(AnalyserNode::getByteFrequencyData) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	REQ_OBJ_ARG(0, array);
	
	std::vector<uint8_t> arrayVec;
	
	if ( ! array->Has(JS_STR("length")) ) {
		return Nan::ThrowError("Argument should be array-like. Property 'length' is expected.");
	}
	
	int length = static_cast<int>(array->Get(JS_STR("length"))->NumberValue());
	for (int i = 0; i < length; i++) {
		arrayVec.push_back(static_cast<uint8_t>(array->Get(JS_INT(i))->NumberValue()));
	}
	
	analyserNode->_impl->getByteFrequencyData(arrayVec);
	
}


NAN_METHOD(AnalyserNode::getFloatTimeDomainData) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	REQ_OBJ_ARG(0, array);
	
	std::vector<float> arrayVec;
	
	if ( ! array->Has(JS_STR("length")) ) {
		return Nan::ThrowError("Argument should be array-like. Property 'length' is expected.");
	}
	
	int length = static_cast<int>(array->Get(JS_STR("length"))->NumberValue());
	for (int i = 0; i < length; i++) {
		arrayVec.push_back(static_cast<float>(array->Get(JS_INT(i))->NumberValue()));
	}
	
	analyserNode->_impl->getFloatTimeDomainData(arrayVec);
	
}


NAN_METHOD(AnalyserNode::getByteTimeDomainData) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	REQ_OBJ_ARG(0, array);
	
	std::vector<uint8_t> arrayVec;
	
	if ( ! array->Has(JS_STR("length")) ) {
		return Nan::ThrowError("Argument should be array-like. Property 'length' is expected.");
	}
	
	int length = static_cast<int>(array->Get(JS_STR("length"))->NumberValue());
	for (int i = 0; i < length; i++) {
		arrayVec.push_back(static_cast<uint8_t>(array->Get(JS_INT(i))->NumberValue()));
	}
	
	analyserNode->_impl->getByteTimeDomainData(arrayVec);
	
}



NAN_GETTER(AnalyserNode::isDestroyedGetter) { THIS_ANALYSER_NODE;
	
	RET_VALUE(JS_BOOL(analyserNode->_isDestroyed));
	
}


NAN_GETTER(AnalyserNode::frequencyBinCountGetter) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_UINT32(analyserNode->_frequencyBinCount));
	
}



NAN_GETTER(AnalyserNode::fftSizeGetter) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OFFS(analyserNode->_fftSize));
	
}

NAN_SETTER(AnalyserNode::fftSizeSetter) { THIS_ANALYSER_NODE; THIS_CHECK; SETTER_UINT32_ARG;
	
	CACHE_CAS(_fftSize, v);
	
	delete analyserNode->_impl;
	analyserNode->_impl = new lab::AnalyserNode(analyserNode->_fftSize);
	
}


NAN_GETTER(AnalyserNode::minDecibelsGetter) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_DOUBLE(analyserNode->_minDecibels));
	
}

NAN_SETTER(AnalyserNode::minDecibelsSetter) { THIS_ANALYSER_NODE; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	CACHE_CAS(_minDecibels, v);
	
	analyserNode->_impl->setMinDecibels(analyserNode->_minDecibels);
	
}


NAN_GETTER(AnalyserNode::maxDecibelsGetter) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_DOUBLE(analyserNode->_maxDecibels));
	
}

NAN_SETTER(AnalyserNode::maxDecibelsSetter) { THIS_ANALYSER_NODE; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	CACHE_CAS(_maxDecibels, v);
	
	analyserNode->_impl->setMaxDecibels(analyserNode->_maxDecibels);
	
}


NAN_GETTER(AnalyserNode::smoothingTimeConstantGetter) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_DOUBLE(analyserNode->_smoothingTimeConstant));
	
}

NAN_SETTER(AnalyserNode::smoothingTimeConstantSetter) { THIS_ANALYSER_NODE; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	CACHE_CAS(_smoothingTimeConstant, v);
	
	analyserNode->_impl->setSmoothingTimeConstant(analyserNode->_maxDecibels);
	
}

