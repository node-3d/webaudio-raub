#include <LabSound/core/OscillatorNode.h>
#include <LabSound/core/Synthesis.h>

#include "oscillator-node.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"

#include "common.hpp"


// ------ Aux macros


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

OscillatorNode::OscillatorNode(Napi::Object context, float sampleRate) :
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


JS_METHOD(OscillatorNode::setPeriodicWave) { THIS_CHECK;
	
	REQ_OBJ_ARG(0, periodicWave);
	
	// TODO: do something?
	
}


JS_GETTER(OscillatorNode::typeGetter) { THIS_CHECK;
	
	lab::OscillatorNode *node = static_cast<lab::OscillatorNode*>(
		_impl.get()
	);
	
	RET_VALUE(JS_STR(fromOscillatorType(node->type())));
	
}


JS_SETTER(OscillatorNode::typeSetter) { THIS_CHECK; SETTER_UTF8_ARG;
	
	lab::OscillatorNode *node = static_cast<lab::OscillatorNode*>(
		_impl.get()
	);
	
	node->setType(toOscillatorType(*v));
	
	emit("type", 1, &value);
	
}


JS_GETTER(OscillatorNode::frequencyGetter) { THIS_CHECK;
	
	RET_VALUE(__frequency.Value());
	
}


JS_GETTER(OscillatorNode::detuneGetter) { THIS_CHECK;
	
	RET_VALUE(__detune.Value());
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference OscillatorNode::_ctorOscillatorNode;


void OscillatorNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "OscillatorNode", {
		ACCESSOR_RW(OscillatorNode, type),
		ACCESSOR_M(OscillatorNode, setPeriodicWave),
		ACCESSOR_M(OscillatorNode, destroy),
		ACCESSOR_R(OscillatorNode, detune),
		ACCESSOR_R(OscillatorNode, frequency),
		ACCESSOR_R(OscillatorNode, isDestroyed),
	
	});
	
	_ctorOscillatorNode = Napi::Persistent(ctor);
	_ctorOscillatorNode.SuppressDestruct();
	
	exports.Set("OscillatorNode", ctor);
	
}


bool OscillatorNode::isOscillatorNode(Napi::Object obj) {
	return obj.InstanceOf(_ctorOscillatorNode.Value());
}


Napi::Object OscillatorNode::getNew(Napi::Object context) {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorOscillatorNode);
	V8_VAR_VAL argv[] = { context };
	return Nan::NewInstance(ctor, 1, argv).ToLocalChecked();
	
}


OscillatorNode::OscillatorNode(const Napi::CallbackInfo &info): Napi::ObjectWrap<OscillatorNode>(info) {
	
	CTOR_CHECK("OscillatorNode");
	
	REQ_OBJ_ARG(0, context);
	
	AudioContext *audioContext = Nan::ObjectWrap::Unwrap<AudioContext>(context);
	
	OscillatorNode *oscillatorNode = new OscillatorNode(context, audioContext->getContext()->sampleRate());
	
}


JS_METHOD(OscillatorNode::destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	
}


JS_GETTER(OscillatorNode::isDestroyedGetter) {
	
	RET_BOOL(_isDestroyed);
	
}
