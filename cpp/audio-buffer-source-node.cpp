#include <cstdlib>

#include <LabSound/core/AudioContext.h>
#include <LabSound/core/SampledAudioNode.h>
#include <LabSound/extended/AudioContextLock.h>

#include "audio-buffer-source-node.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"
#include "audio-buffer.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_AUDIO_BUFFER_SOURCE_NODE                                         \
	AudioBufferSourceNode *audioBufferSourceNode = Nan::ObjectWrap::Unwrap<AudioBufferSourceNode>(info.This());

#define THIS_CHECK                                                            \
	if (audioBufferSourceNode->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (audioBufferSourceNode->CACHE == V) {                                  \
		return;                                                               \
	}                                                                         \
	audioBufferSourceNode->CACHE = V;


// ------ Constructor and Destructor

AudioBufferSourceNode::AudioBufferSourceNode(V8_VAR_OBJ context) :
AudioScheduledSourceNode(
	context,
	NodePtr(new lab::SampledAudioNode())
) {
	
	lab::SampledAudioNode *node = static_cast<lab::SampledAudioNode*>(_impl.get());
	
	_playbackRate.Reset(AudioParam::getNew(context, node->playbackRate()));
	
	// FIXME: LabSound
	_detune.Reset(AudioParam::getNew(context, node->gain()));
	
	_isDestroyed = false;
	
}


AudioBufferSourceNode::~AudioBufferSourceNode() {
	
	_destroy();
	
}


void AudioBufferSourceNode::_destroy() { DES_CHECK;
	
	_buffer.Reset();
	_playbackRate.Reset();
	_detune.Reset();
	
	_isDestroyed = true;
	
	AudioScheduledSourceNode::_destroy();
	
}


// ------ Methods and props


NAN_METHOD(AudioBufferSourceNode::start) { THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK;
	
	LET_DOUBLE_ARG(0, when);
	LET_DOUBLE_ARG(1, grainOffset);
	LET_DOUBLE_ARG(2, grainDuration);
	
	lab::SampledAudioNode *node = static_cast<lab::SampledAudioNode*>(
		audioBufferSourceNode->_impl.get()
	);
	
	if (grainDuration > 0) {
		node->startGrain(when, grainOffset, grainDuration);
	} else {
		node->startGrain(when, grainOffset);
	}
	
}


NAN_GETTER(AudioBufferSourceNode::bufferGetter) { THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(audioBufferSourceNode->_buffer));
	
}


NAN_SETTER(AudioBufferSourceNode::bufferSetter) {
	THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK; SETTER_OBJ_ARG;
	
	if (Nan::New(audioBufferSourceNode->_buffer) == v) {
		return;
	}
	audioBufferSourceNode->_buffer.Reset(v);
	
	V8_VAR_OBJ context = JS_OBJ(audioBufferSourceNode->_context);
	AudioContext *audioContext = ObjectWrap::Unwrap<AudioContext>(context);
	
	lab::AudioContext *ctx = audioContext->getContext().get();
	
	lab::ContextRenderLock r(ctx, "AudioBufferSourceNode::bufferSetter");
	
	AudioBuffer *audioBuffer = ObjectWrap::Unwrap<AudioBuffer>(v);
	AudioBuffer::BusPtr bus = audioBuffer->getBus();
	
	lab::SampledAudioNode *node = static_cast<lab::SampledAudioNode*>(
		audioBufferSourceNode->_impl.get()
	);
	node->setBus(r, bus);
	
	audioBufferSourceNode->emit("buffer", 1, &value);
	
}


NAN_GETTER(AudioBufferSourceNode::playbackRateGetter) { THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(audioBufferSourceNode->_playbackRate));
	
}


NAN_GETTER(AudioBufferSourceNode::detuneGetter) { THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(audioBufferSourceNode->_detune));
	
}


NAN_GETTER(AudioBufferSourceNode::loopGetter) { THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK;
	
	lab::SampledAudioNode *node = static_cast<lab::SampledAudioNode*>(
		audioBufferSourceNode->_impl.get()
	);
	
	RET_VALUE(JS_BOOL(node->loop()));
	
}

NAN_SETTER(AudioBufferSourceNode::loopSetter) {
	THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK; SETTER_BOOL_ARG;
	
	lab::SampledAudioNode *node = static_cast<lab::SampledAudioNode*>(
		audioBufferSourceNode->_impl.get()
	);
	
	node->setLoop(v);
	
	audioBufferSourceNode->emit("loop", 1, &value);
	
}


NAN_GETTER(AudioBufferSourceNode::loopStartGetter) { THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK;
	
	lab::SampledAudioNode *node = static_cast<lab::SampledAudioNode*>(
		audioBufferSourceNode->_impl.get()
	);
	
	RET_VALUE(JS_DOUBLE(node->loopStart()));
	
}

NAN_SETTER(AudioBufferSourceNode::loopStartSetter) {
	THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	lab::SampledAudioNode *node = static_cast<lab::SampledAudioNode*>(
		audioBufferSourceNode->_impl.get()
	);
	
	node->setLoopStart(v);
	
	audioBufferSourceNode->emit("loopStart", 1, &value);
	
}


NAN_GETTER(AudioBufferSourceNode::loopEndGetter) { THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK;
	
	lab::SampledAudioNode *node = static_cast<lab::SampledAudioNode*>(
		audioBufferSourceNode->_impl.get()
	);
	
	RET_VALUE(JS_DOUBLE(node->loopEnd()));
	
}

NAN_SETTER(AudioBufferSourceNode::loopEndSetter) {
	THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	lab::SampledAudioNode *node = static_cast<lab::SampledAudioNode*>(
		audioBufferSourceNode->_impl.get()
	);
	
	node->setLoopEnd(v);
	
	audioBufferSourceNode->emit("loopEnd", 1, &value);
	
}


// ------ System methods and props for ObjectWrap

V8_STORE_FT AudioBufferSourceNode::_protoAudioBufferSourceNode;
V8_STORE_FUNC AudioBufferSourceNode::_ctorAudioBufferSourceNode;


void AudioBufferSourceNode::init(V8_VAR_OBJ target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);
	
	// class AudioBufferSourceNode inherits AudioScheduledSourceNode
	V8_VAR_FT parent = Nan::New(AudioScheduledSourceNode::_protoAudioScheduledSourceNode);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AudioBufferSourceNode"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
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
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoAudioBufferSourceNode.Reset(proto);
	_ctorAudioBufferSourceNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("AudioBufferSourceNode"), ctor);
	
	
}


V8_VAR_OBJ AudioBufferSourceNode::getNew(V8_VAR_OBJ context) {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorAudioBufferSourceNode);
	V8_VAR_VAL argv[] = { context };
	return Nan::NewInstance(ctor, 1, argv).ToLocalChecked();
	
}


NAN_METHOD(AudioBufferSourceNode::newCtor) {
	
	CTOR_CHECK("AudioBufferSourceNode");
	
	REQ_OBJ_ARG(0, context);
	
	AudioBufferSourceNode *audioBufferSourceNode = new AudioBufferSourceNode(context);
	audioBufferSourceNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(AudioBufferSourceNode::destroy) { THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK;
	
	audioBufferSourceNode->emit("destroy");
	
	audioBufferSourceNode->_destroy();
	
}


NAN_GETTER(AudioBufferSourceNode::isDestroyedGetter) { THIS_AUDIO_BUFFER_SOURCE_NODE;
	
	RET_VALUE(JS_BOOL(audioBufferSourceNode->_isDestroyed));
	
}
