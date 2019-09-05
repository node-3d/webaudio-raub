#include <LabSound/LabSound.h>

#include "delay-node.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"


IMPLEMENT_ES5_CLASS(DelayNode);

void DelayNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_GETTER(delayTime);
	JS_ASSIGN_METHOD(destroy);
	
	exports.Set("DelayNode", ctor);
	
}


DelayNode::DelayNode(const Napi::CallbackInfo &info): 
CommonNode<DelayNode>(info, "DelayNode") { NAPI_ENV;
	
	REQ_OBJ_ARG(0, context);
	REQ_DOUBLE_ARG(1, delay);
	
	AudioContext *audioContext = Napi::ObjectWrap<AudioContext>::Unwrap(context);
	float sampleRate = audioContext->getCtx()->sampleRate();
	
	reset(context, std::make_shared<lab::DelayNode>(sampleRate, delay));
	
	lab::DelayNode *node = static_cast<lab::DelayNode*>(
		_impl.get()
	);
	
	_delayTime.Reset(AudioParam::create(env, context, node->delayTime()));
	
	Napi::Value argv[] = {
		static_cast<Napi::Value>(context),
		static_cast<Napi::Value>(JS_NUM(reinterpret_cast<size_t>(node)))
	};
	super(info, 2, argv);
	
}


DelayNode::~DelayNode() {
	_destroy();
}


void DelayNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	CommonNode::_destroy();
	
}


JS_IMPLEMENT_GETTER(DelayNode, delayTime) { THIS_CHECK;
	
	RET_VALUE(_delayTime.Value());
	
}


JS_IMPLEMENT_METHOD(DelayNode, destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	RET_UNDEFINED;
	
}
