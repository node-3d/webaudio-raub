#ifndef _MEDIA_STREAM_AUDIO_SOURCE_NODE_HPP_
#define _MEDIA_STREAM_AUDIO_SOURCE_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class MediaStreamAudioSourceNode : public AudioNode {
	
public:
	
	// Public V8 init
	static void init(V8_VAR_OBJ target);
	
	static bool isMediaStreamAudioSourceNode(V8_VAR_OBJ obj);
	
	// Make a new instance from C++ land
	static V8_VAR_OBJ getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	MediaStreamAudioSourceNode();
	virtual ~MediaStreamAudioSourceNode();
	
	static V8_STORE_FT _protoMediaStreamAudioSourceNode;
	static V8_STORE_FUNC _ctorMediaStreamAudioSourceNode;
	
	bool _isDestroyed;
	
	V8_STORE_OBJ _mediaStream;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	static NAN_GETTER(mediaStreamGetter);
	
};


#endif // _MEDIA_STREAM_AUDIO_SOURCE_NODE_HPP_
