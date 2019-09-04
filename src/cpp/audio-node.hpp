#ifndef _AUDIO_NODE_HPP_
#define _AUDIO_NODE_HPP_

#include "common.hpp"

#include <LabSound/core/AudioNode.h>


class AudioNode : public CommonNode<AudioNode> {
	
public:
	
	static void init(Napi::Env env, Napi::Object exports);
	static bool isAudioNode(Napi::Object obj);
	
	~AudioNode();
	explicit AudioNode(const Napi::CallbackInfo &info);
	
	void _destroy();
	
private:
	
	static Napi::FunctionReference _constructor;
	
	uint32_t _channelCount;
	std::string _channelCountMode;
	std::string _channelInterpretation;
	
	JS_DECLARE_METHOD(destroy);
	
	JS_DECLARE_METHOD(connect);
	JS_DECLARE_METHOD(disconnect);
	
	JS_DECLARE_GETTER(context);
	
	JS_DECLARE_GETTER(numberOfInputs);
	
	JS_DECLARE_GETTER(numberOfOutputs);
	
	JS_DECLARE_GETTER(channelCount);
	JS_DECLARE_SETTER(channelCount);
	
	JS_DECLARE_GETTER(channelCountMode);
	JS_DECLARE_SETTER(channelCountMode);
	
	JS_DECLARE_GETTER(channelInterpretation);
	JS_DECLARE_SETTER(channelInterpretation);
	
};


#endif // _AUDIO_NODE_HPP_
