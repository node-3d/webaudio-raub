#ifndef _AUDIO_SCHEDULED_SOURCE_NODE_HPP_
#define _AUDIO_SCHEDULED_SOURCE_NODE_HPP_


#include "audio-node.hpp"

namespace lab { class AudioScheduledSourceNode; };


class AudioScheduledSourceNode : public Napi::ObjectWrap<AudioScheduledSourceNode>, private CommonNode {
	
public:
	
	typedef std::shared_ptr<lab::AudioScheduledSourceNode> NodePtr;
	
	~AudioScheduledSourceNode();
	explicit AudioScheduledSourceNode(const Napi::CallbackInfo &info);
	
	static void init(Napi::Env env, Napi::Object exports);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
protected:
	
	AudioScheduledSourceNode() {} // fake, TODO: remove
	AudioScheduledSourceNode(Napi::Object context, NodePtr node);
	
	static Napi::FunctionReference _constructor;
	
	bool _isDestroyed;
	
	void onEnded();
	
	
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	JS_METHOD(start);
	JS_METHOD(stop);
	
};


#endif // _AUDIO_SCHEDULED_SOURCE_NODE_HPP_
