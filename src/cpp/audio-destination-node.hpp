#ifndef _AUDIO_DESTINATION_NODE_HPP_
#define _AUDIO_DESTINATION_NODE_HPP_


#include "common.hpp"

#include "audio-node.hpp"

namespace lab { class AudioDestinationNode; };


class AudioDestinationNode : public Napi::ObjectWrap<AudioDestinationNode>, private CommonNode {
	
public:
	
	typedef std::shared_ptr<lab::AudioDestinationNode> DestPtr;
	
	~AudioDestinationNode();
	explicit AudioDestinationNode(const Napi::CallbackInfo &info);
	
	static void init(Napi::Env env, Napi::Object exports);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
protected:
	
	AudioDestinationNode(Napi::Object context, DestPtr node);
	
	static Napi::FunctionReference _constructor;
	
	bool _isDestroyed;
	
	uint32_t _maxChannelCount;
	
	DestPtr _impl;
	Napi::ObjectReference _context;
	
	
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	
	
	JS_GETTER(maxChannelCountGetter);
	
};


#endif // _AUDIO_DESTINATION_NODE_HPP_
