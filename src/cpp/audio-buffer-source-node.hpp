#ifndef _AUDIO_BUFFER_SOURCE_NODE_HPP_
#define _AUDIO_BUFFER_SOURCE_NODE_HPP_

#include "common.hpp"

#include "audio-scheduled-source-node.hpp"


class AudioBufferSourceNode : public CommonNode {
DECLARE_ES5_CLASS(AudioBufferSourceNode, AudioBufferSourceNode);
	
public:
	
	static void init(Napi::Env env, Napi::Object exports);
	
	explicit AudioBufferSourceNode(const Napi::CallbackInfo &info);
	~AudioBufferSourceNode();
	
	void _destroy();
	
private:
	
	Napi::ObjectReference _buffer;
	Napi::ObjectReference _playbackRate;
	Napi::ObjectReference _detune;
	
	JS_DECLARE_METHOD(AudioBufferSourceNode, destroy);
	
	JS_DECLARE_METHOD(AudioBufferSourceNode, start);
	
	JS_DECLARE_GETTER(AudioBufferSourceNode, buffer);
	JS_DECLARE_SETTER(AudioBufferSourceNode, buffer);
	
	JS_DECLARE_GETTER(AudioBufferSourceNode, playbackRate);
	
	JS_DECLARE_GETTER(AudioBufferSourceNode, detune);
	
	JS_DECLARE_GETTER(AudioBufferSourceNode, loop);
	JS_DECLARE_SETTER(AudioBufferSourceNode, loop);
	
	JS_DECLARE_GETTER(AudioBufferSourceNode, loopStart);
	JS_DECLARE_SETTER(AudioBufferSourceNode, loopStart);
	
	JS_DECLARE_GETTER(AudioBufferSourceNode, loopEnd);
	JS_DECLARE_SETTER(AudioBufferSourceNode, loopEnd);
	
};


#endif // _AUDIO_BUFFER_SOURCE_NODE_HPP_
