#ifndef _MEDIA_STREAM_AUDIO_SOURCE_NODE_HPP_
#define _MEDIA_STREAM_AUDIO_SOURCE_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class MediaStreamAudioSourceNode : public Napi::ObjectWrap<MediaStreamAudioSourceNode> {
	
public:
	
	~MediaStreamAudioSourceNode();
	MediaStreamAudioSourceNode(const Napi::CallbackInfo &info);
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isMediaStreamAudioSourceNode(Napi::Object obj);
	
	// Make a new instance from C++ land
	explicit MediaStreamAudioSourceNode(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
protected:
	
	MediaStreamAudioSourceNode();
	
	static Napi::FunctionReference _ctorMediaStreamAudioSourceNode;
	
	bool _isDestroyed;
	
	Napi::ObjectReference _mediaStream;
	
	
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	
	
	JS_GETTER(mediaStreamGetter);
	
};


#endif // _MEDIA_STREAM_AUDIO_SOURCE_NODE_HPP_
