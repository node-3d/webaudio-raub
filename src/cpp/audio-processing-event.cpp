
#include "audio-processing-event.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

AudioProcessingEvent::AudioProcessingEvent() {
	
	_isDestroyed = false;
	
}


AudioProcessingEvent::~AudioProcessingEvent() {
	
	_destroy();
	
}


void AudioProcessingEvent::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
}


// ------ Methods and props



JS_GETTER(AudioProcessingEvent::playbackTimeGetter) { THIS_AUDIO_PROCESSING_EVENT; THIS_CHECK;
	
	RET_NUM(_playbackTime);
	
}


JS_GETTER(AudioProcessingEvent::inputBufferGetter) { THIS_AUDIO_PROCESSING_EVENT; THIS_CHECK;
	
	RET_VALUE(__inputBuffer.Value());
	
}


JS_GETTER(AudioProcessingEvent::outputBufferGetter) { THIS_AUDIO_PROCESSING_EVENT; THIS_CHECK;
	
	RET_VALUE(__outputBuffer.Value());
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference AudioProcessingEvent::_ctorAudioProcessingEvent;


void AudioProcessingEvent::init(Napi::Env env, Napi::Object exports) {
	
	
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, playbackTime);
	ACCESSOR_R(obj, inputBuffer);
	ACCESSOR_R(obj, outputBuffer);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Napi::Function ctor = DefineClass(env, "AudioProcessingEvent", {
	
	});
	
	_ctorAudioProcessingEvent = Napi::Persistent(ctor);
	_ctorAudioProcessingEvent.SuppressDestruct();
	
	exports.Set("AudioProcessingEvent", ctor);
	
}


bool AudioProcessingEvent::isAudioProcessingEvent(Napi::Object obj) {
	return obj.InstanceOf(_ctorAudioProcessingEvent.Value());
}


Napi::Object AudioProcessingEvent::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorAudioProcessingEvent);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


JS_METHOD(AudioProcessingEvent::newCtor) {
	
	CTOR_CHECK("AudioProcessingEvent");
	
	AudioProcessingEvent *audioProcessingEvent = new AudioProcessingEvent();
	audioProcessingEvent->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


JS_METHOD(AudioProcessingEvent::destroy) { THIS_AUDIO_PROCESSING_EVENT; THIS_CHECK;
	
	_destroy();
	
}


JS_GETTER(AudioProcessingEvent::isDestroyedGetter) { THIS_AUDIO_PROCESSING_EVENT;
	
	RET_BOOL(_isDestroyed);
	
}
