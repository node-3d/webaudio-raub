#include <cstdlib>

#include <LabSound/core/AudioContext.h>
#include <LabSound/core/AudioNode.h>
#include <LabSound/core/AudioParam.h>
#include <LabSound/extended/AudioContextLock.h>

#include "audio-node.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_AUDIO_NODE                                                       \
	AudioNode *audioNode = Nan::ObjectWrap::Unwrap<AudioNode>(info.This());

#define THIS_CHECK                                                            \
	if (audioNode->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (audioNode->CACHE == V) {                                              \
		return;                                                               \
	}                                                                         \
	audioNode->CACHE = V;


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

AudioNode::AudioNode(V8_VAR_OBJ context, NodePtr node) : EventEmitter() {
	
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
	
	V8_VAR_OBJ context = JS_OBJ(_context);
	AudioContext *audioContext = ObjectWrap::Unwrap<AudioContext>(context);
	lab::AudioContext *ctx = audioContext->getContext().get();
	ctx->disconnect(_impl, nullptr);
	
	_impl.reset();
	_context.Reset();
	
	_isDestroyed = true;
	
	EventEmitter::_destroy();
	
}


// ------ Methods and props


// node2 node1.connect(node2);
// node2 node1.connect(node2, output);
// node2 node1.connect(node2, output, input);
// undefined node1.connect(param);
// undefined node1.connect(param, output);
NAN_METHOD(AudioNode::connect) { THIS_AUDIO_NODE; THIS_CHECK;
	
	REQ_OBJ_ARG(0, destination);
	
	V8_VAR_OBJ context = JS_OBJ(audioNode->_context);
	AudioContext *audioContext = ObjectWrap::Unwrap<AudioContext>(context);
	
	lab::AudioContext *ctx = audioContext->getContext().get();
	
	if (isAudioNode(destination)) {
		
		LET_INT32_ARG(1, output);
		LET_INT32_ARG(2, input);
		
		AudioNode *destNode = ObjectWrap::Unwrap<AudioNode>(destination);
		
		ctx->connect(destNode->_impl, audioNode->_impl, input, output);
		
	} else if (AudioParam::isAudioParam(destination)) {
		
		LET_INT32_ARG(1, output);
		
		AudioParam *destParam = ObjectWrap::Unwrap<AudioParam>(destination);
		
		ctx->connectParam(destParam->getParam(), audioNode->_impl, output);
		
	}
	
}


// undefined node1.disconnect();
// undefined node1.disconnect(node2);
// undefined node1.disconnect(node2, output);
// undefined node1.disconnect(node2, output, input);
NAN_METHOD(AudioNode::disconnect) { THIS_AUDIO_NODE; THIS_CHECK;
	
	int output = 0;
	int input = 0;
	V8_VAR_OBJ destination;
	
	V8_VAR_OBJ context = JS_OBJ(audioNode->_context);
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
		ctx->disconnect(audioNode->_impl, NodePtr(), input, output);
		return;
		
	}
	
	if (isAudioNode(destination)) {
		
		AudioNode *destNode = ObjectWrap::Unwrap<AudioNode>(destination);
		ctx->disconnect(audioNode->_impl, destNode->_impl, input, output);
		
	} else if (AudioParam::isAudioParam(destination)) {
		
		AudioParam *destParam = ObjectWrap::Unwrap<AudioParam>(destination);
		
		AudioParam::ParamPtr param = destParam->getParam();
		
		lab::ContextGraphLock graphLock(ctx, "AudioNode::disconnect");
		// TODO:
		// param->disconnect(graphLock, param, audioNode->_impl);
		
	}
	
}


NAN_GETTER(AudioNode::contextGetter) { THIS_AUDIO_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(audioNode->_context));
	
}


NAN_GETTER(AudioNode::numberOfInputsGetter) { THIS_AUDIO_NODE; THIS_CHECK;
	
	RET_VALUE(JS_UINT32(static_cast<uint32_t>(audioNode->_impl->numberOfInputs())));
	
}


NAN_GETTER(AudioNode::numberOfOutputsGetter) { THIS_AUDIO_NODE; THIS_CHECK;
	
	RET_VALUE(JS_UINT32(static_cast<uint32_t>(audioNode->_impl->numberOfOutputs())));
	
}


NAN_GETTER(AudioNode::channelCountGetter) { THIS_AUDIO_NODE; THIS_CHECK;
	
	RET_VALUE(JS_UINT32(static_cast<uint32_t>(audioNode->_impl->channelCount())));
	
}


NAN_SETTER(AudioNode::channelCountSetter) { THIS_AUDIO_NODE; THIS_CHECK; SETTER_UINT32_ARG;
	
	CACHE_CAS(_channelCount, v);
	
	V8_VAR_OBJ context = JS_OBJ(audioNode->_context);
	AudioContext *audioContext = ObjectWrap::Unwrap<AudioContext>(context);
	
	lab::ContextGraphLock graphLock(audioContext->getContext().get(), "AudioNode::channelCountSetter");
	audioNode->_impl->setChannelCount(graphLock, audioNode->_channelCount);
	
	audioNode->emit("channelCount", 1, &value);
	
}


NAN_GETTER(AudioNode::channelCountModeGetter) { THIS_AUDIO_NODE; THIS_CHECK;
	
	RET_VALUE(JS_UTF8(audioNode->_channelCountMode));
	
}

NAN_SETTER(AudioNode::channelCountModeSetter) { THIS_AUDIO_NODE; THIS_CHECK; SETTER_UTF8_ARG;
	
	if (audioNode->_channelCountMode == *v) {
		return;
	}
	audioNode->_channelCountMode = *v;
	
	// TODO: may be additional actions on change?
	
	audioNode->emit("channelCountMode", 1, &value);
	
}


NAN_GETTER(AudioNode::channelInterpretationGetter) { THIS_AUDIO_NODE; THIS_CHECK;
	
	RET_VALUE(JS_UTF8(audioNode->_channelInterpretation));
	
}

NAN_SETTER(AudioNode::channelInterpretationSetter) { THIS_AUDIO_NODE; THIS_CHECK; SETTER_UTF8_ARG;
	
	if (audioNode->_channelInterpretation == *v) {
		return;
	}
	audioNode->_channelInterpretation = *v;
	
	// TODO: may be additional actions on change?
	
	audioNode->emit("channelInterpretation", 1, &value);
	
}


// ------ System methods and props for ObjectWrap

V8_STORE_FT AudioNode::_protoAudioNode;
V8_STORE_FUNC AudioNode::_ctorAudioNode;


void AudioNode::init(V8_VAR_OBJ target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);
	
	// class AudioNode inherits EventEmitter
	V8_VAR_FT parent = Nan::New(EventEmitter::_protoEventEmitter);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AudioNode"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
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
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoAudioNode.Reset(proto);
	_ctorAudioNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("AudioNode"), ctor);
	
	
}


bool AudioNode::isAudioNode(V8_VAR_OBJ obj) {
	return Nan::New(_protoAudioNode)->HasInstance(obj);
}


NAN_METHOD(AudioNode::newCtor) {
	
	Nan::ThrowTypeError("'AudioNode' is abstract, use a specific node class.");
	
}


NAN_METHOD(AudioNode::destroy) { THIS_AUDIO_NODE; THIS_CHECK;
	
	audioNode->emit("destroy");
	
	audioNode->_destroy();
	
}


NAN_GETTER(AudioNode::isDestroyedGetter) { THIS_AUDIO_NODE;
	
	RET_VALUE(JS_BOOL(audioNode->_isDestroyed));
	
}
