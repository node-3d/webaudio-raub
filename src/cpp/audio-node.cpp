#include <LabSound/LabSound.h>

#include "audio-node.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"

#include "common.hpp"


IMPLEMENT_ES5_CLASS(AudioNode);

void AudioNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_SETTER(channelInterpretation);
	JS_ASSIGN_SETTER(channelCountMode);
	JS_ASSIGN_SETTER(channelCount);
	JS_ASSIGN_METHOD(disconnect);
	JS_ASSIGN_METHOD(connect);
	JS_ASSIGN_GETTER(numberOfOutputs);
	JS_ASSIGN_GETTER(numberOfInputs);
	JS_ASSIGN_GETTER(context);
	JS_ASSIGN_METHOD(destroy);
	
	exports.Set("AudioNode", ctor);
	
}


bool AudioNode::isAudioNode(Napi::Object obj) {
	return obj.InstanceOf(_ctorEs5.Value());
}


inline std::string fromChannelCountMode(lab::ChannelCountMode mode) {
	if (mode == lab::ChannelCountMode::ClampedMax) {
		return "clamped-max";
	} else if (mode == lab::ChannelCountMode::Explicit) {
		return "explicit";
	} else {
		return "max";
	}
}


inline lab::ChannelCountMode toChannelCountMode(const std::string &mode) {
	if (mode == "clamped-max") {
		return lab::ChannelCountMode::ClampedMax;
	} else if (mode == "explicit") {
		return lab::ChannelCountMode::Explicit;
	} else {
		return lab::ChannelCountMode::Max;
	}
}


inline std::string fromChannelInterpretation(lab::ChannelInterpretation io) {
	if (io == lab::ChannelInterpretation::Discrete) {
		return "discrete";
	} else {
		return "speakers";
	}
}


inline lab::ChannelInterpretation toChannelInterpretation(const std::string &io) {
	if (io == "discrete") {
		return lab::ChannelInterpretation::Discrete;
	} else {
		return lab::ChannelInterpretation::Speakers;
	}
}


AudioNode::AudioNode(const Napi::CallbackInfo &info):
CommonNode(info.This(), "AudioNode") { NAPI_ENV;
	super(info);
	
	REQ_OBJ_ARG(0, context);
	REQ_EXT_ARG(1, extNode);
	
	NodePtr *ext = reinterpret_cast<NodePtr *>(extNode.Data());
	
	reset(context, *ext);
	
	_channelCount = _impl->channelCount();
	_channelCountMode = fromChannelCountMode(_impl->channelCountMode());
	_channelInterpretation = fromChannelInterpretation(_impl->channelInterpretation());
	
}


AudioNode::~AudioNode() {
	_destroy();
}


void AudioNode::_destroy() { DES_CHECK;
	CommonNode::_destroy();
}


// node2 node1.connect(node2);
// node2 node1.connect(node2, output);
// node2 node1.connect(node2, output, input);
// undefined node1.connect(param);
// undefined node1.connect(param, output);
JS_IMPLEMENT_METHOD(AudioNode, connect) { THIS_CHECK;
	
	REQ_OBJ_ARG(0, destination);
	
	Napi::Object context = _context.Value();
	AudioContext *audioContext = Napi::ObjectWrap<AudioContext>::Unwrap(context);
	
	lab::AudioContext *ctx = audioContext->getCtx().get();
	
	if (isAudioNode(destination)) {
		
		LET_INT32_ARG(1, output);
		LET_INT32_ARG(2, input);
		
		AudioNode *destNode = Napi::ObjectWrap<AudioNode>::Unwrap(destination);
		
		ctx->connect(_impl, _impl, input, output);
		
	} else if (AudioParam::isAudioParam(destination)) {
		
		LET_INT32_ARG(1, output);
		
		AudioParam *destParam = Napi::ObjectWrap<AudioParam>::Unwrap(destination);
		
		ctx->connectParam(destParam->getParam(), _impl, output);
		
	}
	
	RET_UNDEFINED;
	
}


