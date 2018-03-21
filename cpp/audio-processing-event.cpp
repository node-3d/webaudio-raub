#include <cstdlib>
//#include <iostream> // -> std::cout << "..." << std::endl;


#include "audio-processing-event.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_AUDIO_PROCESSING_EVENT                                                    \
	AudioProcessingEvent *audioProcessingEvent = ObjectWrap::Unwrap<AudioProcessingEvent>(info.This());

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

Nan::Persistent<v8::FunctionTemplate> AudioProcessingEvent::_protoAudioProcessingEvent;
Nan::Persistent<v8::Function> AudioProcessingEvent::_ctorAudioProcessingEvent;


void AudioProcessingEvent::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AudioProcessingEvent"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, playbackTime);
	ACCESSOR_R(obj, inputBuffer);
	ACCESSOR_R(obj, outputBuffer);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoAudioProcessingEvent.Reset(proto);
	_ctorAudioProcessingEvent.Reset(ctor);
	
	Nan::Set(target, JS_STR("AudioProcessingEvent"), ctor);
	
	
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
