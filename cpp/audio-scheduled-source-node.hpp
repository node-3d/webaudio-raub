#ifndef _AUDIO_SCHEDULED_SOURCE_NODE_HPP_
#define _AUDIO_SCHEDULED_SOURCE_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"

namespace lab { class AudioScheduledSourceNode; };


class AudioScheduledSourceNode : public AudioNode {
	
public:
	
	typedef std::shared_ptr<lab::AudioScheduledSourceNode> NodePtr;
	
	// Public V8 init
	static void init(V8_VAR_OBJ target);
	
	// Make a new instance from C++ land
	static V8_VAR_OBJ getNew(V8_VAR_OBJ context, NodePtr node);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	AudioScheduledSourceNode() {} // fake, TODO: remove
	AudioScheduledSourceNode(V8_VAR_OBJ context, NodePtr node);
	virtual ~AudioScheduledSourceNode();
	
	static V8_STORE_FT _protoAudioScheduledSourceNode;
	static V8_STORE_FUNC _ctorAudioScheduledSourceNode;
	
	bool _isDestroyed;
	
	V8_STORE_FUNC _onended;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	static NAN_METHOD(start);
	static NAN_METHOD(stop);
	
	static NAN_GETTER(onendedGetter);
	static NAN_SETTER(onendedSetter);
	
};


#endif // _AUDIO_SCHEDULED_SOURCE_NODE_HPP_
