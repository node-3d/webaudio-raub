#ifndef _AUDIO_DESTINATION_NODE_HPP_
#define _AUDIO_DESTINATION_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"

namespace lab { class AudioDestinationNode; };


class AudioDestinationNode : public AudioNode {
	
public:
	
	typedef std::shared_ptr<lab::AudioDestinationNode> DestPtr;
	
	~AudioDestinationNode();
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	// Make a new instance from C++ land
	explicit AudioDestinationNode(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	AudioDestinationNode(Napi::Object context, DestPtr node);
	
	static Napi::FunctionReference _ctorAudioDestinationNode;
	
	bool _isDestroyed;
	
	uint32_t _maxChannelCount;
	
	DestPtr _impl;
	Napi::ObjectReference _context;
	
	
// JS methods and props, available through V8 APIs
private:
	
	JS_METHOD(newCtor);
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	
	
	JS_GETTER(maxChannelCountGetter);
	
};


#endif // _AUDIO_DESTINATION_NODE_HPP_
