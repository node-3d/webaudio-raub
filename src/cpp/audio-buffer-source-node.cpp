#include <LabSound/core/AudioContext.h>
#include <LabSound/core/SampledAudioNode.h>
#include <LabSound/extended/AudioContextLock.h>

#include "audio-buffer-source-node.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"
#include "audio-buffer.hpp"

#include "common.hpp"


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
	
	Napi::Object context = _context.Value();
	AudioContext *audioContext = Napi::ObjectWrap<AudioContext>::Unwrap(context);
	
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


JS_METHOD(AudioBufferSourceNode::start) { THIS_CHECK;
	
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


JS_GETTER(AudioBufferSourceNode::bufferGetter) { THIS_CHECK;
	
	RET_VALUE(_buffer.Value());
	
}


JS_SETTER(AudioBufferSourceNode::bufferSetter) {
	THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK; SETTER_OBJ_ARG;
	
	if (Nan::New(_buffer) == v) {
		return;
	}
	_buffer.Reset(v);
	
	Napi::Object context = _context.Value()
	});;
	AudioContext *audioContext = Napi::ObjectWrap<AudioContext>::Unwrap(context);
	
	lab::AudioContext *ctx = audioContext->getContext().get();
	
	lab::ContextRenderLock r(ctx, "AudioBufferSourceNode::bufferSetter");
	
	AudioBuffer *audioBuffer = Napi::ObjectWrap<AudioBuffer>::Unwrap(v);
	AudioBuffer::BusPtr bus = audioBuffer->getBus();
	
	lab::SampledAudioNode *node = static_cast<lab::SampledAudioNode*>(
		_impl.get()
	);
	node->setBus(r, bus);
	
	emit("buffer", 1, &value);
	
}


JS_GETTER(AudioBufferSourceNode::playbackRateGetter) { THIS_CHECK;
	
	RET_VALUE(_playbackRate.Value());
	
}


JS_GETTER(AudioBufferSourceNode::detuneGetter) { THIS_CHECK;
	
	RET_VALUE(_detune.Value());
	
}


JS_GETTER(AudioBufferSourceNode::loopGetter) { THIS_CHECK;
	
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
	
	emit("loop", 1, &value);
	
}


JS_GETTER(AudioBufferSourceNode::loopStartGetter) { THIS_CHECK;
	
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
	
	emit("loopStart", 1, &value);
	
}


JS_GETTER(AudioBufferSourceNode::loopEndGetter) { THIS_CHECK;
	
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
	
	emit("loopEnd", 1, &value);
	
}


// ------ System methods and props for Napi::ObjectWrap

Napi::FunctionReference AudioBufferSourceNode::_constructor;


void AudioBufferSourceNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "AudioBufferSourceNode", {
		ACCESSOR_RW(AudioBufferSourceNode, loopEnd),
		ACCESSOR_RW(AudioBufferSourceNode, loopStart),
		ACCESSOR_RW(AudioBufferSourceNode, loop),
		ACCESSOR_RW(AudioBufferSourceNode, buffer),
		ACCESSOR_M(AudioBufferSourceNode, start),
		ACCESSOR_M(AudioBufferSourceNode, destroy),
		ACCESSOR_R(AudioBufferSourceNode, detune),
		ACCESSOR_R(AudioBufferSourceNode, playbackRate),
		ACCESSOR_R(AudioBufferSourceNode, isDestroyed)
	});
	
	_constructor = Napi::Persistent(ctor);
	_constructor.SuppressDestruct();
	
	exports.Set("AudioBufferSourceNode", ctor);
	
}


Napi::Object AudioBufferSourceNode::getNew(Napi::Object context) {
	
	Napi::Function ctor = Nan::New(_constructor);
	Napi::Value argv[] = { context };
	return Nan::NewInstance(ctor, 1, argv).ToLocalChecked();
	
}


AudioBufferSourceNode::AudioBufferSourceNode(const Napi::CallbackInfo &info): Napi::ObjectWrap<AudioBufferSourceNode>(info) {
	
	CTOR_CHECK("AudioBufferSourceNode");
	
	REQ_OBJ_ARG(0, context);
	
	AudioBufferSourceNode *audioBufferSourceNode = new AudioBufferSourceNode(context);
	
}


JS_METHOD(AudioBufferSourceNode::destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	
}


JS_GETTER(AudioBufferSourceNode::isDestroyedGetter) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
