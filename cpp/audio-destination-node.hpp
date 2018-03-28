#ifndef _AUDIO_DESTINATION_NODE_HPP_
#define _AUDIO_DESTINATION_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"

namespace lab { class AudioDestinationNode; };


class AudioDestinationNode : public AudioNode {
	
public:
	
	typedef std::shared_ptr<lab::AudioDestinationNode> DestPtr;
	
	// Public V8 init
	static void init(V8_VAR_OBJ target);
	
	// Make a new instance from C++ land
	static V8_VAR_OBJ getNew(V8_VAR_OBJ context, DestPtr node);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	AudioDestinationNode(V8_VAR_OBJ context, DestPtr node);
	virtual ~AudioDestinationNode();
	
	static V8_STORE_FT _protoAudioDestinationNode;
	static V8_STORE_FUNC _ctorAudioDestinationNode;
	
	bool _isDestroyed;
	
	unsigned int _maxChannelCount;
	
	DestPtr _impl;
	V8_STORE_OBJ _context;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	static NAN_GETTER(maxChannelCountGetter);
	
};


#endif // _AUDIO_DESTINATION_NODE_HPP_
