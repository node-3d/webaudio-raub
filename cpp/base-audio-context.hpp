#ifndef _BASE_AUDIO_CONTEXT_HPP_
#define _BASE_AUDIO_CONTEXT_HPP_


#include <addon-tools.hpp>


class BaseAudioContext : public Nan::ObjectWrap {
	
// Public V8 init
public:
	
	static void init(v8::Local<v8::Object> target);
	
	
// Public C++ methods: in-engine calls
public:
	
	
// Protected C++ methods: implementing JS calls
protected:
	
	BaseAudioContext();
	virtual ~BaseAudioContext();
	
	
// JS methods and props
protected:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	
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
	
	
	static NAN_GETTER(isDestroyedGetter);
	
	
	static NAN_GETTER(destinationGetter);
	

	static NAN_GETTER(currentTimeGetter);
	

	static NAN_GETTER(sampleRateGetter);
	

	static NAN_GETTER(listenerGetter);
	

	static NAN_GETTER(stateGetter);
	
	
// Actual destruction-handler
private:
	
	void _destroy();
	
	
// Stored JS constructor and helpers
private:
	
	static Nan::Persistent<v8::Function> _constructor;
	
	
public:
	
	static Nan::Persistent<v8::FunctionTemplate> protorype;
	
	
// This-state storage
private:
	
	bool _isDestroyed;
	
	Nan::Persistent<v8::Object> _destination;
	double _currentTime;
	float _sampleRate;
	Nan::Persistent<v8::Object> _listener;
	std::string _state;
	
};


#endif // _BASE_AUDIO_CONTEXT_HPP_
