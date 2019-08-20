#include <LabSound/LabSound.h>

#include "oscillator-node.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"


Napi::FunctionReference OscillatorNode::_constructor;

void OscillatorNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "OscillatorNode", {
		ACCESSOR_RW(OscillatorNode, type),
		ACCESSOR_M(OscillatorNode, setPeriodicWave),
		ACCESSOR_R(OscillatorNode, detune),
		ACCESSOR_R(OscillatorNode, frequency),
		ACCESSOR_M(OscillatorNode, destroy)
	});
	
	_constructor = Napi::Persistent(ctor);
	_constructor.SuppressDestruct();
	
	exports.Set("OscillatorNode", ctor);
	
}


inline std::string fromOscillatorType(lab::OscillatorType mode) {
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


inline lab::OscillatorType toOscillatorType(const std::string &mode) {
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


OscillatorNode::OscillatorNode(const Napi::CallbackInfo &info):
Napi::ObjectWrap<OscillatorNode>(info),
CommonNode(info.Env(), "OscillatorNode") { NAPI_ENV;
	
	CTOR_CHECK("OscillatorNode");
	
	REQ_OBJ_ARG(0, context);
	
	AudioContext *audioContext = Napi::ObjectWrap<AudioContext>::Unwrap(context);
	float sampleRate = audioContext->getCtx()->sampleRate();
	Napi::Object that = info.This().As<Napi::Object>();
	Napi::Function ctor = _constructor.Value().As<Napi::Function>();
	Napi::Function _Super = ctor.Get("_Super").As<Napi::Function>();
	
	reset(context, std::make_shared<lab::OscillatorNode>(sampleRate));
	
	std::vector<napi_value> args;
	args.push_back(context);
	_Super.Call(that, args);
	
	lab::OscillatorNode *node = static_cast<lab::OscillatorNode*>(
		_impl.get()
	);
	
	_frequency.Reset(AudioParam::create(env, context, node->frequency()));
	_detune.Reset(AudioParam::create(env, context, node->detune()));
	
}


OscillatorNode::~OscillatorNode() {
	_destroy();
	
}


void OscillatorNode::_destroy() { DES_CHECK;
	
	_frequency.Reset();
	_detune.Reset();
	
	CommonNode::_destroy();
	
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


JS_SETTER(OscillatorNode::typeSetter) { THIS_SETTER_CHECK; SETTER_STR_ARG;
	
	lab::OscillatorNode *node = static_cast<lab::OscillatorNode*>(
		_impl.get()
	);
	
	node->setType(toOscillatorType(v.c_str()));
	
	emit(info, "type", 1, &value);
	
}


JS_GETTER(OscillatorNode::frequencyGetter) { THIS_CHECK;
	
	RET_VALUE(_frequency.Value());
	
}


JS_GETTER(OscillatorNode::detuneGetter) { THIS_CHECK;
	
	RET_VALUE(_detune.Value());
	
}
