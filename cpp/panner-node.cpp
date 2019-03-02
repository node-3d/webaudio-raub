#include <cstdlib>

#include <LabSound/core/AudioNode.h>
#include <LabSound/core/PannerNode.h>
#include <LabSound/core/FloatPoint3D.h>

#include "panner-node.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_PANNER_NODE                                                      \
	PannerNode *pannerNode = Nan::ObjectWrap::Unwrap<PannerNode>(info.This());

#define THIS_CHECK                                                            \
	if (pannerNode->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (pannerNode->CACHE == V) {                                             \
		return;                                                               \
	}                                                                         \
	pannerNode->CACHE = V;

#define PARAM_GETTER(NAME)                                                    \
NAN_GETTER(PannerNode::NAME ## Getter) { THIS_PANNER_NODE; THIS_CHECK;        \
	RET_VALUE(JS_OBJ(pannerNode->_ ## NAME));                                 \
}


inline string fromDistanceModel(uint16 mode) {
	if (mode == lab::PannerNode::LINEAR_DISTANCE) {
		return "linear";
	} else if (mode == lab::PannerNode::INVERSE_DISTANCE) {
		return "inverse";
	} else {
		return "exponential";
	}
}


inline uint16 toDistanceModel(const string &mode) {
	if (mode == "linear") {
		return lab::PannerNode::LINEAR_DISTANCE;
	} else if (mode == "inverse") {
		return lab::PannerNode::INVERSE_DISTANCE;
	} else {
		return lab::PannerNode::EXPONENTIAL_DISTANCE;
	}
}


inline string fromPanningMode(lab::PanningMode mode) {
	if (mode == lab::PanningMode::EQUALPOWER) {
		return "equalpower";
	} else {
		return "HRTF";
	}
}


inline lab::PanningMode toPanningMode(const string &mode) {
	if (mode == "equalpower") {
		return lab::PanningMode::EQUALPOWER;
	} else {
		return lab::PanningMode::HRTF;
	}
}


// ------ Constructor and Destructor

PannerNode::PannerNode(V8_VAR_OBJ context, float sampleRate, const string &hrtf) :
AudioNode(context, NodePtr(new lab::PannerNode(sampleRate, hrtf))) {
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(_impl.get());
	
	_positionX.Reset(AudioParam::getNew(context, node->positionX()));
	_positionY.Reset(AudioParam::getNew(context, node->positionY()));
	_positionZ.Reset(AudioParam::getNew(context, node->positionZ()));
	_orientationX.Reset(AudioParam::getNew(context, node->forwardX()));
	_orientationY.Reset(AudioParam::getNew(context, node->forwardY()));
	_orientationZ.Reset(AudioParam::getNew(context, node->forwardZ()));
	
	_isDestroyed = false;
	
}


PannerNode::~PannerNode() {
	
	_destroy();
	
}


void PannerNode::_destroy() { DES_CHECK;
	
	_positionX.Reset();
	_positionY.Reset();
	_positionZ.Reset();
	_orientationX.Reset();
	_orientationY.Reset();
	_orientationZ.Reset();
	
	_isDestroyed = true;
	
	AudioNode::_destroy();
	
}


// ------ Methods and props


NAN_METHOD(PannerNode::setPosition) { THIS_PANNER_NODE; THIS_CHECK;
	
	REQ_FLOAT_ARG(0, x);
	REQ_FLOAT_ARG(1, y);
	REQ_FLOAT_ARG(2, z);
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		pannerNode->_impl.get()
	);
	
	node->setPosition(x, y, z);
	
}


NAN_METHOD(PannerNode::setOrientation) { THIS_PANNER_NODE; THIS_CHECK;
	
	REQ_FLOAT_ARG(0, x);
	REQ_FLOAT_ARG(1, y);
	REQ_FLOAT_ARG(2, z);
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		pannerNode->_impl.get()
	);
	
	node->setForward(lab::FloatPoint3D(x, y, z));
	
}


NAN_METHOD(PannerNode::setVelocity) { THIS_PANNER_NODE; THIS_CHECK;
	
	REQ_FLOAT_ARG(0, x);
	REQ_FLOAT_ARG(1, y);
	REQ_FLOAT_ARG(2, z);
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		pannerNode->_impl.get()
	);
	
	node->setVelocity(x, y, z);
	
}

NAN_GETTER(PannerNode::panningModelGetter) { THIS_PANNER_NODE; THIS_CHECK;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		pannerNode->_impl.get()
	);
	
	RET_VALUE(JS_STR(fromPanningMode(node->panningModel())));
	
}

NAN_SETTER(PannerNode::panningModelSetter) { THIS_PANNER_NODE; THIS_CHECK; SETTER_UTF8_ARG;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		pannerNode->_impl.get()
	);
	
	node->setPanningModel(toPanningMode(*v));
	
	pannerNode->emit("panningModel", 1, &value);
	
}


PARAM_GETTER(positionX);
PARAM_GETTER(positionY);
PARAM_GETTER(positionZ);
PARAM_GETTER(orientationX);
PARAM_GETTER(orientationY);
PARAM_GETTER(orientationZ);


