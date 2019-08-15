#ifndef _MEDIA_STREAM_AUDIO_DESTINATION_NODE_HPP_
#define _MEDIA_STREAM_AUDIO_DESTINATION_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class MediaStreamAudioDestinationNode : public Napi::ObjectWrap<MediaStreamAudioDestinationNode> {
	
public:
	
	~MediaStreamAudioDestinationNode();
	MediaStreamAudioDestinationNode(const Napi::CallbackInfo &info);
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isMediaStreamAudioDestinationNode(Napi::Object obj);
	
	// Make a new instance from C++ land
	explicit MediaStreamAudioDestinationNode(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
protected:
	
	MediaStreamAudioDestinationNode();
	
	static Napi::FunctionReference _ctorMediaStreamAudioDestinationNode;
	
	bool _isDestroyed;
	
	Napi::ObjectReference _stream;
	
	
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	
	
	JS_GETTER(streamGetter);
	
};


#endif // _MEDIA_STREAM_AUDIO_DESTINATION_NODE_HPP_
