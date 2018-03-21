#ifndef _BASE_AUDIO_CONTEXT_HPP_
#define _BASE_AUDIO_CONTEXT_HPP_


#include <memory>

#include <event-emitter.hpp>

namespace lab { class AudioContext; };


class BaseAudioContext : public EventEmitter {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	void _destroy();
	
	
// Methods and props
protected:
	
	BaseAudioContext(bool isOffline = false, float sampleRate = 44100.f);
	virtual ~BaseAudioContext();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoBaseAudioContext; // for inheritance
	static Nan::Persistent<v8::Function> _ctorBaseAudioContext;
	
	
// System methods and props for ObjectWrap
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	static NAN_METHOD(createBuffer);
	static NAN_METHOD(decodeAudioData);
	static NAN_METHOD(createBufferSource);
	static NAN_METHOD(createConstantSource);
	static NAN_METHOD(createGain);
	static NAN_METHOD(createDelay);
	static NAN_METHOD(createBiquadFilter);
	static NAN_METHOD(createIIRFilter);
	static NAN_METHOD(createWaveShaper);
	static NAN_METHOD(createPanner);
	static NAN_METHOD(createConvolver);
	static NAN_METHOD(createDynamicsCompressor);
	static NAN_METHOD(createAnalyser);
	static NAN_METHOD(createScriptProcessor);
	static NAN_METHOD(createStereoPanner);
	static NAN_METHOD(createOscillator);
	static NAN_METHOD(createPeriodicWave);
	static NAN_METHOD(createChannelSplitter);
	static NAN_METHOD(createChannelMerger);
	static NAN_METHOD(resume);
	static NAN_METHOD(createMediaElementSource);
	static NAN_METHOD(createMediaStreamSource);
	static NAN_METHOD(createMediaStreamDestination);
	
	static NAN_GETTER(destinationGetter);
	
	static NAN_GETTER(currentTimeGetter);
	
	static NAN_GETTER(sampleRateGetter);
	
	static NAN_GETTER(listenerGetter);
	
	static NAN_GETTER(stateGetter);
	
	
private:
	
	bool _isDestroyed;
	
	Nan::Persistent<v8::Object> _destination;
	double _currentTime;
	float _sampleRate;
	Nan::Persistent<v8::Object> _listener;
	std::string _state;
	
	std::unique_ptr<lab::AudioContext> _impl;
	
};


#endif // _BASE_AUDIO_CONTEXT_HPP_
