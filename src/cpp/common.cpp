#include <LabSound/LabSound.h>

#include "common.hpp"
#include "audio-context.hpp"


void _disconnectNode(Napi::Object context, NodePtr node) {
	AudioContext *audioContext = Napi::ObjectWrap<AudioContext>::Unwrap(context);
	lab::AudioContext *ctx = audioContext->getCtx().get();
	ctx->disconnect(node, nullptr);
};


void _disconnectParam(Napi::Object context, ParamPtr param) {
	AudioContext *audioContext = Napi::ObjectWrap<AudioContext>::Unwrap(context);
	lab::AudioContext *ctx = audioContext->getCtx().get();
	lab::ContextGraphLock graphLock(ctx, "_disconnectParam");
	lab::AudioParam::disconnectAll(graphLock, param);
};
