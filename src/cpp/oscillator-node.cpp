#include <cstdlib>

#include <LabSound/core/OscillatorNode.h>
#include <LabSound/core/Synthesis.h>

#include "oscillator-node.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_OSCILLATOR_NODE                                                  \
	OscillatorNode *oscillatorNode = Nan::ObjectWrap::Unwrap<OscillatorNode>(info.This());

#define THIS_CHECK                                                            \
	if (oscillatorNode->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (oscillatorNode->CACHE == V) {                                         \
		return;                                                               \
	}                                                                         \
	oscillatorNode->CACHE = V;


inline string fromOscillatorType(lab::OscillatorType mode) {
	if (mode == lab::OscillatorType::SINE) {
		return "sine";
	} else if (mode == lab::OscillatorType::SQUARE) {
		return "square";
	} else if (mode == lab::OscillatorType::SAWTOOTH) {
		return "sawtooth";
	} else if (mode == lab::OscillatorType::TRIANGLE) {
		return "triangle";
	} else {
		return "custom";
	}
}


inline lab::OscillatorType toOscillatorType(const string &mode) {
	if (mode == "sine") {
		return lab::OscillatorType::SINE;
	} else if (mode == "square") {
		return lab::OscillatorType::SQUARE;
	} else if (mode == "sawtooth") {
		return lab::OscillatorType::SAWTOOTH;
	} else if (mode == "triangle") {
		return lab::OscillatorType::TRIANGLE;
	} else {
		return lab::OscillatorType::CUSTOM;
	}
}


// ------ Constructor and Destructor

OscillatorNode::OscillatorNode(V8_VAR_OBJ context, float sampleRate) :
AudioScheduledSourceNode(
	context,
	shared_ptr<lab::AudioScheduledSourceNode>(new lab::OscillatorNode(sampleRate))
) {
	
	lab::OscillatorNode *node = static_cast<lab::OscillatorNode*>(_impl.get());
	
	_frequency.Reset(AudioParam::getNew(context, node->frequency()));
	_detune.Reset(AudioParam::getNew(context, node->detune()));
	
	_isDestroyed = false;
	
}


OscillatorNode::~OscillatorNode() {
	
	_destroy();
	
}


void OscillatorNode::_destroy() { DES_CHECK;
	
	_frequency.Reset();
	_detune.Reset();
	
	_isDestroyed = true;
	
	AudioNode::_destroy();
	
}


// ------ Methods and props


NAN_METHOD(OscillatorNode::setPeriodicWave) { THIS_OSCILLATOR_NODE; THIS_CHECK;
	
	REQ_OBJ_ARG(0, periodicWave);
	
	// TODO: do something?
	
}


NAN_GETTER(OscillatorNode::typeGetter) { THIS_OSCILLATOR_NODE; THIS_CHECK;
	
	lab::OscillatorNode *node = static_cast<lab::OscillatorNode*>(
		oscillatorNode->_impl.get()
	);
	
	RET_VALUE(JS_STR(fromOscillatorType(node->type())));
	
}


NAN_SETTER(OscillatorNode::typeSetter) { THIS_OSCILLATOR_NODE; THIS_CHECK; SETTER_UTF8_ARG;
	
	lab::OscillatorNode *node = static_cast<lab::OscillatorNode*>(
		oscillatorNode->_impl.get()
	);
	
	node->setType(toOscillatorType(*v));
	
	oscillatorNode->emit("type", 1, &value);
	
}


NAN_GETTER(OscillatorNode::frequencyGetter) { THIS_OSCILLATOR_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(oscillatorNode->_frequency));
	
}


NAN_GETTER(OscillatorNode::detuneGetter) { THIS_OSCILLATOR_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(oscillatorNode->_detune));
	
}


// ------ System methods and props for ObjectWrap

V8_STORE_FT OscillatorNode::_protoOscillatorNode;
V8_STORE_FUNC OscillatorNode::_ctorOscillatorNode;


void OscillatorNode::init(V8_VAR_OBJ target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);
	
	// class OscillatorNode inherits AudioScheduledSourceNode
	V8_VAR_FT parent = Nan::New(AudioScheduledSourceNode::_protoAudioScheduledSourceNode);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("OscillatorNode"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_RW(obj, type);
	ACCESSOR_R(obj, frequency);
	ACCESSOR_R(obj, detune);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	Nan::SetPrototypeMethod(proto, "setPeriodicWave", setPeriodicWave);
	
	// -------- static
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoOscillatorNode.Reset(proto);
	_ctorOscillatorNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("OscillatorNode"), ctor);
	
	
}


bool OscillatorNode::isOscillatorNode(V8_VAR_OBJ obj) {
	return Nan::New(_protoOscillatorNode)->HasInstance(obj);
}


V8_VAR_OBJ OscillatorNode::getNew(V8_VAR_OBJ context) {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorOscillatorNode);
	V8_VAR_VAL argv[] = { context };
	return Nan::NewInstance(ctor, 1, argv).ToLocalChecked();
	
}


NAN_METHOD(OscillatorNode::newCtor) {
	
	CTOR_CHECK("OscillatorNode");
	
	REQ_OBJ_ARG(0, context);
	
	AudioContext *audioContext = Nan::ObjectWrap::Unwrap<AudioContext>(context);
	
	OscillatorNode *oscillatorNode = new OscillatorNode(context, audioContext->getContext()->sampleRate());
	oscillatorNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(OscillatorNode::destroy) { THIS_OSCILLATOR_NODE; THIS_CHECK;
	
	oscillatorNode->emit("destroy");
	
	oscillatorNode->_destroy();
	
}


NAN_GETTER(OscillatorNode::isDestroyedGetter) { THIS_OSCILLATOR_NODE;
	
	RET_VALUE(JS_BOOL(oscillatorNode->_isDestroyed));
	
}
