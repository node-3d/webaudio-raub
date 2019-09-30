#include "common.hpp"
#include "audio-context.hpp"


void _disconnectNode(Napi::Object context, NodePtr node) {
	AudioContext *audioContext = AudioContext::unwrap(context);
	lab::AudioContext *ctx = audioContext->getCtx().get();
	ctx->disconnect(node, nullptr);
}


void _disconnectParam(Napi::Object context, ParamPtr param) {
	AudioContext *audioContext = AudioContext::unwrap(context);
	lab::AudioContext *ctx = audioContext->getCtx().get();
	lab::ContextGraphLock graphLock(ctx, "_disconnectParam");
	lab::AudioParam::disconnectAll(graphLock, param);
}
