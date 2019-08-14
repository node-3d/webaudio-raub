#include <LabSound/core/AudioContext.h>
#include <LabSound/core/AudioNode.h>
#include <LabSound/core/AudioParam.h>
#include <LabSound/extended/AudioContextLock.h>

#include "audio-node.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"

#include "common.hpp"


// ------ Aux macros


inline string fromChannelCountMode(lab::ChannelCountMode mode) {
	if (mode == lab::ChannelCountMode::ClampedMax) {
		return "clamped-max";
	} else if (mode == lab::ChannelCountMode::Explicit) {
		return "explicit";
	} else {
		return "max";
	}
}


inline lab::ChannelCountMode toChannelCountMode(const string &mode) {
	if (mode == "clamped-max") {
		return lab::ChannelCountMode::ClampedMax;
	} else if (mode == "explicit") {
		return lab::ChannelCountMode::Explicit;
	} else {
		return lab::ChannelCountMode::Max;
	}
}


inline string fromChannelInterpretation(lab::ChannelInterpretation io) {
	if (io == lab::ChannelInterpretation::Discrete) {
		return "discrete";
	} else {
		return "speakers";
	}
}


inline lab::ChannelInterpretation toChannelInterpretation(const string &io) {
	if (io == "discrete") {
		return lab::ChannelInterpretation::Discrete;
	} else {
		return lab::ChannelInterpretation::Speakers;
	}
}


// ------ Constructor and Destructor

AudioNode::AudioNode(Napi::Object context, NodePtr node) : EventEmitter() {
	
	_isDestroyed = false;
	
	_context.Reset(context);
	_impl = node;
	NodePtr *nn = new NodePtr(node);
	
	
	_channelCount = node->channelCount();
	_channelCountMode = fromChannelCountMode(node->channelCountMode());
	_channelInterpretation = fromChannelInterpretation(node->channelInterpretation());
	
}


AudioNode::~AudioNode() {
	
	_destroy();
	
}


AudioNode::NodePtr AudioNode::getNode() const {
	return _impl;
}


void AudioNode::_destroy() { DES_CHECK;
	
	Napi::Object context = JS_OBJ(_context);
	AudioContext *audioContext = ObjectWrap::Unwrap<AudioContext>(context);
	lab::AudioContext *ctx = audioContext->getContext().get();
	ctx->disconnect(_impl, nullptr);
	
	_impl.reset();
	_context.Reset();
	
	_isDestroyed = true;
	
}


// ------ Methods and props


// node2 node1.connect(node2);
// node2 node1.connect(node2, output);
// node2 node1.connect(node2, output, input);
// undefined node1.connect(param);
// undefined node1.connect(param, output);
JS_METHOD(AudioNode::connect) { THIS_AUDIO_NODE; THIS_CHECK;
	
	REQ_OBJ_ARG(0, destination);
	
	Napi::Object context = JS_OBJ(_context);
	AudioContext *audioContext = ObjectWrap::Unwrap<AudioContext>(context);
	
	lab::AudioContext *ctx = audioContext->getContext().get();
	
	if (isAudioNode(destination)) {
		
		LET_INT32_ARG(1, output);
		LET_INT32_ARG(2, input);
		
		AudioNode *destNode = ObjectWrap::Unwrap<AudioNode>(destination);
		
		ctx->connect(_impl, _impl, input, output);
		
	} else if (AudioParam::isAudioParam(destination)) {
		
		LET_INT32_ARG(1, output);
		
		AudioParam *destParam = ObjectWrap::Unwrap<AudioParam>(destination);
		
		ctx->connectParam(destParam->getParam(), _impl, output);
		
	}
	
}


