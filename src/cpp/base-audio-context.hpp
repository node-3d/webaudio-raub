#ifndef _BASE_AUDIO_CONTEXT_HPP_
#define _BASE_AUDIO_CONTEXT_HPP_

#include "common.hpp"


class BaseAudioContext : public Napi::ObjectWrap<BaseAudioContext>, public CommonCtx {
	
public:
	
	static void init(Napi::Env env, Napi::Object exports);
	
	explicit BaseAudioContext(const Napi::CallbackInfo &info);
	~BaseAudioContext();
	
	
private:
	
	static Napi::FunctionReference _constructor;
	
	Napi::ObjectReference _destination;
	Napi::ObjectReference _listener;
	std::string _state;
	
	JS_METHOD(update);
	
	JS_METHOD(resume);
	JS_METHOD(decodeAudioData);
	// JS_METHOD(createBuffer);
	
	// JS_METHOD(createBufferSource);
	// // JS_METHOD(createConstantSource);
	// JS_METHOD(createGain);
	// JS_METHOD(createDelay);
	// JS_METHOD(createBiquadFilter);
	// JS_METHOD(createIIRFilter);
	// // JS_METHOD(createWaveShaper);
	// JS_METHOD(createPanner);
	// JS_METHOD(createConvolver);
	// // JS_METHOD(createDynamicsCompressor);
	// // JS_METHOD(createAnalyser);
	// JS_METHOD(createScriptProcessor);
	// // JS_METHOD(createStereoPanner);
	// JS_METHOD(createOscillator);
	// JS_METHOD(createPeriodicWave);
	// JS_METHOD(createChannelSplitter);
	// JS_METHOD(createChannelMerger);
	// JS_METHOD(createMediaElementSource);
	// JS_METHOD(createMediaStreamSource);
	// JS_METHOD(createMediaStreamDestination);
	
	JS_GETTER(destinationGetter);
	
	JS_GETTER(currentTimeGetter);
	
	JS_GETTER(sampleRateGetter);
	
	JS_GETTER(listenerGetter);
	
	JS_GETTER(stateGetter);
	
};


#endif // _BASE_AUDIO_CONTEXT_HPP_
