#include "gain-node.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"


IMPLEMENT_ES5_CLASS(GainNode);

void GainNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_GETTER(gain);
	JS_ASSIGN_METHOD(destroy);
	
	exports.Set("GainNode", ctor);
	
}


GainNode::GainNode(const Napi::CallbackInfo &info):
CommonNode(info.This(), "GainNode") { NAPI_ENV;
	
	REQ_OBJ_ARG(0, context);
	REQ_FUN_ARG(1, paramCtor);
	
	reset(context, std::make_shared<lab::GainNode>());
	
	lab::GainNode *node = static_cast<lab::GainNode*>(
		_impl.get()
	);
	
	napi_value argv[2];
	argv[0] = context;
	
	argv[1] = JS_EXT(&node->gain());
	_gain.Reset(paramCtor.New(2, argv), 1);
	
	argv[1] = JS_EXT(&_impl);
	super(info, 2, argv);
	
}


GainNode::~GainNode() {
	_destroy();
}


void GainNode::_destroy() { DES_CHECK;
	
	_gain.Reset();
	
	CommonNode::_destroy();
	
}


JS_IMPLEMENT_GETTER(GainNode, gain) { THIS_CHECK;
	
	RET_VALUE(_gain.Value());
	
}


JS_IMPLEMENT_METHOD(GainNode, destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	RET_UNDEFINED;
	
}
