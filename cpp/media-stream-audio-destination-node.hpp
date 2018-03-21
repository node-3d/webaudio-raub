#ifndef _MEDIA_STREAM_AUDIO_DESTINATION_NODE_HPP_
#define _MEDIA_STREAM_AUDIO_DESTINATION_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class MediaStreamAudioDestinationNode : public AudioNode {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	MediaStreamAudioDestinationNode();
	virtual ~MediaStreamAudioDestinationNode();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoMediaStreamAudioDestinationNode; // for inheritance
	static Nan::Persistent<v8::Function> _ctorMediaStreamAudioDestinationNode;
	
	bool _isDestroyed;
	
	Nan::Persistent<v8::Object> _stream;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	static NAN_GETTER(streamGetter);
	
};


#endif // _MEDIA_STREAM_AUDIO_DESTINATION_NODE_HPP_
