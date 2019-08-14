#include <LabSound/core/AudioContext.h>
#include <LabSound/core/SampledAudioNode.h>
#include <LabSound/extended/AudioContextLock.h>

#include "audio-buffer-source-node.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"
#include "audio-buffer.hpp"

#include "common.hpp"


// ------ Aux macros

	Nan::ObjectWrap::Unwrap<AudioBufferSourceNode>(info.This());


// ------ Constructor and Destructor

int num = 0;

AudioBufferSourceNode::AudioBufferSourceNode(Napi::Object context) :
AudioScheduledSourceNode(
	context,
	NodePtr(new lab::SampledAudioNode())
) {
	
	lab::SampledAudioNode *node = static_cast<lab::SampledAudioNode*>(_impl.get());
	
	_playbackRate.Reset(AudioParam::getNew(context, node->playbackRate()));
	
	// FIXME: LabSound
	// _detune.Reset(AudioParam::getNew(context, node->gain()));
	
	_isDestroyed = false;
	
}


AudioBufferSourceNode::~AudioBufferSourceNode() {
	
	_destroy();
	
}


void AudioBufferSourceNode::_destroy() { DES_CHECK;
	
	lab::SampledAudioNode *node = static_cast<lab::SampledAudioNode*>(
		_impl.get()
	);
	
	Napi::Object context = JS_OBJ(_context);
	AudioContext *audioContext = ObjectWrap::Unwrap<AudioContext>(context);
	
	lab::AudioContext *ctx = audioContext->getContext().get();
	
	{
		lab::ContextRenderLock r(ctx, "AudioBufferSourceNode::_destroy");
		node->setBus(r, nullptr);
	}
	
	_buffer.Reset();
	_playbackRate.Reset();
	_detune.Reset();
	
	_isDestroyed = true;
	
	AudioScheduledSourceNode::_destroy();
	
}


// ------ Methods and props


JS_METHOD(AudioBufferSourceNode::start) { THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK;
	
	LET_DOUBLE_ARG(0, when);
	LET_DOUBLE_ARG(1, grainOffset);
	LET_DOUBLE_ARG(2, grainDuration);
	
	lab::SampledAudioNode *node = static_cast<lab::SampledAudioNode*>(
		_impl.get()
	);
	
	if (grainDuration > 0) {
		node->startGrain(when, grainOffset, grainDuration);
	} else {
		node->startGrain(when, grainOffset);
	}
	
}


JS_GETTER(AudioBufferSourceNode::bufferGetter) {
	
	THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK;
	
	RET_VALUE(__buffer.Value());
	
}


JS_SETTER(AudioBufferSourceNode::bufferSetter) {
	THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK; SETTER_OBJ_ARG;
	
	if (Nan::New(_buffer) == v) {
		return;
	}
	_buffer.Reset(v);
	
	Napi::Object context = JS_OBJ(_context);
	AudioContext *audioContext = ObjectWrap::Unwrap<AudioContext>(context);
	
	lab::AudioContext *ctx = audioContext->getContext().get();
	
	lab::ContextRenderLock r(ctx, "AudioBufferSourceNode::bufferSetter");
	
	AudioBuffer *audioBuffer = ObjectWrap::Unwrap<AudioBuffer>(v);
	AudioBuffer::BusPtr bus = audioBuffer->getBus();
	
	lab::SampledAudioNode *node = static_cast<lab::SampledAudioNode*>(
		_impl.get()
	);
	node->setBus(r, bus);
	
	audioBufferSourceNode->emit("buffer", 1, &value);
	
}


JS_GETTER(AudioBufferSourceNode::playbackRateGetter) { THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK;
	
	RET_VALUE(__playbackRate.Value());
	
}


JS_GETTER(AudioBufferSourceNode::detuneGetter) { THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK;
	
	RET_VALUE(__detune.Value());
	
}


JS_GETTER(AudioBufferSourceNode::loopGetter) { THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK;
	
	lab::SampledAudioNode *node = static_cast<lab::SampledAudioNode*>(
		_impl.get()
	);
	
	RET_BOOL(node->loop());
	
}

JS_SETTER(AudioBufferSourceNode::loopSetter) {
	THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK; SETTER_BOOL_ARG;
	
	lab::SampledAudioNode *node = static_cast<lab::SampledAudioNode*>(
		_impl.get()
	);
	
	node->setLoop(v);
	
	audioBufferSourceNode->emit("loop", 1, &value);
	
}


JS_GETTER(AudioBufferSourceNode::loopStartGetter) { THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK;
	
	lab::SampledAudioNode *node = static_cast<lab::SampledAudioNode*>(
		_impl.get()
	);
	
	RET_NUM(node->loopStart());
	
}

JS_SETTER(AudioBufferSourceNode::loopStartSetter) {
	THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	lab::SampledAudioNode *node = static_cast<lab::SampledAudioNode*>(
		_impl.get()
	);
	
	node->setLoopStart(v);
	
	audioBufferSourceNode->emit("loopStart", 1, &value);
	
}


JS_GETTER(AudioBufferSourceNode::loopEndGetter) { THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK;
	
	lab::SampledAudioNode *node = static_cast<lab::SampledAudioNode*>(
		_impl.get()
	);
	
	RET_NUM(node->loopEnd());
	
}

JS_SETTER(AudioBufferSourceNode::loopEndSetter) {
	THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	lab::SampledAudioNode *node = static_cast<lab::SampledAudioNode*>(
		_impl.get()
	);
	
	node->setLoopEnd(v);
	
	audioBufferSourceNode->emit("loopEnd", 1, &value);
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference AudioBufferSourceNode::_ctorAudioBufferSourceNode;


void AudioBufferSourceNode::init(Napi::Env env, Napi::Object exports) {
	
	
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_RW(obj, buffer);
	ACCESSOR_R(obj, playbackRate);
	ACCESSOR_R(obj, detune);
	ACCESSOR_RW(obj, loop);
	ACCESSOR_RW(obj, loopStart);
	ACCESSOR_RW(obj, loopEnd);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	Nan::SetPrototypeMethod(proto, "start", start);
	
	// -------- static
	
	Napi::Function ctor = DefineClass(env, "AudioBufferSourceNode", {
	
	});
	
	_ctorAudioBufferSourceNode = Napi::Persistent(ctor);
	_ctorAudioBufferSourceNode.SuppressDestruct();
	
	exports.Set("AudioBufferSourceNode", ctor);
	
}


Napi::Object AudioBufferSourceNode::getNew(Napi::Object context) {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorAudioBufferSourceNode);
	V8_VAR_VAL argv[] = { context };
	return Nan::NewInstance(ctor, 1, argv).ToLocalChecked();
	
}


JS_METHOD(AudioBufferSourceNode::newCtor) {
	
	CTOR_CHECK("AudioBufferSourceNode");
	
	REQ_OBJ_ARG(0, context);
	
	AudioBufferSourceNode *audioBufferSourceNode = new AudioBufferSourceNode(context);
	audioBufferSourceNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


JS_METHOD(AudioBufferSourceNode::destroy) { THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK;
	
	audioBufferSourceNode->emit("destroy");
	
	_destroy();
	
}


JS_GETTER(AudioBufferSourceNode::isDestroyedGetter) { THIS_AUDIO_BUFFER_SOURCE_NODE;
	
	RET_BOOL(_isDestroyed);
	
}
