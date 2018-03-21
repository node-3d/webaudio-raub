#ifndef _AUDIO_DESTINATION_NODE_HPP_
#define _AUDIO_DESTINATION_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class AudioDestinationNode : public AudioNode {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	void _destroy();
	
	
// Methods and props
protected:
	
	AudioDestinationNode();
	virtual ~AudioDestinationNode();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoAudioDestinationNode; // for inheritance
	static Nan::Persistent<v8::Function> _ctorAudioDestinationNode;
	
	
// System methods and props for ObjectWrap
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	static NAN_GETTER(maxChannelCountGetter);
	
	
private:
	
	bool _isDestroyed;
	
	unsigned int _maxChannelCount;
	
};


#endif // _AUDIO_DESTINATION_NODE_HPP_
