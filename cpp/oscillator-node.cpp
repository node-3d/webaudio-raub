#include <cstdlib>
//#include <iostream> // -> cout << "..." << endl;


#include <LabSound/core/OscillatorNode.h>

#include "oscillator-node.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_OSCILLATOR_NODE                                                    \
	OscillatorNode *oscillatorNode = Nan::ObjectWrap::Unwrap<OscillatorNode>(info.This());

#define THIS_CHECK                                                            \
	if (oscillatorNode->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (oscillatorNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	oscillatorNode->CACHE = V;


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
	
	_isDestroyed = true;
	
	AudioNode::_destroy();
	
}


// ------ Methods and props


NAN_METHOD(OscillatorNode::setPeriodicWave) { THIS_OSCILLATOR_NODE; THIS_CHECK;
	
	REQ_OBJ_ARG(0, periodicWave);
	
	// TODO: do something?
	
}


NAN_GETTER(OscillatorNode::typeGetter) { THIS_OSCILLATOR_NODE; THIS_CHECK;
	
	RET_VALUE(JS_UTF8(oscillatorNode->_type));
	
}

NAN_SETTER(OscillatorNode::typeSetter) { THIS_OSCILLATOR_NODE; THIS_CHECK; SETTER_UTF8_ARG;
	
	if (oscillatorNode->_type == *v) {
		return;
	}
	oscillatorNode->_type = *v;
	
	// TODO: may be additional actions on change?
	
	oscillatorNode->emit("type", 1, &value);
	
}


NAN_GETTER(OscillatorNode::frequencyGetter) { THIS_OSCILLATOR_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(oscillatorNode->_frequency));
	
}


NAN_GETTER(OscillatorNode::detuneGetter) { THIS_OSCILLATOR_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(oscillatorNode->_detune));
	
}


// ------ System methods and props for ObjectWrap

Nan::Persistent<FunctionTemplate> OscillatorNode::_protoOscillatorNode;
Nan::Persistent<Function> OscillatorNode::_ctorOscillatorNode;


void OscillatorNode::init(V8_VAR_OBJ target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);
	
	// class OscillatorNode inherits AudioNode
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
	
	oscillatorNode->_destroy();
	
}


NAN_GETTER(OscillatorNode::isDestroyedGetter) { THIS_OSCILLATOR_NODE;
	
	RET_VALUE(JS_BOOL(oscillatorNode->_isDestroyed));
	
}
