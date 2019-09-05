#include <LabSound/LabSound.h>

#include "oscillator-node.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"


IMPLEMENT_ES5_CLASS(OscillatorNode);

void OscillatorNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_SETTER(type);
	JS_ASSIGN_METHOD(setPeriodicWave);
	JS_ASSIGN_GETTER(detune);
	JS_ASSIGN_GETTER(frequency);
	JS_ASSIGN_METHOD(destroy);
	
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
CommonNode(info.This(), "OscillatorNode") { NAPI_ENV;
	
	REQ_OBJ_ARG(0, context);
	
	AudioContext *audioContext = Napi::ObjectWrap<AudioContext>::Unwrap(context);
	float sampleRate = audioContext->getCtx()->sampleRate();
	
	reset(context, std::make_shared<lab::OscillatorNode>(sampleRate));
	
	lab::OscillatorNode *node = static_cast<lab::OscillatorNode*>(
		_impl.get()
	);
	
	_frequency.Reset(AudioParam::create(env, context, node->frequency()));
	_detune.Reset(AudioParam::create(env, context, node->detune()));
	
	Napi::Value argv[] = {
		static_cast<Napi::Value>(context),
		static_cast<Napi::Value>(JS_NUM(reinterpret_cast<size_t>(&_impl)))
	};
	super(info, 2, argv);
	
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


JS_IMPLEMENT_METHOD(OscillatorNode, setPeriodicWave) { THIS_CHECK;
	
	REQ_OBJ_ARG(0, periodicWave);
	
	// TODO: do something?
	RET_UNDEFINED;
	
}


JS_IMPLEMENT_GETTER(OscillatorNode, type) { THIS_CHECK;
	
	lab::OscillatorNode *node = static_cast<lab::OscillatorNode*>(
		_impl.get()
	);
	
	RET_VALUE(JS_STR(fromOscillatorType(node->type())));
	
}


JS_IMPLEMENT_SETTER(OscillatorNode, type) { THIS_SETTER_CHECK; SETTER_STR_ARG;
	
	lab::OscillatorNode *node = static_cast<lab::OscillatorNode*>(
		_impl.get()
	);
	
	node->setType(toOscillatorType(v.c_str()));
	
	emit("type", 1, &value);
	
}


JS_IMPLEMENT_GETTER(OscillatorNode, frequency) { THIS_CHECK;
	
	RET_VALUE(_frequency.Value());
	
}


JS_IMPLEMENT_GETTER(OscillatorNode, detune) { THIS_CHECK;
	
	RET_VALUE(_detune.Value());
	
}


JS_IMPLEMENT_METHOD(OscillatorNode, destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	RET_UNDEFINED;
	
}
