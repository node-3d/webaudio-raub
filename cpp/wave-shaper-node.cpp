#include <cstdlib>
//#include <iostream> // -> cout << "..." << endl;


#include "wave-shaper-node.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_WAVE_SHAPER_NODE                                                    \
	WaveShaperNode *waveShaperNode = Nan::ObjectWrap::Unwrap<WaveShaperNode>(info.This());

#define THIS_CHECK                                                            \
	if (waveShaperNode->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (waveShaperNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	waveShaperNode->CACHE = V;


// ------ Constructor and Destructor

WaveShaperNode::WaveShaperNode() : AudioNode() {
	
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



NAN_GETTER(WaveShaperNode::curveGetter) { THIS_WAVE_SHAPER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(waveShaperNode->_curve));
	
}

NAN_SETTER(WaveShaperNode::curveSetter) { THIS_WAVE_SHAPER_NODE; THIS_CHECK; SETTER_OBJ_ARG;
	
	if (Nan::New(waveShaperNode->_curve) == v) {
		return;
	}
	waveShaperNode->_curve.Reset(v);
	
	// TODO: may be additional actions on change?
	
	waveShaperNode->emit("curve", 1, &value);
	
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
	
	waveShaperNode->emit("oversample", 1, &value);
	
}


// ------ System methods and props for ObjectWrap

Nan::Persistent<FunctionTemplate> WaveShaperNode::_protoWaveShaperNode;
Nan::Persistent<Function> WaveShaperNode::_ctorWaveShaperNode;


void WaveShaperNode::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	// class WaveShaperNode inherits AudioNode
	Local<FunctionTemplate> parent = Nan::New(AudioNode::_protoAudioNode);
	proto->Inherit(parent);
	
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
	
	_protoWaveShaperNode.Reset(proto);
	_ctorWaveShaperNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("WaveShaperNode"), ctor);
	
	
}


Local<Object> WaveShaperNode::getNew() {
	
	Local<Function> ctor = Nan::New(_ctorWaveShaperNode);
	// Local<Value> argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


NAN_METHOD(WaveShaperNode::newCtor) {
	
	CTOR_CHECK("WaveShaperNode");
	
	WaveShaperNode *waveShaperNode = new WaveShaperNode();
	waveShaperNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(WaveShaperNode::destroy) { THIS_WAVE_SHAPER_NODE; THIS_CHECK;
	
	waveShaperNode->_destroy();
	
}


NAN_GETTER(WaveShaperNode::isDestroyedGetter) { THIS_WAVE_SHAPER_NODE;
	
	RET_VALUE(JS_BOOL(waveShaperNode->_isDestroyed));
	
}
