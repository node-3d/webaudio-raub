#include <cstdlib>
//#include <iostream> // -> cout << "..." << endl;


#include "panner-node.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_PANNER_NODE                                                    \
	PannerNode *pannerNode = Nan::ObjectWrap::Unwrap<PannerNode>(info.This());

#define THIS_CHECK                                                            \
	if (pannerNode->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (pannerNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	pannerNode->CACHE = V;


// ------ Constructor and Destructor

PannerNode::PannerNode() : AudioNode() {
	
	_isDestroyed = false;
	
}


PannerNode::~PannerNode() {
	
	_destroy();
	
}


void PannerNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	AudioNode::_destroy();
	
}


// ------ Methods and props


NAN_METHOD(PannerNode::setPosition) { THIS_PANNER_NODE; THIS_CHECK;
	
	REQ_FLOAT_ARG(0, x);
	REQ_FLOAT_ARG(1, y);
	REQ_FLOAT_ARG(2, z);
	
	// TODO: do something?
	
}


NAN_METHOD(PannerNode::setOrientation) { THIS_PANNER_NODE; THIS_CHECK;
	
	REQ_FLOAT_ARG(0, x);
	REQ_FLOAT_ARG(1, y);
	REQ_FLOAT_ARG(2, z);
	
	// TODO: do something?
	
}


NAN_GETTER(PannerNode::panningModelGetter) { THIS_PANNER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_UTF8(pannerNode->_panningModel));
	
}

NAN_SETTER(PannerNode::panningModelSetter) { THIS_PANNER_NODE; THIS_CHECK; SETTER_UTF8_ARG;
	
	if (pannerNode->_panningModel == *v) {
		return;
	}
	pannerNode->_panningModel = *v;
	
	// TODO: may be additional actions on change?
	
	pannerNode->emit("panningModel", 1, &value);
	
}


NAN_GETTER(PannerNode::positionXGetter) { THIS_PANNER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(pannerNode->_positionX));
	
}


NAN_GETTER(PannerNode::positionYGetter) { THIS_PANNER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(pannerNode->_positionY));
	
}


NAN_GETTER(PannerNode::positionZGetter) { THIS_PANNER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(pannerNode->_positionZ));
	
}


NAN_GETTER(PannerNode::orientationXGetter) { THIS_PANNER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(pannerNode->_orientationX));
	
}


NAN_GETTER(PannerNode::orientationYGetter) { THIS_PANNER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(pannerNode->_orientationY));
	
}


NAN_GETTER(PannerNode::orientationZGetter) { THIS_PANNER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(pannerNode->_orientationZ));
	
}


NAN_GETTER(PannerNode::distanceModelGetter) { THIS_PANNER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_UTF8(pannerNode->_distanceModel));
	
}

NAN_SETTER(PannerNode::distanceModelSetter) { THIS_PANNER_NODE; THIS_CHECK; SETTER_UTF8_ARG;
	
	if (pannerNode->_distanceModel == *v) {
		return;
	}
	pannerNode->_distanceModel = *v;
	
	// TODO: may be additional actions on change?
	
	pannerNode->emit("distanceModel", 1, &value);
	
}


NAN_GETTER(PannerNode::refDistanceGetter) { THIS_PANNER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_DOUBLE(pannerNode->_refDistance));
	
}

NAN_SETTER(PannerNode::refDistanceSetter) { THIS_PANNER_NODE; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	CACHE_CAS(_refDistance, v);
	
	// TODO: may be additional actions on change?
	
	pannerNode->emit("refDistance", 1, &value);
	
}


NAN_GETTER(PannerNode::maxDistanceGetter) { THIS_PANNER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_DOUBLE(pannerNode->_maxDistance));
	
}

NAN_SETTER(PannerNode::maxDistanceSetter) { THIS_PANNER_NODE; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	CACHE_CAS(_maxDistance, v);
	
	// TODO: may be additional actions on change?
	
	pannerNode->emit("maxDistance", 1, &value);
	
}


