#include <LabSound/LabSound.h>

#include "audio-destination-node.hpp"


Napi::FunctionReference AudioDestinationNode::_constructor;

void AudioDestinationNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_GETTER(maxChannelCount);
		ACCESSOR_M(AudioDestinationNode, destroy)
	});
	
	exports.Set("AudioDestinationNode", ctor);
	
}


Napi::Object AudioDestinationNode::create(Napi::Env env, Napi::Object context, NodePtr node) {
	Napi::Function ctor = _constructor.Value().As<Napi::Function>();
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


JS_GETTER(AudioDestinationNode::maxChannelCountGetter) { THIS_CHECK;
	
	RET_NUM(_maxChannelCount);
	
}


JS_METHOD(AudioDestinationNode::destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	RET_UNDEFINED;
	
}
