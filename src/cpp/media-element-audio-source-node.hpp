#ifndef _MEDIA_ELEMENT_AUDIO_SOURCE_NODE_HPP_
#define _MEDIA_ELEMENT_AUDIO_SOURCE_NODE_HPP_


#include "common.hpp"

#include "audio-node.hpp"


class MediaElementAudioSourceNode : public CommonNode<MediaElementAudioSourceNode> {
	
public:
	
	~MediaElementAudioSourceNode();
	explicit MediaElementAudioSourceNode(const Napi::CallbackInfo &info);
	
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isMediaElementAudioSourceNode(Napi::Object obj);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
protected:
	
	MediaElementAudioSourceNode();
	
	static Napi::FunctionReference _constructor;
	
	bool _isDestroyed;
	
	Napi::ObjectReference _mediaElement;
	
	
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	
	
	JS_GETTER(mediaElementGetter);
	
};


#endif // _MEDIA_ELEMENT_AUDIO_SOURCE_NODE_HPP_
