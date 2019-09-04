#ifndef _AUDIO_DESTINATION_NODE_HPP_
#define _AUDIO_DESTINATION_NODE_HPP_

#include "common.hpp"


class AudioDestinationNode : public CommonNode<AudioDestinationNode> {
	
public:
	
	static void init(Napi::Env env, Napi::Object exports);
	static Napi::Object create(Napi::Env env, Napi::Object context, NodePtr node);
	
	explicit AudioDestinationNode(const Napi::CallbackInfo &info);
	~AudioDestinationNode();
	
	void _destroy();
	
private:
	
	static Napi::FunctionReference _constructor;
	
	uint32_t _maxChannelCount;
	
	JS_DECLARE_METHOD(destroy);
	
	JS_DECLARE_GETTER(maxChannelCount);
	
};


#endif // _AUDIO_DESTINATION_NODE_HPP_
