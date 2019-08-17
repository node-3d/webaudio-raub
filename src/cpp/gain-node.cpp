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

GainNode *GainNode::create(Napi::Env env) {
	Napi::Function ctor = _constructor.Value().As<Napi::Function>();
	return ctor.New();
}


GainNode::GainNode(const Napi::CallbackInfo &info):
Napi::ObjectWrap<GainNode>(info) { NAPI_ENV;
	
	CTOR_CHECK("GainNode");
	
	REQ_OBJ_ARG(0, context);
	
	lab::GainNode *node = new lab::GainNode();
	
	reset(context, NodePtr(node));
	
	_gain.Reset(AudioParam::create(context, node->gain()));
	
}


void GainNode::_destroy() { DES_CHECK;
	
	_gain.Reset();
	
	CommonNode::_destroy();
	
}


JS_GETTER(GainNode::gainGetter) { THIS_CHECK;
	
	RET_VALUE(_gain.Value());
	
}