// undefined node1.disconnect();
// undefined node1.disconnect(node2);
// undefined node1.disconnect(node2, output);
// undefined node1.disconnect(node2, output, input);
JS_IMPLEMENT_METHOD(AudioNode, disconnect) { THIS_CHECK;
	
	int output = 0;
	int input = 0;
	Napi::Object destination;
	
	Napi::Object context = _context.Value();
	AudioContext *audioContext = Napi::ObjectWrap<AudioContext>::Unwrap(context);
	lab::AudioContext *ctx = audioContext->getCtx().get();
	
	if (info.Length() == 1) {
		
		if (info[0].IsObject()) {
			
			REQ_OBJ_ARG(0, destArg);
			
		} else if (info[0].IsNumber()) {
			
			REQ_INT_ARG(0, outputArg);
			output = outputArg;
			
		}
		
	} else if (info.Length() == 2) {
		
		REQ_OBJ_ARG(0, destArg);
		REQ_INT_ARG(1, outputArg);
		
		destination = destArg;
		output = outputArg;
		
	} else if (info.Length() == 3) {
		
		REQ_OBJ_ARG(0, destArg);
		REQ_INT_ARG(1, outputArg);
		REQ_INT_ARG(2, inputArg);
		
		destination = destArg;
		output = outputArg;
		input = inputArg;
		
	} else {
		
		// Disconnect self
		ctx->disconnect(_impl, NodePtr(), input, output);
		RET_UNDEFINED;
		
	}
	
	if (isAudioNode(destination)) {
		
		AudioNode *destNode = Napi::ObjectWrap<AudioNode>::Unwrap(destination);
		ctx->disconnect(_impl, _impl, input, output);
		
	} else if (AudioParam::isAudioParam(destination)) {
		
		AudioParam *destParam = Napi::ObjectWrap<AudioParam>::Unwrap(destination);
		
		ParamPtr param = destParam->getParam();
		
		lab::ContextGraphLock graphLock(ctx, "AudioNode::disconnect");
		// TODO:
		// param->disconnect(graphLock, param, _impl);
		
	}
	
	RET_UNDEFINED;
	
}


JS_IMPLEMENT_GETTER(AudioNode, context) { THIS_CHECK;
	
	RET_VALUE(_context.Value());
	
}


JS_IMPLEMENT_GETTER(AudioNode, numberOfInputs) { THIS_CHECK;
	
	RET_NUM(static_cast<uint32_t>(_impl->numberOfInputs()));
	
}


JS_IMPLEMENT_GETTER(AudioNode, numberOfOutputs) { THIS_CHECK;
	
	RET_NUM(static_cast<uint32_t>(_impl->numberOfOutputs()));
	
}


JS_IMPLEMENT_GETTER(AudioNode, channelCount) { THIS_CHECK;
	
	RET_NUM(static_cast<uint32_t>(_impl->channelCount()));
	
}


JS_IMPLEMENT_SETTER(AudioNode, channelCount) { THIS_SETTER_CHECK; SETTER_UINT32_ARG;
	
	CACHE_CAS(_channelCount, v);
	
	Napi::Object context = _context.Value();
	AudioContext *audioContext = Napi::ObjectWrap<AudioContext>::Unwrap(context);
	
	lab::ContextGraphLock graphLock(audioContext->getCtx().get(), "AudioNode::channelCountSetter");
	_impl->setChannelCount(graphLock, _channelCount);
	
	emit("channelCount", 1, &value);
	
}


JS_IMPLEMENT_GETTER(AudioNode, channelCountMode) { THIS_CHECK;
	
	RET_STR(_channelCountMode);
	
}

JS_IMPLEMENT_SETTER(AudioNode, channelCountMode) { THIS_SETTER_CHECK; SETTER_STR_ARG;
	
	if (_channelCountMode == v) {
		return;
	}
	_channelCountMode = v;
	
	// TODO: may be additional actions on change?
	
	emit("channelCountMode", 1, &value);
	
}


JS_IMPLEMENT_GETTER(AudioNode, channelInterpretation) { THIS_CHECK;
	
	RET_STR(_channelInterpretation);
	
}

JS_IMPLEMENT_SETTER(AudioNode, channelInterpretation) { THIS_SETTER_CHECK; SETTER_STR_ARG;
	
	if (_channelInterpretation == v) {
		return;
	}
	_channelInterpretation = v;
	
	// TODO: may be additional actions on change?
	
	emit("channelInterpretation", 1, &value);
	
}


JS_IMPLEMENT_METHOD(AudioNode, destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	RET_UNDEFINED;
	
}
