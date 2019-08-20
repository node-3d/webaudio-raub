#ifndef _AUDIO_NODE_HPP_
#define _AUDIO_NODE_HPP_

#include "common.hpp"

#include <LabSound/core/AudioNode.h>


class AudioNode : public Napi::ObjectWrap<AudioNode>, public CommonNode {
	
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
	
	JS_METHOD(destroy);
	
	JS_METHOD(connect);
	JS_METHOD(disconnect);
	
	JS_GETTER(contextGetter);
	
	JS_GETTER(numberOfInputsGetter);
	
	JS_GETTER(numberOfOutputsGetter);
	
	JS_GETTER(channelCountGetter);
	JS_SETTER(channelCountSetter);
	
	JS_GETTER(channelCountModeGetter);
	JS_SETTER(channelCountModeSetter);
	
	JS_GETTER(channelInterpretationGetter);
	JS_SETTER(channelInterpretationSetter);
	
};


#endif // _AUDIO_NODE_HPP_
