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


JS_METHOD(AudioBuffer::getChannelData) { THIS_AUDIO_BUFFER; THIS_CHECK;
	
	REQ_UINT32_ARG(0, channelIndex);
	
	// TODO: do something?
	
}


JS_METHOD(AudioBuffer::copyFromChannel) { THIS_AUDIO_BUFFER; THIS_CHECK;
	
	REQ_OBJ_ARG(0, destination);
	REQ_INT32_ARG(1, channelNumber);
	REQ_UINT32_ARG(2, startInChannel);
	
	// TODO: do something?
	
}


JS_METHOD(AudioBuffer::copyToChannel) { THIS_AUDIO_BUFFER; THIS_CHECK;
	
	REQ_OBJ_ARG(0, source);
	REQ_INT32_ARG(1, channelNumber);
	REQ_UINT32_ARG(2, startInChannel);
	
	// TODO: do something?
	
}


JS_GETTER(AudioBuffer::lengthGetter) { THIS_AUDIO_BUFFER; THIS_CHECK;
	
	RET_NUM(_length);
	
}


JS_GETTER(AudioBuffer::durationGetter) { THIS_AUDIO_BUFFER; THIS_CHECK;
	
	RET_NUM(_duration);
	
}


JS_GETTER(AudioBuffer::sampleRateGetter) { THIS_AUDIO_BUFFER; THIS_CHECK;
	
	RET_NUM(_sampleRate);
	
}


JS_GETTER(AudioBuffer::numberOfChannelsGetter) { THIS_AUDIO_BUFFER; THIS_CHECK;
	
	RET_NUM(_numberOfChannels);
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference AudioBuffer::_ctorAudioBuffer;


void AudioBuffer::init(Napi::Env env, Napi::Object exports) {
	
	
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, length);
	ACCESSOR_R(obj, duration);
	ACCESSOR_R(obj, sampleRate);
	ACCESSOR_R(obj, numberOfChannels);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	Nan::SetPrototypeMethod(proto, "getChannelData", getChannelData);
	Nan::SetPrototypeMethod(proto, "copyFromChannel", copyFromChannel);
	Nan::SetPrototypeMethod(proto, "copyToChannel", copyToChannel);
	
	// -------- static
	
	Napi::Function ctor = DefineClass(env, "AudioBuffer", {
	
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


JS_METHOD(AudioBuffer::newCtor) {
	
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
	
	audioBuffer->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


JS_METHOD(AudioBuffer::destroy) { THIS_AUDIO_BUFFER; THIS_CHECK;
	
	_destroy();
	
}


JS_GETTER(AudioBuffer::isDestroyedGetter) { THIS_AUDIO_BUFFER;
	
	RET_BOOL(_isDestroyed);
	
}
