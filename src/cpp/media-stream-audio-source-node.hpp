#ifndef _MEDIA_STREAM_AUDIO_SOURCE_NODE_HPP_
#define _MEDIA_STREAM_AUDIO_SOURCE_NODE_HPP_


#include "common.hpp"

#include "audio-node.hpp"


class MediaStreamAudioSourceNode : public CommonNode {
DECLARE_ES5_CLASS(MediaStreamAudioSourceNode, MediaStreamAudioSourceNode);
	
public:
	
	~MediaStreamAudioSourceNode();
	explicit MediaStreamAudioSourceNode(const Napi::CallbackInfo &info);
	
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isMediaStreamAudioSourceNode(Napi::Object obj);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
protected:
	
	MediaStreamAudioSourceNode();
	
	static Napi::FunctionReference _constructor;
	
	bool _isDestroyed;
	
	Napi::ObjectReference _mediaStream;
	
	
private:
	
	JS_DECLARE_METHOD(MediaStreamAudioSourceNode, destroy);
	JS_DECLARE_GETTER(MediaStreamAudioSourceNode, isDestroyed);
	
	
	
	JS_DECLARE_GETTER(MediaStreamAudioSourceNode, mediaStream);
	
};


#endif // _MEDIA_STREAM_AUDIO_SOURCE_NODE_HPP_
