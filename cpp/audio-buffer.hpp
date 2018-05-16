#ifndef _AUDIO_BUFFER_HPP_
#define _AUDIO_BUFFER_HPP_


#include <memory>

#include <addon-tools.hpp>

namespace lab { class AudioBus; };


class AudioBuffer : public Nan::ObjectWrap {
	
public:
	
	typedef std::shared_ptr<lab::AudioBus> BusPtr;
	
	~AudioBuffer();
	
	// Public V8 init
	static void init(V8_VAR_OBJ target);
	
	// Make a new instance from C++ land
	static V8_VAR_OBJ getNew(BusPtr bus);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	BusPtr getBus() const;
	
	
// Methods and props, available for children
protected:
	
	AudioBuffer();
	explicit AudioBuffer(BusPtr bus);
	
	static V8_STORE_FT _protoAudioBuffer;
	static V8_STORE_FUNC _ctorAudioBuffer;
	
	bool _isDestroyed;
	
	int _length;
	double _duration;
	float _sampleRate;
	unsigned int _numberOfChannels;
	
	BusPtr _impl;
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	static NAN_METHOD(getChannelData);
	static NAN_METHOD(copyFromChannel);
	static NAN_METHOD(copyToChannel);
	
	static NAN_GETTER(lengthGetter);
	
	static NAN_GETTER(durationGetter);
	
	static NAN_GETTER(sampleRateGetter);
	
	static NAN_GETTER(numberOfChannelsGetter);
	
};


#endif // _AUDIO_BUFFER_HPP_
