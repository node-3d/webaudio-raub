#include <LabSound/LabSound.h>

#include "audio-buffer-source-node.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"
#include "audio-buffer.hpp"


Napi::FunctionReference AudioBufferSourceNode::_constructor;

void AudioBufferSourceNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "AudioBufferSourceNode", {
		ACCESSOR_RW(AudioBufferSourceNode, loopEnd),
		ACCESSOR_RW(AudioBufferSourceNode, loopStart),
		ACCESSOR_RW(AudioBufferSourceNode, loop),
		ACCESSOR_RW(AudioBufferSourceNode, buffer),
		ACCESSOR_M(AudioBufferSourceNode, start),
		ACCESSOR_R(AudioBufferSourceNode, detune),
		ACCESSOR_R(AudioBufferSourceNode, playbackRate),
		ACCESSOR_M(AudioBufferSourceNode, destroy)
	});
	
	_constructor = Napi::Persistent(ctor);
	_constructor.SuppressDestruct();
	
	exports.Set("AudioBufferSourceNode", ctor);
	
}


AudioBufferSourceNode::AudioBufferSourceNode(const Napi::CallbackInfo &info):
Napi::ObjectWrap<AudioBufferSourceNode>(info),
CommonNode(info, "AudioBufferSourceNode") { NAPI_ENV;
	
	CTOR_CHECK("AudioBufferSourceNode");
	
	REQ_OBJ_ARG(0, context);
	
	Napi::Object that = info.This().As<Napi::Object>();
	Napi::Function ctor = _constructor.Value().As<Napi::Function>();
	Napi::Function _Super = ctor.Get("_Super").As<Napi::Function>();
	
	reset(context, std::make_shared<lab::SampledAudioNode>());
	
	std::vector<napi_value> args;
	args.push_back(context);
	_Super.Call(that, args);
	
	lab::SampledAudioNode *node = static_cast<lab::SampledAudioNode*>(
		_impl.get()
	);
	
	_playbackRate.Reset(AudioParam::create(env, context, node->playbackRate()));
	// FIXME: LabSound
	// _detune.Reset(AudioParam::getNew(context, node->gain()));
	
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
	
	lab::AudioContext *ctx = audioContext->getCtx().get();
	
	{
		lab::ContextRenderLock r(ctx, "AudioBufferSourceNode::_destroy");
		node->setBus(r, nullptr);
	}
	
	_buffer.Reset();
	_playbackRate.Reset();
	_detune.Reset();
	
	_isDestroyed = true;
	
	CommonNode::_destroy();
	
}


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


JS_SETTER(AudioBufferSourceNode::bufferSetter) { THIS_SETTER_CHECK; SETTER_OBJ_ARG;
	
	// if (Nan::New(_buffer) == v) {
	// 	return;
	// }
	_buffer.Reset(v);
	
	Napi::Object context = _context.Value();
	AudioContext *audioContext = Napi::ObjectWrap<AudioContext>::Unwrap(context);
	
	lab::AudioContext *ctx = audioContext->getCtx().get();
	
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

JS_SETTER(AudioBufferSourceNode::loopSetter) { THIS_SETTER_CHECK; SETTER_BOOL_ARG;
	
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

JS_SETTER(AudioBufferSourceNode::loopStartSetter) { THIS_SETTER_CHECK; SETTER_DOUBLE_ARG;
	
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

JS_SETTER(AudioBufferSourceNode::loopEndSetter) { THIS_SETTER_CHECK; SETTER_DOUBLE_ARG;
	
	lab::SampledAudioNode *node = static_cast<lab::SampledAudioNode*>(
		_impl.get()
	);
	
	node->setLoopEnd(v);
	
	emit("loopEnd", 1, &value);
	
}
