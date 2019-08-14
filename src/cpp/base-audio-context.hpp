#ifndef _BASE_AUDIO_CONTEXT_HPP_
#define _BASE_AUDIO_CONTEXT_HPP_


#include <memory>

#include <addon-tools.hpp>

namespace lab { class AudioContext; };


class BaseAudioContext : public Napi::ObjectWrap<BaseAudioContext> {
	
public:
	
	typedef std::shared_ptr<lab::AudioContext> CtxPtr;
	
	~BaseAudioContext();
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	// Make a new instance from C++ land
	explicit BaseAudioContext(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	CtxPtr getContext() const;
	void finishNew(Napi::Object context);
	
	
// Methods and props
protected:
	
	explicit BaseAudioContext(bool isOffline = false, float sampleRate = 44100.f);
	
	static V8_STORE_FT _protoBaseAudioContext; // for inheritance
	static Napi::FunctionReference _ctorBaseAudioContext;
	
	bool _isDestroyed;
	
	Napi::ObjectReference _destination;
	Napi::ObjectReference _listener;
	std::string _state;
	
	CtxPtr _impl;
	
	
// System methods and props for ObjectWrap
private:
	
	JS_METHOD(newCtor);
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	JS_METHOD(update);
	
	JS_METHOD(resume);
	JS_METHOD(decodeAudioData);
	JS_METHOD(createBuffer);
	
	JS_METHOD(createBufferSource);
	// JS_METHOD(createConstantSource);
	JS_METHOD(createGain);
	JS_METHOD(createDelay);
	JS_METHOD(createBiquadFilter);
	JS_METHOD(createIIRFilter);
	// JS_METHOD(createWaveShaper);
	JS_METHOD(createPanner);
	JS_METHOD(createConvolver);
	// JS_METHOD(createDynamicsCompressor);
	// JS_METHOD(createAnalyser);
	JS_METHOD(createScriptProcessor);
	// JS_METHOD(createStereoPanner);
	JS_METHOD(createOscillator);
	JS_METHOD(createPeriodicWave);
	JS_METHOD(createChannelSplitter);
	JS_METHOD(createChannelMerger);
	JS_METHOD(createMediaElementSource);
	JS_METHOD(createMediaStreamSource);
	JS_METHOD(createMediaStreamDestination);
	
	JS_GETTER(destinationGetter);
	
	JS_GETTER(currentTimeGetter);
	
	JS_GETTER(sampleRateGetter);
	
	JS_GETTER(listenerGetter);
	
	JS_GETTER(stateGetter);
	
};


#endif // _BASE_AUDIO_CONTEXT_HPP_
