#include <cstdlib>
#include <iostream>

#include "analyser-node.hpp"

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
	
	
	// -------- dynamic
	
	
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	
	
	
	_constructor.Reset(ctor);
	Nan::Set(target, JS_STR("AnalyserNode"), ctor);
	
	
}


NAN_METHOD(AnalyserNode::newCtor) {
	
	CTOR_CHECK("AnalyserNode");
	
	AnalyserNode *analyserNode = new AnalyserNode();
	analyserNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


AnalyserNode::AnalyserNode() {
	
	_isDestroyed = false;
	
}


AnalyserNode::~AnalyserNode() {
	
	_destroy();
	
}


void AnalyserNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	
	
}



NAN_METHOD(AnalyserNode::destroy) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	analyserNode->_destroy();
	
}


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



NAN_GETTER(AnalyserNode::isDestroyedGetter) { THIS_ANALYSER_NODE;
	
	RET_VALUE(JS_BOOL(analyserNode->_isDestroyed));
	
}


NAN_GETTER(AnalyserNode::frequencyBinCountGetter) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_UINT32(analyserNode->_frequencyBinCount));
	
}

NAN_SETTER(AnalyserNode::frequencyBinCountSetter) { THIS_ANALYSER_NODE; THIS_CHECK; SETTER_UINT32_ARG;
	
	CACHE_CAS(_frequencyBinCount, v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(AnalyserNode::fftSizeGetter) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_UINT32(analyserNode->_fftSize));
	
}

NAN_SETTER(AnalyserNode::fftSizeSetter) { THIS_ANALYSER_NODE; THIS_CHECK; SETTER_UINT32_ARG;
	
	CACHE_CAS(_fftSize, v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(AnalyserNode::minDecibelsGetter) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_DOUBLE(analyserNode->_minDecibels));
	
}

NAN_SETTER(AnalyserNode::minDecibelsSetter) { THIS_ANALYSER_NODE; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	CACHE_CAS(_minDecibels, v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(AnalyserNode::maxDecibelsGetter) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_DOUBLE(analyserNode->_maxDecibels));
	
}

NAN_SETTER(AnalyserNode::maxDecibelsSetter) { THIS_ANALYSER_NODE; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	CACHE_CAS(_maxDecibels, v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(AnalyserNode::smoothingTimeConstantGetter) { THIS_ANALYSER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_DOUBLE(analyserNode->_smoothingTimeConstant));
	
}

NAN_SETTER(AnalyserNode::smoothingTimeConstantSetter) { THIS_ANALYSER_NODE; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	CACHE_CAS(_smoothingTimeConstant, v);
	
	// TODO: may be additional actions on change?
	
}

