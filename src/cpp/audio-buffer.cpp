#include <memory>

#include <LabSound/core/AudioBus.h>

#include "audio-buffer.hpp"
#include "audio-context.hpp"

#include "common.hpp"


// ------ Constructor and Destructor


AudioBuffer::AudioBuffer(const Napi::CallbackInfo &info): Napi::ObjectWrap<AudioBuffer>(info) {
	
	CTOR_CHECK("AudioBuffer");
	
	if (info.Length() > 0) {
		
		if (info[0].IsExternal()) {
			
			REQ_EXT_ARG(0, extBus);
			
			BusPtr *bus = reinterpret_cast<BusPtr *>(extBus->Value());
			_impl = bus;
			
		} else if (info[0].IsObject()) {
			
			REQ_OBJ_ARG(0, opts);
			
			_impl = make_shared<lab::AudioBus>(1, 1, false);
			
		}
		
	} else {
		
		_impl = make_shared<lab::AudioBus>(1, 1, false);
		
	}
	
}


AudioBuffer::~AudioBuffer() {
	
	_destroy();
	
}


AudioBuffer::BusPtr AudioBuffer::getBus() const {
	return _impl;
}


void AudioBuffer::_destroy() { DES_CHECK;
	
	_impl.reset();
	
	_isDestroyed = true;
	
}


// ------ Methods and props


JS_METHOD(AudioBuffer::getChannelData) { THIS_CHECK;
	
	REQ_UINT32_ARG(0, channelIndex);
	
	// TODO: do something?
	
}


JS_METHOD(AudioBuffer::copyFromChannel) { THIS_CHECK;
	
	REQ_OBJ_ARG(0, destination);
	REQ_INT32_ARG(1, channelNumber);
	REQ_UINT32_ARG(2, startInChannel);
	
	// TODO: do something?
	
}


JS_METHOD(AudioBuffer::copyToChannel) { THIS_CHECK;
	
	REQ_OBJ_ARG(0, source);
	REQ_INT32_ARG(1, channelNumber);
	REQ_UINT32_ARG(2, startInChannel);
	
	// TODO: do something?
	
}


JS_GETTER(AudioBuffer::lengthGetter) { THIS_CHECK;
	
	RET_NUM(_length);
	
}


JS_GETTER(AudioBuffer::durationGetter) { THIS_CHECK;
	
	RET_NUM(_duration);
	
}


JS_GETTER(AudioBuffer::sampleRateGetter) { THIS_CHECK;
	
	RET_NUM(_sampleRate);
	
}


JS_GETTER(AudioBuffer::numberOfChannelsGetter) { THIS_CHECK;
	
	RET_NUM(_numberOfChannels);
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference AudioBuffer::_ctorAudioBuffer;


void AudioBuffer::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "AudioBuffer", {
		ACCESSOR_M(AudioBuffer, copyToChannel),
		ACCESSOR_M(AudioBuffer, copyFromChannel),
		ACCESSOR_M(AudioBuffer, getChannelData),
		ACCESSOR_M(AudioBuffer, destroy),
		ACCESSOR_R(AudioBuffer, numberOfChannels),
		ACCESSOR_R(AudioBuffer, sampleRate),
		ACCESSOR_R(AudioBuffer, duration),
		ACCESSOR_R(AudioBuffer, length),
		ACCESSOR_R(AudioBuffer, isDestroyed)
	});
	
	_ctorAudioBuffer = Napi::Persistent(ctor);
	_ctorAudioBuffer.SuppressDestruct();
	
	exports.Set("AudioBuffer", ctor);
	
}


JS_METHOD(AudioBuffer::destroy) { THIS_CHECK;
	
	_destroy();
	
}


JS_GETTER(AudioBuffer::isDestroyedGetter) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
