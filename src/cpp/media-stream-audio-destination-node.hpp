#ifndef _MEDIA_STREAM_AUDIO_DESTINATION_NODE_HPP_
#define _MEDIA_STREAM_AUDIO_DESTINATION_NODE_HPP_


#include "common.hpp"

#include "audio-node.hpp"


class MediaStreamAudioDestinationNode : public CommonNode<MediaStreamAudioDestinationNode> {
	
public:
	
	~MediaStreamAudioDestinationNode();
	explicit MediaStreamAudioDestinationNode(const Napi::CallbackInfo &info);
	
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isMediaStreamAudioDestinationNode(Napi::Object obj);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
protected:
	
	MediaStreamAudioDestinationNode();
	
	static Napi::FunctionReference _constructor;
	
	bool _isDestroyed;
	
	Napi::ObjectReference _stream;
	
	
private:
	
	JS_DECLARE_METHOD(destroy);
	JS_DECLARE_GETTER(isDestroyed);
	
	
	
	JS_DECLARE_GETTER(stream);
	
};


#endif // _MEDIA_STREAM_AUDIO_DESTINATION_NODE_HPP_
