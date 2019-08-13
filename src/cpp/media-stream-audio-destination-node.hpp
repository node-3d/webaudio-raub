#ifndef _MEDIA_STREAM_AUDIO_DESTINATION_NODE_HPP_
#define _MEDIA_STREAM_AUDIO_DESTINATION_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class MediaStreamAudioDestinationNode : public AudioNode {
	
public:
	
	~MediaStreamAudioDestinationNode();
	
	// Public V8 init
	static void init(Napi::Object target);
	
	static bool isMediaStreamAudioDestinationNode(Napi::Object obj);
	
	// Make a new instance from C++ land
	static Napi::Object getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	MediaStreamAudioDestinationNode();
	
	static V8_STORE_FT _protoMediaStreamAudioDestinationNode;
	static V8_STORE_FUNC _ctorMediaStreamAudioDestinationNode;
	
	bool _isDestroyed;
	
	V8_STORE_OBJ _stream;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	static NAN_GETTER(streamGetter);
	
};


#endif // _MEDIA_STREAM_AUDIO_DESTINATION_NODE_HPP_
