#include <LabSound/core/GainNode.h>

#include "gain-node.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"


Napi::FunctionReference GainNode::_constructor;

void GainNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "GainNode", {
		ACCESSOR_M(GainNode, destroy),
		ACCESSOR_R(GainNode, gain),
		ACCESSOR_R(GainNode, isDestroyed)
	});
	
	_constructor = Napi::Persistent(ctor);
	_constructor.SuppressDestruct();
	
	exports.Set("GainNode", ctor);
	
}

Napi::Object GainNode::create(Napi::Env env, Napi::Object context) {
	Napi::Function ctor = _constructor.Value().As<Napi::Function>();
	std::vector<napi_value> args;
	args.push_back(context);
	return ctor.New(args);
}


GainNode::GainNode(const Napi::CallbackInfo &info):
Napi::ObjectWrap<GainNode>(info) { NAPI_ENV;
	
	CTOR_CHECK("GainNode");
	
	REQ_OBJ_ARG(0, context);
	
	NodePtr node = std::make_shared<lab::GainNode>();
	
	reset(context, node);
	
	Napi::Object that = info.This().As<Napi::Object>();
	Napi::Function ctor = _constructor.Value().As<Napi::Function>();
	Napi::Function _Super = ctor.Get("_Super").As<Napi::Function>();
	std::vector<napi_value> args;
	args.push_back(context);
	_Super.Call(that, args);
	
	lab::GainNode *gainNode = reinterpret_cast<lab::GainNode*>(node.get());
	_gain.Reset(AudioParam::create(env, context, gainNode->gain()));
	
}


void GainNode::_destroy() { DES_CHECK;
	
	_gain.Reset();
	
	CommonNode::_destroy();
	
}


JS_GETTER(GainNode::gainGetter) { THIS_CHECK;
	
	RET_VALUE(_gain.Value());
	
}
