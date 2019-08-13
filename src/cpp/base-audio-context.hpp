#ifndef _BASE_AUDIO_CONTEXT_HPP_
#define _BASE_AUDIO_CONTEXT_HPP_


#include <memory>

#include <event-emitter.hpp>

namespace lab { class AudioContext; };


class BaseAudioContext : public Napi::ObjectWrap<BaseAudioContext> {
	
public:
	
	typedef std::shared_ptr<lab::AudioContext> CtxPtr;
	
	~BaseAudioContext();
	
	// Public V8 init
	static void init(Napi::Object target);
	
	// Make a new instance from C++ land
	static Napi::Object getNew(Napi::Object context);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	CtxPtr getContext() const;
	void finishNew(Napi::Object context);
	
	
// Methods and props
protected:
	
	explicit BaseAudioContext(bool isOffline = false, float sampleRate = 44100.f);
	
	static V8_STORE_FT _protoBaseAudioContext; // for inheritance
	static V8_STORE_FUNC _ctorBaseAudioContext;
	
	bool _isDestroyed;
	
	V8_STORE_OBJ _destination;
	V8_STORE_OBJ _listener;
	std::string _state;
	
	CtxPtr _impl;
	
	
// System methods and props for ObjectWrap
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	static NAN_METHOD(update);
	
	static NAN_METHOD(resume);
	static NAN_METHOD(decodeAudioData);
	static NAN_METHOD(createBuffer);
	
	static NAN_METHOD(createBufferSource);
	// static NAN_METHOD(createConstantSource);
	static NAN_METHOD(createGain);
	static NAN_METHOD(createDelay);
	static NAN_METHOD(createBiquadFilter);
	static NAN_METHOD(createIIRFilter);
	// static NAN_METHOD(createWaveShaper);
	static NAN_METHOD(createPanner);
	static NAN_METHOD(createConvolver);
	// static NAN_METHOD(createDynamicsCompressor);
	// static NAN_METHOD(createAnalyser);
	static NAN_METHOD(createScriptProcessor);
	// static NAN_METHOD(createStereoPanner);
	static NAN_METHOD(createOscillator);
	static NAN_METHOD(createPeriodicWave);
	static NAN_METHOD(createChannelSplitter);
	static NAN_METHOD(createChannelMerger);
	static NAN_METHOD(createMediaElementSource);
	static NAN_METHOD(createMediaStreamSource);
	static NAN_METHOD(createMediaStreamDestination);
	
	static NAN_GETTER(destinationGetter);
	
	static NAN_GETTER(currentTimeGetter);
	
	static NAN_GETTER(sampleRateGetter);
	
	static NAN_GETTER(listenerGetter);
	
	static NAN_GETTER(stateGetter);
	
};


#endif // _BASE_AUDIO_CONTEXT_HPP_
