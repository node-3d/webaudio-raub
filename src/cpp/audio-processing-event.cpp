
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



JS_IMPLEMENT_GETTER(AudioProcessingEvent, playbackTime) { THIS_CHECK;
	
	RET_NUM(_playbackTime);
	
}


JS_IMPLEMENT_GETTER(AudioProcessingEvent, inputBuffer) { THIS_CHECK;
	
	RET_VALUE(_inputBuffer.Value());
	
}


JS_IMPLEMENT_GETTER(AudioProcessingEvent, outputBuffer) { THIS_CHECK;
	
	RET_VALUE(_outputBuffer.Value());
	
}


// ------ System methods and props for Napi::ObjectWrap

IMPLEMENT_ES5_CLASS(AudioProcessingEvent);


void AudioProcessingEvent::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_METHOD(destroy);
	JS_ASSIGN_GETTER(outputBuffer);
	JS_ASSIGN_GETTER(inputBuffer);
	JS_ASSIGN_GETTER(playbackTime);
	JS_ASSIGN_GETTER(isDestroyed);
	
	exports.Set("AudioProcessingEvent", ctor);
	
}


bool AudioProcessingEvent::isAudioProcessingEvent(Napi::Object obj) {
	return obj.InstanceOf(_ctorEs5.Value());
}


Napi::Object AudioProcessingEvent::getNew() {
	
	Napi::Function ctor = Nan::New(_constructor);
	// Napi::Value argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


AudioProcessingEvent::AudioProcessingEvent(const Napi::CallbackInfo &info): Napi::ObjectWrap<AudioProcessingEvent>(info) {
	
	AudioProcessingEvent *audioProcessingEvent = new AudioProcessingEvent();
	
}


JS_IMPLEMENT_METHOD(AudioProcessingEvent, destroy) { THIS_CHECK;
	
	_destroy();
	
}


JS_IMPLEMENT_GETTER(AudioProcessingEvent, isDestroyed) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
