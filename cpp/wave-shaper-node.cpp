#include <cstdlib>
#include <iostream>

#include "wave-shaper-node.hpp"

using namespace v8;
using namespace node;
using namespace std;


#define THIS_WAVE_SHAPER_NODE                                                    \
	WaveShaperNode *waveShaperNode = ObjectWrap::Unwrap<WaveShaperNode>(info.This());

#define THIS_CHECK                                                            \
	if (waveShaperNode->_isDestroyed) return;

#define DES_CHECK                                                             \
	if (_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (waveShaperNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	waveShaperNode->CACHE = V;


Nan::Persistent<v8::Function> WaveShaperNode::_constructor;


void WaveShaperNode::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("WaveShaperNode"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_RW(obj, curve);
	ACCESSOR_RW(obj, oversample);
	
	// -------- dynamic
	
	
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	
	
	
	_constructor.Reset(ctor);
	Nan::Set(target, JS_STR("WaveShaperNode"), ctor);
	
	
}


NAN_METHOD(WaveShaperNode::newCtor) {
	
	CTOR_CHECK("WaveShaperNode");
	
	WaveShaperNode *waveShaperNode = new WaveShaperNode();
	waveShaperNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


WaveShaperNode::WaveShaperNode() {
	
	_isDestroyed = false;
	
}


WaveShaperNode::~WaveShaperNode() {
	
	_destroy();
	
}


void WaveShaperNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	
	
}



NAN_METHOD(WaveShaperNode::destroy) { THIS_WAVE_SHAPER_NODE; THIS_CHECK;
	
	waveShaperNode->_destroy();
	
}




NAN_GETTER(WaveShaperNode::isDestroyedGetter) { THIS_WAVE_SHAPER_NODE;
	
	RET_VALUE(JS_BOOL(waveShaperNode->_isDestroyed));
	
}


NAN_GETTER(WaveShaperNode::curveGetter) { THIS_WAVE_SHAPER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(waveShaperNode->_curve));
	
}

NAN_SETTER(WaveShaperNode::curveSetter) { THIS_WAVE_SHAPER_NODE; THIS_CHECK; SETTER_OBJ_ARG;
	
	if (Nan::New(waveShaperNode->_curve) == v) {
		return;
	}
	waveShaperNode->_curve.Reset(v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(WaveShaperNode::oversampleGetter) { THIS_WAVE_SHAPER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_UTF8(waveShaperNode->_oversample));
	
}

NAN_SETTER(WaveShaperNode::oversampleSetter) { THIS_WAVE_SHAPER_NODE; THIS_CHECK; SETTER_UTF8_ARG;
	
	if (waveShaperNode->_oversample == *v) {
		return;
	}
	waveShaperNode->_oversample = *v;
	
	// TODO: may be additional actions on change?
	
}

