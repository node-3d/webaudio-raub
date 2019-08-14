#include <LabSound/core/AudioBus.h>

#include "audio-buffer.hpp"
#include "audio-context.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

AudioBuffer::AudioBuffer() {
	
	_isDestroyed = false;
	
	_impl = make_shared<lab::AudioBus>(1, 1, false);
	
}


AudioBuffer::AudioBuffer(BusPtr bus) {
	
	_isDestroyed = false;
	
	_impl = bus;
	
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
		ACCESSOR_R(AudioBuffer, isDestroyed),
	
	});
	
	_ctorAudioBuffer = Napi::Persistent(ctor);
	_ctorAudioBuffer.SuppressDestruct();
	
	exports.Set("AudioBuffer", ctor);
	
}


Napi::Object AudioBuffer::getNew(BusPtr bus) {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorAudioBuffer);
	V8_VAR_EXT extBus = JS_EXT(&bus);
	V8_VAR_VAL argv[] = { extBus };
	return Nan::NewInstance(ctor, 1, argv).ToLocalChecked();
	
}


AudioBuffer::AudioBuffer(const Napi::CallbackInfo &info): Napi::ObjectWrap<AudioBuffer>(info) {
	
	CTOR_CHECK("AudioBuffer");
	
	AudioBuffer *audioBuffer = nullptr;
	
	if (info.Length() > 0) {
		
		
		if (info[0]->IsExternal()) {
			
			REQ_EXT_ARG(0, extBus);
			
			BusPtr *bus = reinterpret_cast<BusPtr *>(extBus->Value());
			
			audioBuffer = new AudioBuffer(*bus);
			
		} else if (info[0]->IsObject()) {
			
			REQ_OBJ_ARG(0, opts);
			
			audioBuffer = new AudioBuffer();
			
		}
		
	} else {
		
		audioBuffer = new AudioBuffer();
		
	}
	
	
}


JS_METHOD(AudioBuffer::destroy) { THIS_CHECK;
	
	_destroy();
	
}


JS_GETTER(AudioBuffer::isDestroyedGetter) {
	
	RET_BOOL(_isDestroyed);
	
}
