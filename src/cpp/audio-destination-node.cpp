#include <LabSound/LabSound.h>

#include "audio-destination-node.hpp"


IMPLEMENT_ES5_CLASS(AudioDestinationNode);

void AudioDestinationNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_GETTER(maxChannelCount);
	JS_ASSIGN_METHOD(destroy);
	
	exports.Set("AudioDestinationNode", ctor);
	
}


Napi::Object AudioDestinationNode::create(Napi::Env env, Napi::Object context, NodePtr node) {
	Napi::Function ctor = _ctorEs5.Value().As<Napi::Function>();
	std::vector<napi_value> args;
	args.push_back(context);
	args.push_back(JS_EXT(&node));
	return ctor.New(args);
}


AudioDestinationNode::AudioDestinationNode(const Napi::CallbackInfo &info):
CommonNode<AudioDestinationNode>(info, "AudioDestinationNode") { NAPI_ENV;
	super(info);
	
	REQ_OBJ_ARG(0, context);
	REQ_EXT_ARG(1, extNode);
	
	NodePtr *node = reinterpret_cast<NodePtr *>(extNode.Data());
	
	reset(context, *node);
	
}


AudioDestinationNode::~AudioDestinationNode() {
	_destroy();
}


void AudioDestinationNode::_destroy() { DES_CHECK;
	
	CommonNode::_destroy();
	
}


JS_IMPLEMENT_GETTER(AudioDestinationNode, maxChannelCount) { THIS_CHECK;
	
	RET_NUM(_maxChannelCount);
	
}


JS_IMPLEMENT_METHOD(AudioDestinationNode, destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	RET_UNDEFINED;
	
}