// undefined node1.disconnect();
// undefined node1.disconnect(node2);
// undefined node1.disconnect(node2, output);
// undefined node1.disconnect(node2, output, input);
JS_METHOD(AudioNode::disconnect) { THIS_AUDIO_NODE; THIS_CHECK;
	
	int output = 0;
	int input = 0;
	Napi::Object destination;
	
	Napi::Object context = JS_OBJ(_context);
	AudioContext *audioContext = ObjectWrap::Unwrap<AudioContext>(context);
	lab::AudioContext *ctx = audioContext->getContext().get();
	
	if (info.Length() == 1) {
		
		if (info[0]->IsObject()) {
			
			REQ_OBJ_ARG(0, destArg);
			
		} else if (info[0]->IsNumber()) {
			
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
		return;
		
	}
	
	if (isAudioNode(destination)) {
		
		AudioNode *destNode = ObjectWrap::Unwrap<AudioNode>(destination);
		ctx->disconnect(_impl, _impl, input, output);
		
	} else if (AudioParam::isAudioParam(destination)) {
		
		AudioParam *destParam = ObjectWrap::Unwrap<AudioParam>(destination);
		
		AudioParam::ParamPtr param = destParam->getParam();
		
		lab::ContextGraphLock graphLock(ctx, "AudioNode::disconnect");
		// TODO:
		// param->disconnect(graphLock, param, _impl);
		
	}
	
}


JS_GETTER(AudioNode::contextGetter) { THIS_AUDIO_NODE; THIS_CHECK;
	
	RET_VALUE(__context.Value());
	
}


JS_GETTER(AudioNode::numberOfInputsGetter) { THIS_AUDIO_NODE; THIS_CHECK;
	
	RET_NUM(static_cast<uint32_t>(_impl->numberOfInputs()));
	
}


JS_GETTER(AudioNode::numberOfOutputsGetter) { THIS_AUDIO_NODE; THIS_CHECK;
	
	RET_NUM(static_cast<uint32_t>(_impl->numberOfOutputs()));
	
}


JS_GETTER(AudioNode::channelCountGetter) { THIS_AUDIO_NODE; THIS_CHECK;
	
	RET_NUM(static_cast<uint32_t>(_impl->channelCount()));
	
}


JS_SETTER(AudioNode::channelCountSetter) { THIS_AUDIO_NODE; THIS_CHECK; SETTER_UINT32_ARG;
	
	CACHE_CAS(_channelCount, v);
	
	Napi::Object context = JS_OBJ(_context);
	AudioContext *audioContext = ObjectWrap::Unwrap<AudioContext>(context);
	
	lab::ContextGraphLock graphLock(audioContext->getContext().get(), "AudioNode::channelCountSetter");
	_impl->setChannelCount(graphLock, _channelCount);
	
	audioNode->emit("channelCount", 1, &value);
	
}


JS_GETTER(AudioNode::channelCountModeGetter) { THIS_AUDIO_NODE; THIS_CHECK;
	
	RET_STR(__channelCountMode);
	
}

JS_SETTER(AudioNode::channelCountModeSetter) { THIS_AUDIO_NODE; THIS_CHECK; SETTER_UTF8_ARG;
	
	if (_channelCountMode == *v) {
		return;
	}
	_channelCountMode = *v;
	
	// TODO: may be additional actions on change?
	
	audioNode->emit("channelCountMode", 1, &value);
	
}


JS_GETTER(AudioNode::channelInterpretationGetter) { THIS_AUDIO_NODE; THIS_CHECK;
	
	RET_STR(__channelInterpretation);
	
}

JS_SETTER(AudioNode::channelInterpretationSetter) { THIS_AUDIO_NODE; THIS_CHECK; SETTER_UTF8_ARG;
	
	if (_channelInterpretation == *v) {
		return;
	}
	_channelInterpretation = *v;
	
	// TODO: may be additional actions on change?
	
	audioNode->emit("channelInterpretation", 1, &value);
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference AudioNode::_ctorAudioNode;


void AudioNode::init(Napi::Env env, Napi::Object exports) {
	
	
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, context);
	ACCESSOR_R(obj, numberOfInputs);
	ACCESSOR_R(obj, numberOfOutputs);
	ACCESSOR_RW(obj, channelCount);
	ACCESSOR_RW(obj, channelCountMode);
	ACCESSOR_RW(obj, channelInterpretation);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	Nan::SetPrototypeMethod(proto, "connect", connect);
	Nan::SetPrototypeMethod(proto, "disconnect", disconnect);
	
	// -------- static
	
	Napi::Function ctor = DefineClass(env, "AudioNode", {
	
	});
	
	_ctorAudioNode = Napi::Persistent(ctor);
	_ctorAudioNode.SuppressDestruct();
	
	exports.Set("AudioNode", ctor);
	
}


bool AudioNode::isAudioNode(Napi::Object obj) {
	return obj.InstanceOf(_ctorAudioNode.Value());
}


JS_METHOD(AudioNode::newCtor) {
	
	Nan::ThrowTypeError("'AudioNode' is abstract, use a specific node class.");
	
}


JS_METHOD(AudioNode::destroy) { THIS_AUDIO_NODE; THIS_CHECK;
	
	audioNode->emit("destroy");
	
	_destroy();
	
}


JS_GETTER(AudioNode::isDestroyedGetter) { THIS_AUDIO_NODE;
	
	RET_BOOL(_isDestroyed);
	
}
