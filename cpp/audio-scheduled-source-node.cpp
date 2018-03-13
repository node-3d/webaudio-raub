#include <cstdlib>
#include <iostream>

#include "audio-scheduled-source-node.hpp"

using namespace v8;
using namespace node;
using namespace std;


#define THIS_AUDIO_SCHEDULED_SOURCE_NODE                                                    \
	AudioScheduledSourceNode *audioScheduledSourceNode = ObjectWrap::Unwrap<AudioScheduledSourceNode>(info.This());

#define THIS_CHECK                                                            \
	if (audioScheduledSourceNode->_isDestroyed) return;

#define DES_CHECK                                                             \
	if (_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (audioScheduledSourceNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	audioScheduledSourceNode->CACHE = V;


Nan::Persistent<v8::Function> AudioScheduledSourceNode::_constructor;


void AudioScheduledSourceNode::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AudioScheduledSourceNode"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	
	// -------- dynamic
	
	
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	
	
	
	_constructor.Reset(ctor);
	Nan::Set(target, JS_STR("AudioScheduledSourceNode"), ctor);
	
	
}


NAN_METHOD(AudioScheduledSourceNode::newCtor) {
	
	CTOR_CHECK("AudioScheduledSourceNode");
	
	AudioScheduledSourceNode *audioScheduledSourceNode = new AudioScheduledSourceNode();
	audioScheduledSourceNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


AudioScheduledSourceNode::AudioScheduledSourceNode() {
	
	_isDestroyed = false;
	
}


AudioScheduledSourceNode::~AudioScheduledSourceNode() {
	
	_destroy();
	
}


void AudioScheduledSourceNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	
	
}



NAN_METHOD(AudioScheduledSourceNode::destroy) { THIS_AUDIO_SCHEDULED_SOURCE_NODE; THIS_CHECK;
	
	audioScheduledSourceNode->_destroy();
	
}


NAN_METHOD(AudioScheduledSourceNode::start) { THIS_AUDIO_SCHEDULED_SOURCE_NODE; THIS_CHECK;
	
	REQ_DOUBLE_ARG(0, when);
	
	// TODO: do something?
	
}


NAN_METHOD(AudioScheduledSourceNode::stop) { THIS_AUDIO_SCHEDULED_SOURCE_NODE; THIS_CHECK;
	
	REQ_DOUBLE_ARG(0, when);
	
	// TODO: do something?
	
}



NAN_GETTER(AudioScheduledSourceNode::isDestroyedGetter) { THIS_AUDIO_SCHEDULED_SOURCE_NODE;
	
	RET_VALUE(JS_BOOL(audioScheduledSourceNode->_isDestroyed));
	
}


NAN_GETTER(AudioScheduledSourceNode::onendedGetter) { THIS_AUDIO_SCHEDULED_SOURCE_NODE; THIS_CHECK;
	
	RET_VALUE(JS_FUN(audioScheduledSourceNode->_onended));
	
}

NAN_SETTER(AudioScheduledSourceNode::onendedSetter) { THIS_AUDIO_SCHEDULED_SOURCE_NODE; THIS_CHECK; SETTER_FUN_ARG;
	
	if (Nan::New(audioScheduledSourceNode->_onended) == v) {
		return;
	}
	audioScheduledSourceNode->_onended.Reset(v);
	
	// TODO: may be additional actions on change?
	
}

