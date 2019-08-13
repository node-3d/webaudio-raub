#ifndef _MEDIA_ELEMENT_AUDIO_SOURCE_NODE_HPP_
#define _MEDIA_ELEMENT_AUDIO_SOURCE_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class MediaElementAudioSourceNode : public AudioNode {
	
public:
	
	~MediaElementAudioSourceNode();
	
	// Public V8 init
	static void init(V8_VAR_OBJ target);
	
	static bool isMediaElementAudioSourceNode(V8_VAR_OBJ obj);
	
	// Make a new instance from C++ land
	static V8_VAR_OBJ getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	MediaElementAudioSourceNode();
	
	static V8_STORE_FT _protoMediaElementAudioSourceNode;
	static V8_STORE_FUNC _ctorMediaElementAudioSourceNode;
	
	bool _isDestroyed;
	
	V8_STORE_OBJ _mediaElement;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	static NAN_GETTER(mediaElementGetter);
	
};


#endif // _MEDIA_ELEMENT_AUDIO_SOURCE_NODE_HPP_
