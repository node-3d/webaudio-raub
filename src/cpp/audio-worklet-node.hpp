#ifndef _AUDIO_WORKLET_NODE_HPP_
#define _AUDIO_WORKLET_NODE_HPP_


#include "common.hpp"


class AudioWorkletNode : public Napi::ObjectWrap<AudioWorkletNode>, private CommonNode {
	
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
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	
	
	JS_GETTER(parametersGetter);
	
	JS_GETTER(portGetter);
	
	JS_GETTER(onprocessorerrorGetter);
	JS_SETTER(onprocessorerrorSetter);
	
};


#endif // _AUDIO_WORKLET_NODE_HPP_
