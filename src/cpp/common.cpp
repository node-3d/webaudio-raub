#include <LabSound/LabSound.h>

#include "audio-context.hpp"

#include "common.hpp"


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

void CommonBus::reset(Napi::Object context, BusPtr bus) {
	_context.Reset(context);
	_impl = bus;
}


void CommonListener::reset(Napi::Object context, ListenerPtr listener) {
	_context.Reset(context);
	_impl = listener;
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

CommonBus::BusPtr CommonBus::getBus() const {
	return _impl;
}

CommonListener::ListenerPtr CommonListener::getListener() const {
	return _impl;
}


void Common::_destroy() { DES_CHECK;
	_isDestroyed = true;
}


void CommonNode::_destroy() { DES_CHECK;
	
	AudioContext *audioContext = Napi::ObjectWrap<AudioContext>::Unwrap(_context.Value());
	lab::AudioContext *ctx = audioContext->getCtx().get();
	ctx->disconnect(_impl, nullptr);
	
	_impl.reset();
	_context.Reset();
	
	Common::_destroy();
	
}


void CommonParam::_destroy() { DES_CHECK;
	
	_impl.reset();
	_context.Reset();
	
	Common::_destroy();
	
}


void CommonCtx::_destroy() { DES_CHECK;
	
	_impl.reset();
	
	Common::_destroy();
	
}


void CommonBus::_destroy() { DES_CHECK;
	
	_impl.reset();
	_context.Reset();
	
	Common::_destroy();
	
}


void CommonListener::_destroy() { DES_CHECK;
	
	_impl.reset();
	_context.Reset();
	
	Common::_destroy();
	
}


void Common::emit(
	const char* name,
	int argc,
	const Napi::Value *argv
) { DES_CHECK;
	Napi::Object that = Value().As<Napi::Object>();
	eventEmit(that, name, argc, argv);
}

void Common::emitAsync(
	const char* name,
	int argc,
	const Napi::Value *argv
) { DES_CHECK;
	Napi::Object that = Value().As<Napi::Object>();
	eventEmitAsync(that, name, argc, argv, asyncCtx);
}

JS_METHOD(Common::destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	
	RET_UNDEFINED;
	
}


JS_GETTER(Common::isDestroyedGetter) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
