#ifndef _AUDIO_BUFFER_SOURCE_NODE_HPP_
#define _AUDIO_BUFFER_SOURCE_NODE_HPP_

#include "common.hpp"

#include "audio-scheduled-source-node.hpp"


class AudioBufferSourceNode : public CommonNode<AudioBufferSourceNode> {
	
public:
	
	static void init(Napi::Env env, Napi::Object exports);
	static Napi::Object create(Napi::Env env, Napi::Object context);
	
	explicit AudioBufferSourceNode(const Napi::CallbackInfo &info);
	~AudioBufferSourceNode();
	
	void _destroy();
	
private:
	
	static Napi::FunctionReference _constructor;
	
	Napi::ObjectReference _buffer;
	Napi::ObjectReference _playbackRate;
	Napi::ObjectReference _detune;
	
	JS_DECLARE_METHOD(destroy);
	
	JS_DECLARE_METHOD(start);
	
	JS_DECLARE_GETTER(buffer);
	JS_DECLARE_SETTER(buffer);
	
	JS_DECLARE_GETTER(playbackRate);
	
	JS_DECLARE_GETTER(detune);
	
	JS_DECLARE_GETTER(loop);
	JS_DECLARE_SETTER(loop);
	
	JS_DECLARE_GETTER(loopStart);
	JS_DECLARE_SETTER(loopStart);
	
	JS_DECLARE_GETTER(loopEnd);
	JS_DECLARE_SETTER(loopEnd);
	
};


#endif // _AUDIO_BUFFER_SOURCE_NODE_HPP_
