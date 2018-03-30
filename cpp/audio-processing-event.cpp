#include <cstdlib>
//#include <iostream> // -> cout << "..." << endl;


#include "audio-processing-event.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_AUDIO_PROCESSING_EVENT                                                    \
	AudioProcessingEvent *audioProcessingEvent = Nan::ObjectWrap::Unwrap<AudioProcessingEvent>(info.This());

#define THIS_CHECK                                                            \
	if (audioProcessingEvent->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (audioProcessingEvent->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	audioProcessingEvent->CACHE = V;


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



NAN_GETTER(AudioProcessingEvent::playbackTimeGetter) { THIS_AUDIO_PROCESSING_EVENT; THIS_CHECK;
	
	RET_VALUE(JS_DOUBLE(audioProcessingEvent->_playbackTime));
	
}


NAN_GETTER(AudioProcessingEvent::inputBufferGetter) { THIS_AUDIO_PROCESSING_EVENT; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(audioProcessingEvent->_inputBuffer));
	
}


NAN_GETTER(AudioProcessingEvent::outputBufferGetter) { THIS_AUDIO_PROCESSING_EVENT; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(audioProcessingEvent->_outputBuffer));
	
}


// ------ System methods and props for ObjectWrap

V8_STORE_FT AudioProcessingEvent::_protoAudioProcessingEvent;
V8_STORE_FUNC AudioProcessingEvent::_ctorAudioProcessingEvent;


void AudioProcessingEvent::init(V8_VAR_OBJ target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);

	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AudioProcessingEvent"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, playbackTime);
	ACCESSOR_R(obj, inputBuffer);
	ACCESSOR_R(obj, outputBuffer);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoAudioProcessingEvent.Reset(proto);
	_ctorAudioProcessingEvent.Reset(ctor);
	
	Nan::Set(target, JS_STR("AudioProcessingEvent"), ctor);
	
	
}


bool AudioProcessingEvent::isAudioProcessingEvent(V8_VAR_OBJ obj) {
	return Nan::New(_protoAudioProcessingEvent)->HasInstance(obj);
}


V8_VAR_OBJ AudioProcessingEvent::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorAudioProcessingEvent);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


NAN_METHOD(AudioProcessingEvent::newCtor) {
	
	CTOR_CHECK("AudioProcessingEvent");
	
	AudioProcessingEvent *audioProcessingEvent = new AudioProcessingEvent();
	audioProcessingEvent->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(AudioProcessingEvent::destroy) { THIS_AUDIO_PROCESSING_EVENT; THIS_CHECK;
	
	audioProcessingEvent->_destroy();
	
}


NAN_GETTER(AudioProcessingEvent::isDestroyedGetter) { THIS_AUDIO_PROCESSING_EVENT;
	
	RET_VALUE(JS_BOOL(audioProcessingEvent->_isDestroyed));
	
}
