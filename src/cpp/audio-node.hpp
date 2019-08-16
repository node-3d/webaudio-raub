#ifndef _AUDIO_NODE_HPP_
#define _AUDIO_NODE_HPP_


#include <memory>

#include <addon-tools.hpp>

namespace lab { class AudioNode; };
#include <LabSound/core/AudioNode.h>


class AudioNode : public Napi::ObjectWrap<AudioNode> {
	
public:
	
	typedef std::shared_ptr<lab::AudioNode> NodePtr;
	
	~AudioNode();
	AudioNode(const Napi::CallbackInfo &info);
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isAudioNode(Napi::Object obj);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	NodePtr getNode() const;
	
	
protected:
	
	static Napi::FunctionReference _constructor;
	
	bool _isDestroyed;
	
	uint32_t _channelCount;
	std::string _channelCountMode;
	std::string _channelInterpretation;
	
	NodePtr _impl;
	Napi::ObjectReference _context;
	
	
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
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
