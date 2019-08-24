#include <LabSound/LabSound.h>

#include "audio-scheduled-source-node.hpp"


Napi::FunctionReference AudioScheduledSourceNode::_constructor;

void AudioScheduledSourceNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "AudioScheduledSourceNode", {
		ACCESSOR_M(AudioScheduledSourceNode, stop),
		ACCESSOR_M(AudioScheduledSourceNode, start),
		ACCESSOR_M(AudioScheduledSourceNode, destroy),
		ACCESSOR_R(AudioScheduledSourceNode, isDestroyed)
	});
	
	_constructor = Napi::Persistent(ctor);
	_constructor.SuppressDestruct();
	
	exports.Set("AudioScheduledSourceNode", ctor);
	
}


AudioScheduledSourceNode::AudioScheduledSourceNode(const Napi::CallbackInfo &info):
Napi::ObjectWrap<AudioScheduledSourceNode>(info),
CommonNode(info, "AudioScheduledSourceNode") { NAPI_ENV;
		
	CTOR_CHECK("AudioScheduledSourceNode");
	
	REQ_OBJ_ARG(0, context);
	REQ_EXT_ARG(1, extNode);
	
	NodePtr *nodePtr = reinterpret_cast<NodePtr *>(extNode.Data());
	
	reset(context, *nodePtr);
	
	Napi::Object that = info.This().As<Napi::Object>();
	Napi::Function ctor = _constructor.Value().As<Napi::Function>();
	Napi::Function _Super = ctor.Get("_Super").As<Napi::Function>();
	
	std::vector<napi_value> args;
	args.push_back(context);
	_Super.Call(that, args);
	
	lab::AudioScheduledSourceNode *node = static_cast<lab::AudioScheduledSourceNode*>(
		_impl.get()
	);
	
	node->setOnEnded(std::bind(&AudioScheduledSourceNode::onEnded, this));
	
}


AudioScheduledSourceNode::~AudioScheduledSourceNode() {
	_destroy();
}


void AudioScheduledSourceNode::onEnded() {
	
	emitAsync("ended");
	
}


void AudioScheduledSourceNode::_destroy() { DES_CHECK;
	
	lab::AudioScheduledSourceNode *node = static_cast<lab::AudioScheduledSourceNode*>(
		_impl.get()
	);
	
	node->setOnEnded(nullptr);
	
	CommonNode::_destroy();
	
}


// ------ Methods and props


JS_METHOD(AudioScheduledSourceNode::start) { THIS_CHECK;
	
	REQ_DOUBLE_ARG(0, when);
	
	lab::AudioScheduledSourceNode *node = static_cast<lab::AudioScheduledSourceNode*>(
		_impl.get()
	);
	
	node->start(when);
	
}


JS_METHOD(AudioScheduledSourceNode::stop) { THIS_CHECK;
	
	REQ_DOUBLE_ARG(0, when);
	
	lab::AudioScheduledSourceNode *node = static_cast<lab::AudioScheduledSourceNode*>(
		_impl.get()
	);
	
	node->stop(when);
	
}


JS_METHOD(AudioScheduledSourceNode::destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	
}
