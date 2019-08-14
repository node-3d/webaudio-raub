
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



JS_GETTER(AudioProcessingEvent::playbackTimeGetter) { THIS_CHECK;
	
	RET_NUM(_playbackTime);
	
}


JS_GETTER(AudioProcessingEvent::inputBufferGetter) { THIS_CHECK;
	
	RET_VALUE(__inputBuffer.Value());
	
}


JS_GETTER(AudioProcessingEvent::outputBufferGetter) { THIS_CHECK;
	
	RET_VALUE(__outputBuffer.Value());
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference AudioProcessingEvent::_ctorAudioProcessingEvent;


void AudioProcessingEvent::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "AudioProcessingEvent", {
		ACCESSOR_M(AudioProcessingEvent, destroy),
		ACCESSOR_R(AudioProcessingEvent, outputBuffer),
		ACCESSOR_R(AudioProcessingEvent, inputBuffer),
		ACCESSOR_R(AudioProcessingEvent, playbackTime),
		ACCESSOR_R(AudioProcessingEvent, isDestroyed),
	
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


AudioProcessingEvent::AudioProcessingEvent(const Napi::CallbackInfo &info): Napi::ObjectWrap<AudioProcessingEvent>(info) {
	
	CTOR_CHECK("AudioProcessingEvent");
	
	AudioProcessingEvent *audioProcessingEvent = new AudioProcessingEvent();
	
}


JS_METHOD(AudioProcessingEvent::destroy) { THIS_CHECK;
	
	_destroy();
	
}


JS_GETTER(AudioProcessingEvent::isDestroyedGetter) {
	
	RET_BOOL(_isDestroyed);
	
}
