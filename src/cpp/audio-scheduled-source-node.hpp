#ifndef _AUDIO_SCHEDULED_SOURCE_NODE_HPP_
#define _AUDIO_SCHEDULED_SOURCE_NODE_HPP_


#include "audio-node.hpp"

namespace lab { class AudioScheduledSourceNode; };


class AudioScheduledSourceNode : public AudioNode {
	
public:
	
	typedef std::shared_ptr<lab::AudioScheduledSourceNode> NodePtr;
	
	~AudioScheduledSourceNode();
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	// Make a new instance from C++ land
	explicit AudioScheduledSourceNode(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	AudioScheduledSourceNode() {} // fake, TODO: remove
	AudioScheduledSourceNode(Napi::Object context, NodePtr node);
	
	static Napi::FunctionReference _ctorAudioScheduledSourceNode;
	
	bool _isDestroyed;
	
	void onEnded();
	
	
// JS methods and props, available through V8 APIs
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	JS_METHOD(start);
	JS_METHOD(stop);
	
};


#endif // _AUDIO_SCHEDULED_SOURCE_NODE_HPP_
