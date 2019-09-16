#include "audio-buffer-source-node.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"
#include "audio-buffer.hpp"


IMPLEMENT_ES5_CLASS(AudioBufferSourceNode);

void AudioBufferSourceNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_SETTER(loopEnd);
	JS_ASSIGN_SETTER(loopStart);
	JS_ASSIGN_SETTER(loop);
	JS_ASSIGN_SETTER(buffer);
	JS_ASSIGN_METHOD(start);
	JS_ASSIGN_GETTER(detune);
	JS_ASSIGN_GETTER(playbackRate);
	JS_ASSIGN_METHOD(destroy);
	
	exports.Set("AudioBufferSourceNode", ctor);
	
}


AudioBufferSourceNode::AudioBufferSourceNode(const Napi::CallbackInfo &info):
CommonNode(info.This(), "AudioBufferSourceNode") { NAPI_ENV;
	
	REQ_OBJ_ARG(0, context);
	REQ_FUN_ARG(1, paramCtor);
	
	reset(context, std::make_shared<lab::SampledAudioNode>());
	
	lab::SampledAudioNode *node = static_cast<lab::SampledAudioNode*>(
		_impl.get()
	);
	
	napi_value argv[2];
	argv[0] = context;
	
	argv[1] = JS_EXT(&node->playbackRate());
	_playbackRate.Reset(paramCtor.New(2, argv), 1);
	
	argv[1] = JS_EXT(&node->detune());
	_detune.Reset(paramCtor.New(2, argv), 1);
	
	argv[1] = JS_EXT(&_impl);
	super(info, 2, argv);
	
}


AudioBufferSourceNode::~AudioBufferSourceNode() {
	_destroy();
}


void AudioBufferSourceNode::_destroy() { DES_CHECK;
	
	lab::SampledAudioNode *node = static_cast<lab::SampledAudioNode*>(
		_impl.get()
	);
	
	Napi::Object context = _context.Value();
	AudioContext *audioContext = AudioContext::unwrap(context);
	
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


JS_IMPLEMENT_METHOD(AudioBufferSourceNode, start) { THIS_CHECK;
	
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
	RET_UNDEFINED;
	
}


JS_IMPLEMENT_GETTER(AudioBufferSourceNode, buffer) { THIS_CHECK;
	
	RET_VALUE(_buffer.Value());
	
}


JS_IMPLEMENT_SETTER(AudioBufferSourceNode, buffer) { THIS_SETTER_CHECK; SETTER_OBJ_ARG;
	
	_buffer.Reset(v, 1);
	
	Napi::Object context = _context.Value();
	AudioContext *audioContext = AudioContext::unwrap(context);
	
	lab::AudioContext *ctx = audioContext->getCtx().get();
	
	lab::ContextRenderLock r(ctx, "AudioBufferSourceNode::bufferSetter");
	
	AudioBuffer *audioBuffer = AudioBuffer::unwrap(v);
	BusPtr bus = audioBuffer->getBus();
	
	lab::SampledAudioNode *node = static_cast<lab::SampledAudioNode*>(
		_impl.get()
	);
	node->setBus(r, bus);
	
	emit("buffer", 1, &value);
	
}


JS_IMPLEMENT_GETTER(AudioBufferSourceNode, playbackRate) { THIS_CHECK;
	
	RET_VALUE(_playbackRate.Value());
	
}


JS_IMPLEMENT_GETTER(AudioBufferSourceNode, detune) { THIS_CHECK;
	
	RET_VALUE(_detune.Value());
	
}


JS_IMPLEMENT_GETTER(AudioBufferSourceNode, loop) { THIS_CHECK;
	
	lab::SampledAudioNode *node = static_cast<lab::SampledAudioNode*>(
		_impl.get()
	);
	
	RET_BOOL(node->loop());
	
}

JS_IMPLEMENT_SETTER(AudioBufferSourceNode, loop) { THIS_SETTER_CHECK; SETTER_BOOL_ARG;
	
	lab::SampledAudioNode *node = static_cast<lab::SampledAudioNode*>(
		_impl.get()
	);
	
	node->setLoop(v);
	
	emit("loop", 1, &value);
	
}


JS_IMPLEMENT_GETTER(AudioBufferSourceNode, loopStart) { THIS_CHECK;
	
	lab::SampledAudioNode *node = static_cast<lab::SampledAudioNode*>(
		_impl.get()
	);
	
	RET_NUM(node->loopStart());
	
}

JS_IMPLEMENT_SETTER(AudioBufferSourceNode, loopStart) { THIS_SETTER_CHECK; SETTER_DOUBLE_ARG;
	
	lab::SampledAudioNode *node = static_cast<lab::SampledAudioNode*>(
		_impl.get()
	);
	
	node->setLoopStart(v);
	
	emit("loopStart", 1, &value);
	
}


JS_IMPLEMENT_GETTER(AudioBufferSourceNode, loopEnd) { THIS_CHECK;
	
	lab::SampledAudioNode *node = static_cast<lab::SampledAudioNode*>(
		_impl.get()
	);
	
	RET_NUM(node->loopEnd());
	
}

JS_IMPLEMENT_SETTER(AudioBufferSourceNode, loopEnd) { THIS_SETTER_CHECK; SETTER_DOUBLE_ARG;
	
	lab::SampledAudioNode *node = static_cast<lab::SampledAudioNode*>(
		_impl.get()
	);
	
	node->setLoopEnd(v);
	
	emit("loopEnd", 1, &value);
	
}


JS_IMPLEMENT_METHOD(AudioBufferSourceNode, destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	RET_UNDEFINED;
	
}
