#ifndef _MEDIA_ELEMENT_AUDIO_SOURCE_NODE_HPP_
#define _MEDIA_ELEMENT_AUDIO_SOURCE_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class MediaElementAudioSourceNode : public AudioNode {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	void _destroy();
	
	
// Methods and props
protected:
	
	MediaElementAudioSourceNode();
	virtual ~MediaElementAudioSourceNode();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoMediaElementAudioSourceNode; // for inheritance
	static Nan::Persistent<v8::Function> _ctorMediaElementAudioSourceNode;
	
	
// System methods and props for ObjectWrap
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	static NAN_GETTER(mediaElementGetter);
	
	
private:
	
	bool _isDestroyed;
	
	Nan::Persistent<v8::Object> _mediaElement;
	
};


#endif // _MEDIA_ELEMENT_AUDIO_SOURCE_NODE_HPP_
