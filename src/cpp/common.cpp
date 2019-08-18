#include <LabSound/core/AudioContext.h>

#include "audio-context.hpp"

#include "common.hpp"


Common::Common() {
	_isDestroyed = false;
}

Common::~Common() {
	_destroy();
}

void CommonNode::reset(Napi::Object context, NodePtr node) {
	_context.Reset(context);
	_impl = node;
}

void CommonParam::reset(Napi::Object context, ParamPtr param) {
	_context.Reset(context);
	_impl = param;
}

void CommonCtx::reset(CtxPtr ctx) {
	_impl = ctx;
}


CommonNode::NodePtr CommonNode::getNode() const {
	return _impl;
}

CommonParam::ParamPtr CommonParam::getParam() const {
	return _impl;
}

CommonCtx::CtxPtr CommonCtx::getCtx() const {
	return _impl;
}


void Common::_destroy() { DES_CHECK;
	
	_context.Reset();
	
	_isDestroyed = true;
	
}


void CommonNode::_destroy() { DES_CHECK;
	
	AudioContext *audioContext = Napi::ObjectWrap<AudioContext>::Unwrap(_context.Value());
	lab::AudioContext *ctx = audioContext->getContext().get();
	ctx->disconnect(_impl, nullptr);
	
	_impl.reset();
	
	Common::_destroy();
	
}


void CommonParam::_destroy() { DES_CHECK;
	
	// AudioContext *audioContext = Napi::ObjectWrap<AudioContext>::Unwrap(_context.Value());
	// lab::AudioContext *ctx = audioContext->getContext().get();
	// ctx->disconnect(_impl, nullptr);
	
	_impl.reset();
	
	Common::_destroy();
	
}


void CommonCtx::_destroy() { DES_CHECK;
	
	// AudioContext *audioContext = Napi::ObjectWrap<AudioContext>::Unwrap(_context.Value());
	// lab::AudioContext *ctx = audioContext->getContext().get();
	// ctx->disconnect(_impl, nullptr);
	
	_impl.reset();
	
	Common::_destroy();
	
}

void Common::emit(
	const Napi::CallbackInfo& info,
	const char* name,
	int argc,
	const Napi::Value *argv
) {
	NAPI_ENV;
	eventEmit(env, info.This().As<Napi::Object>(), name, argc, argv);
}


JS_METHOD(Common::destroy) { THIS_CHECK;
	
	emit(info, "destroy");
	
	_destroy();
	
}


JS_GETTER(Common::isDestroyedGetter) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
