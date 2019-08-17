#include <LabSound/core/AudioContext.h>

#include "audio-context.hpp"

#include "common.hpp"


Common::Common() {
	_isDestroyed = false;
}

Common::~Common() {
	_destroy();
}


void Common::reset(Napi::Object context) {
	_context.Reset(context);
}

void CommonNode::reset(Napi::Object context, NodePtr node) {
	Common::reset(context);
	_impl = node;
}

void CommonParam::reset(Napi::Object context, ParamPtr param) {
	Common::reset(context);
	_impl = param;
}


CommonNode::NodePtr CommonNode::getNode() const {
	return _impl;
}

CommonParam::ParamPtr CommonParam::getParam() const {
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


void Common::emit(
	const Napi::CallbackInfo& info,
	const char* name,
	int argc,
	Napi::Value *argv
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
