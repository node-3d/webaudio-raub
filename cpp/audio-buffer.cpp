#include <cstdlib>
//#include <iostream> // -> cout << "..." << endl;


#include <LabSound/core/AudioBus.h>

#include "audio-buffer.hpp"
#include "audio-context.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_AUDIO_BUFFER                                                    \
	AudioBuffer *audioBuffer = Nan::ObjectWrap::Unwrap<AudioBuffer>(info.This());

#define THIS_CHECK                                                            \
	if (audioBuffer->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (audioBuffer->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	audioBuffer->CACHE = V;


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


NAN_METHOD(AudioBuffer::getChannelData) { THIS_AUDIO_BUFFER; THIS_CHECK;
	
	REQ_UINT32_ARG(0, channelIndex);
	
	// TODO: do something?
	
}


NAN_METHOD(AudioBuffer::copyFromChannel) { THIS_AUDIO_BUFFER; THIS_CHECK;
	
	REQ_OBJ_ARG(0, destination);
	REQ_INT32_ARG(1, channelNumber);
	REQ_UINT32_ARG(2, startInChannel);
	
	// TODO: do something?
	
}


NAN_METHOD(AudioBuffer::copyToChannel) { THIS_AUDIO_BUFFER; THIS_CHECK;
	
	REQ_OBJ_ARG(0, source);
	REQ_INT32_ARG(1, channelNumber);
	REQ_UINT32_ARG(2, startInChannel);
	
	// TODO: do something?
	
}


NAN_GETTER(AudioBuffer::lengthGetter) { THIS_AUDIO_BUFFER; THIS_CHECK;
	
	RET_VALUE(JS_INT32(audioBuffer->_length));
	
}


NAN_GETTER(AudioBuffer::durationGetter) { THIS_AUDIO_BUFFER; THIS_CHECK;
	
	RET_VALUE(JS_DOUBLE(audioBuffer->_duration));
	
}


NAN_GETTER(AudioBuffer::sampleRateGetter) { THIS_AUDIO_BUFFER; THIS_CHECK;
	
	RET_VALUE(JS_FLOAT(audioBuffer->_sampleRate));
	
}


NAN_GETTER(AudioBuffer::numberOfChannelsGetter) { THIS_AUDIO_BUFFER; THIS_CHECK;
	
	RET_VALUE(JS_UINT32(audioBuffer->_numberOfChannels));
	
}


// ------ System methods and props for ObjectWrap

V8_STORE_FT AudioBuffer::_protoAudioBuffer;
V8_STORE_FUNC AudioBuffer::_ctorAudioBuffer;


void AudioBuffer::init(V8_VAR_OBJ target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AudioBuffer"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
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
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoAudioBuffer.Reset(proto);
	_ctorAudioBuffer.Reset(ctor);
	
	Nan::Set(target, JS_STR("AudioBuffer"), ctor);
	
	
}


V8_VAR_OBJ AudioBuffer::getNew(BusPtr bus) {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorAudioBuffer);
	V8_VAR_EXT extBus = JS_EXT(&bus);
	V8_VAR_VAL argv[] = { extBus };
	return Nan::NewInstance(ctor, 1, argv).ToLocalChecked();
	
}


NAN_METHOD(AudioBuffer::newCtor) {
	
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


NAN_METHOD(AudioBuffer::destroy) { THIS_AUDIO_BUFFER; THIS_CHECK;
	
	audioBuffer->_destroy();
	
}


NAN_GETTER(AudioBuffer::isDestroyedGetter) { THIS_AUDIO_BUFFER;
	
	RET_VALUE(JS_BOOL(audioBuffer->_isDestroyed));
	
}
