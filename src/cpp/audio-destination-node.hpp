#ifndef _AUDIO_DESTINATION_NODE_HPP_
#define _AUDIO_DESTINATION_NODE_HPP_

#include "common.hpp"


class AudioDestinationNode : public Napi::ObjectWrap<AudioDestinationNode>, private CommonNode {
	
public:
	
	static void init(Napi::Env env, Napi::Object exports);
	static Napi::Object create(Napi::Env env, Napi::Object context, NodePtr node);
	
	explicit ConvolverNode(const Napi::CallbackInfo &info);
	~ConvolverNode();
	
	void _destroy();
	
private:
	
	static Napi::FunctionReference _constructor;
	
	uint32_t _maxChannelCount;
	
	JS_METHOD(destroy);
	
	JS_GETTER(maxChannelCountGetter);
	
};


#endif // _AUDIO_DESTINATION_NODE_HPP_