NAN_GETTER(PannerNode::rolloffFactorGetter) { THIS_PANNER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_DOUBLE(pannerNode->_rolloffFactor));
	
}

NAN_SETTER(PannerNode::rolloffFactorSetter) { THIS_PANNER_NODE; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	CACHE_CAS(_rolloffFactor, v);
	
	// TODO: may be additional actions on change?
	
	pannerNode->emit("rolloffFactor", 1, &value);
	
}


NAN_GETTER(PannerNode::coneInnerAngleGetter) { THIS_PANNER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_DOUBLE(pannerNode->_coneInnerAngle));
	
}

NAN_SETTER(PannerNode::coneInnerAngleSetter) { THIS_PANNER_NODE; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	CACHE_CAS(_coneInnerAngle, v);
	
	// TODO: may be additional actions on change?
	
	pannerNode->emit("coneInnerAngle", 1, &value);
	
}


NAN_GETTER(PannerNode::coneOuterAngleGetter) { THIS_PANNER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_DOUBLE(pannerNode->_coneOuterAngle));
	
}

NAN_SETTER(PannerNode::coneOuterAngleSetter) { THIS_PANNER_NODE; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	CACHE_CAS(_coneOuterAngle, v);
	
	// TODO: may be additional actions on change?
	
	pannerNode->emit("coneOuterAngle", 1, &value);
	
}


NAN_GETTER(PannerNode::coneOuterGainGetter) { THIS_PANNER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_DOUBLE(pannerNode->_coneOuterGain));
	
}

NAN_SETTER(PannerNode::coneOuterGainSetter) { THIS_PANNER_NODE; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	CACHE_CAS(_coneOuterGain, v);
	
	// TODO: may be additional actions on change?
	
	pannerNode->emit("coneOuterGain", 1, &value);
	
}


// ------ System methods and props for ObjectWrap

V8_STORE_FT PannerNode::_protoPannerNode;
V8_STORE_FUNC PannerNode::_ctorPannerNode;


void PannerNode::init(V8_VAR_OBJ target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);
	
	// class PannerNode inherits AudioNode
	V8_VAR_FT parent = Nan::New(AudioNode::_protoAudioNode);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("PannerNode"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_RW(obj, panningModel);
	ACCESSOR_R(obj, positionX);
	ACCESSOR_R(obj, positionY);
	ACCESSOR_R(obj, positionZ);
	ACCESSOR_R(obj, orientationX);
	ACCESSOR_R(obj, orientationY);
	ACCESSOR_R(obj, orientationZ);
	ACCESSOR_RW(obj, distanceModel);
	ACCESSOR_RW(obj, refDistance);
	ACCESSOR_RW(obj, maxDistance);
	ACCESSOR_RW(obj, rolloffFactor);
	ACCESSOR_RW(obj, coneInnerAngle);
	ACCESSOR_RW(obj, coneOuterAngle);
	ACCESSOR_RW(obj, coneOuterGain);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	Nan::SetPrototypeMethod(proto, "setPosition", setPosition);
	Nan::SetPrototypeMethod(proto, "setOrientation", setOrientation);
	
	// -------- static
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoPannerNode.Reset(proto);
	_ctorPannerNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("PannerNode"), ctor);
	
	
}


V8_VAR_OBJ PannerNode::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorPannerNode);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


NAN_METHOD(PannerNode::newCtor) {
	
	CTOR_CHECK("PannerNode");
	
	PannerNode *pannerNode = new PannerNode();
	pannerNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(PannerNode::destroy) { THIS_PANNER_NODE; THIS_CHECK;
	
	pannerNode->_destroy();
	
}


NAN_GETTER(PannerNode::isDestroyedGetter) { THIS_PANNER_NODE;
	
	RET_VALUE(JS_BOOL(pannerNode->_isDestroyed));
	
}
