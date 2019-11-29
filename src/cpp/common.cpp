#include "common.hpp"
#include "audio-context.hpp"


void _disconnectNode(AudioContext *context, NodePtr node) {
	lab::AudioContext *ctx = context->getCtx().get();
	ctx->disconnect(node, nullptr);
}


void _disconnectParam(AudioContext *context, ParamPtr param) {
	lab::AudioContext *ctx = context->getCtx().get();
	lab::ContextGraphLock graphLock(ctx, "_disconnectParam");
	lab::AudioParam::disconnectAll(graphLock, param);
}

void Common::reset(Napi::Object context) {
	_context.Reset(context);
	_contextVal = AudioContext::unwrap(context);
}
