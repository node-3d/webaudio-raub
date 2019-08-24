#include <LabSound/LabSound.h>

#include "delay-node.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"


Napi::FunctionReference DelayNode::_constructor;

void DelayNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "DelayNode", {
		ACCESSOR_R(DelayNode, delayTime),
		ACCESSOR_M(DelayNode, destroy)
	});
	
	_constructor = Napi::Persistent(ctor);
	_constructor.SuppressDestruct();
	
	exports.Set("DelayNode", ctor);
	
}


DelayNode::DelayNode(const Napi::CallbackInfo &info): 
Napi::ObjectWrap<DelayNode>(info),
CommonNode(info, "DelayNode") { NAPI_ENV;
	
	CTOR_CHECK("DelayNode");
	
	REQ_OBJ_ARG(0, context);
	REQ_DOUBLE_ARG(1, delay);
	
	AudioContext *audioContext = Napi::ObjectWrap<AudioContext>::Unwrap(context);
	float sampleRate = audioContext->getCtx()->sampleRate();
	
	Napi::Object that = info.This().As<Napi::Object>();
	Napi::Function ctor = _constructor.Value().As<Napi::Function>();
	Napi::Function _Super = ctor.Get("_Super").As<Napi::Function>();
	
	reset(context, std::make_shared<lab::DelayNode>(sampleRate, delay));
	
	std::vector<napi_value> args;
	args.push_back(context);
	_Super.Call(that, args);
	
	lab::DelayNode *node = static_cast<lab::DelayNode*>(
		_impl.get()
	);
	
	_delayTime.Reset(AudioParam::create(env, context, node->delayTime()));
	
}


DelayNode::~DelayNode() {
	_destroy();
}


void DelayNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	CommonNode::_destroy();
	
}


JS_GETTER(DelayNode::delayTimeGetter) { THIS_CHECK;
	
	RET_VALUE(_delayTime.Value());
	
}


JS_METHOD(DelayNode::destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	
}