NAN_GETTER(PannerNode::distanceModelGetter) { THIS_PANNER_NODE; THIS_CHECK;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		pannerNode->_impl.get()
	);
	
	RET_VALUE(JS_STR(fromDistanceModel(node->distanceModel())));
	
}

NAN_SETTER(PannerNode::distanceModelSetter) { THIS_PANNER_NODE; THIS_CHECK; SETTER_UTF8_ARG;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		pannerNode->_impl.get()
	);
	
	node->setDistanceModel(toDistanceModel(*v));
	
	pannerNode->emit("distanceModel", 1, &value);
	
}


NAN_GETTER(PannerNode::refDistanceGetter) { THIS_PANNER_NODE; THIS_CHECK;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		pannerNode->_impl.get()
	);
	
	RET_VALUE(JS_DOUBLE(node->refDistance()));
	
}

NAN_SETTER(PannerNode::refDistanceSetter) { THIS_PANNER_NODE; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		pannerNode->_impl.get()
	);
	
	node->setRefDistance(static_cast<float>(v));
	
	pannerNode->emit("refDistance", 1, &value);
	
}


NAN_GETTER(PannerNode::maxDistanceGetter) { THIS_PANNER_NODE; THIS_CHECK;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		pannerNode->_impl.get()
	);
	
	RET_VALUE(JS_DOUBLE(node->maxDistance()));
	
}

NAN_SETTER(PannerNode::maxDistanceSetter) { THIS_PANNER_NODE; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		pannerNode->_impl.get()
	);
	
	node->setMaxDistance(static_cast<float>(v));
	
	pannerNode->emit("maxDistance", 1, &value);
	
}


NAN_GETTER(PannerNode::rolloffFactorGetter) { THIS_PANNER_NODE; THIS_CHECK;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		pannerNode->_impl.get()
	);
	
	RET_VALUE(JS_DOUBLE(node->rolloffFactor()));
	
}

NAN_SETTER(PannerNode::rolloffFactorSetter) { THIS_PANNER_NODE; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		pannerNode->_impl.get()
	);
	
	node->setRolloffFactor(static_cast<float>(v));
	
	pannerNode->emit("rolloffFactor", 1, &value);
	
}


NAN_GETTER(PannerNode::coneInnerAngleGetter) { THIS_PANNER_NODE; THIS_CHECK;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		pannerNode->_impl.get()
	);
	
	RET_VALUE(JS_DOUBLE(node->coneInnerAngle()));
	
}

NAN_SETTER(PannerNode::coneInnerAngleSetter) { THIS_PANNER_NODE; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		pannerNode->_impl.get()
	);
	
	node->setConeInnerAngle(static_cast<float>(v));
	
	pannerNode->emit("coneInnerAngle", 1, &value);
	
}


NAN_GETTER(PannerNode::coneOuterAngleGetter) { THIS_PANNER_NODE; THIS_CHECK;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		pannerNode->_impl.get()
	);
	
	RET_VALUE(JS_DOUBLE(node->coneOuterAngle()));
	
}

NAN_SETTER(PannerNode::coneOuterAngleSetter) { THIS_PANNER_NODE; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		pannerNode->_impl.get()
	);
	
	node->setConeOuterAngle(static_cast<float>(v));
	
	pannerNode->emit("coneOuterAngle", 1, &value);
	
}


NAN_GETTER(PannerNode::coneOuterGainGetter) { THIS_PANNER_NODE; THIS_CHECK;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		pannerNode->_impl.get()
	);
	
	RET_VALUE(JS_DOUBLE(node->coneOuterGain()));
	
}

NAN_SETTER(PannerNode::coneOuterGainSetter) { THIS_PANNER_NODE; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		pannerNode->_impl.get()
	);
	
	node->setConeOuterGain(static_cast<float>(v));
	
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
	Nan::SetPrototypeMethod(proto, "setVelocity", setVelocity);
	
	// -------- static
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoPannerNode.Reset(proto);
	_ctorPannerNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("PannerNode"), ctor);
	
	
}


bool PannerNode::isPannerNode(V8_VAR_OBJ obj) {
	return Nan::New(_protoPannerNode)->HasInstance(obj);
}


V8_VAR_OBJ PannerNode::getNew(V8_VAR_OBJ context) {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorPannerNode);
	V8_VAR_VAL argv[] = { context };
	return Nan::NewInstance(ctor, 1, argv).ToLocalChecked();
	
}


NAN_METHOD(PannerNode::newCtor) {
	
	CTOR_CHECK("PannerNode");
		
	REQ_OBJ_ARG(0, context);
	
	AudioContext *audioContext = Nan::ObjectWrap::Unwrap<AudioContext>(context);
	
	Nan::Utf8String hrtf(V8_VAR_OBJ::Cast(Nan::New(_ctorPannerNode))->Get(JS_STR("hrtf")));
	PannerNode *pannerNode = new PannerNode(context, audioContext->getContext()->sampleRate(), *hrtf);
	pannerNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(PannerNode::destroy) { THIS_PANNER_NODE; THIS_CHECK;
	
	pannerNode->emit("destroy");
	
	pannerNode->_destroy();
	
}


NAN_GETTER(PannerNode::isDestroyedGetter) { THIS_PANNER_NODE;
	
	RET_VALUE(JS_BOOL(pannerNode->_isDestroyed));
	
}
