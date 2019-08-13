#ifndef _AUDIO_SCHEDULED_SOURCE_NODE_HPP_
#define _AUDIO_SCHEDULED_SOURCE_NODE_HPP_


#include "audio-node.hpp"

namespace lab { class AudioScheduledSourceNode; };


class AudioScheduledSourceNode : public AudioNode {
	
public:
	
	typedef std::shared_ptr<lab::AudioScheduledSourceNode> NodePtr;
	
	~AudioScheduledSourceNode();
	
	// Public V8 init
	static void init(Napi::Object target);
	
	// Make a new instance from C++ land
	static Napi::Object getNew(Napi::Object context, NodePtr node);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	AudioScheduledSourceNode() {} // fake, TODO: remove
	AudioScheduledSourceNode(Napi::Object context, NodePtr node);
	
	static V8_STORE_FT _protoAudioScheduledSourceNode;
	static V8_STORE_FUNC _ctorAudioScheduledSourceNode;
	
	bool _isDestroyed;
	
	void onEnded();
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	static NAN_METHOD(start);
	static NAN_METHOD(stop);
	
};


#endif // _AUDIO_SCHEDULED_SOURCE_NODE_HPP_
