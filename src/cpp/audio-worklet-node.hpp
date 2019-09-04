#ifndef _AUDIO_WORKLET_NODE_HPP_
#define _AUDIO_WORKLET_NODE_HPP_


#include "common.hpp"


class AudioWorkletNode : public CommonNode<AudioWorkletNode> {
	
public:
	
	~AudioWorkletNode();
	explicit AudioWorkletNode(const Napi::CallbackInfo &info);
	
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isAudioWorkletNode(Napi::Object obj);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
protected:
	
	AudioWorkletNode();
	
	static Napi::FunctionReference _constructor;
	
	bool _isDestroyed;
	
	Napi::ObjectReference _parameters;
	Napi::ObjectReference _port;
	V8_STORE_FUNC _onprocessorerror;
	
	
private:
	
	JS_DECLARE_METHOD(destroy);
	JS_DECLARE_GETTER(isDestroyed);
	
	
	
	JS_DECLARE_GETTER(parameters);
	
	JS_DECLARE_GETTER(port);
	
	JS_DECLARE_GETTER(onprocessorerror);
	JS_DECLARE_SETTER(onprocessorerror);
	
};


#endif // _AUDIO_WORKLET_NODE_HPP_
