#include <LabSound/LabSound.h>

#include "gain-node.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"


Napi::FunctionReference GainNode::_constructor;

void GainNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "GainNode", {
		ACCESSOR_R(GainNode, gain),
		ACCESSOR_M(GainNode, destroy)
	});
	
	_constructor = Napi::Persistent(ctor);
	_constructor.SuppressDestruct();
	
	exports.Set("GainNode", ctor);
	
}


GainNode::GainNode(const Napi::CallbackInfo &info):
Napi::ObjectWrap<GainNode>(info),
CommonNode(info, "GainNode") { NAPI_ENV;
	
	CTOR_CHECK("GainNode");
	
	REQ_OBJ_ARG(0, context);
	
	Napi::Object that = info.This().As<Napi::Object>();
	Napi::Function ctor = _constructor.Value().As<Napi::Function>();
	Napi::Function _Super = ctor.Get("_Super").As<Napi::Function>();
	
	reset(context, std::make_shared<lab::GainNode>());
	
	std::vector<napi_value> args;
	args.push_back(context);
	_Super.Call(that, args);
	
	lab::GainNode *node = static_cast<lab::GainNode*>(
		_impl.get()
	);
	
	_gain.Reset(AudioParam::create(env, context, node->gain()));
	
}


GainNode::~GainNode() {
	_destroy();
}


void GainNode::_destroy() { DES_CHECK;
	
	_gain.Reset();
	
	CommonNode::_destroy();
	
}


JS_GETTER(GainNode::gainGetter) { THIS_CHECK;
	
	RET_VALUE(_gain.Value());
	
}
