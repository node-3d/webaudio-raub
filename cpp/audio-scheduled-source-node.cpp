#include <cstdlib>
//#include <iostream> // -> std::cout << "..." << std::endl;


#include "audio-scheduled-source-node.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_AUDIO_SCHEDULED_SOURCE_NODE                                                    \
	AudioScheduledSourceNode *audioScheduledSourceNode = ObjectWrap::Unwrap<AudioScheduledSourceNode>(info.This());

#define THIS_CHECK                                                            \
	if (audioScheduledSourceNode->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (audioScheduledSourceNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	audioScheduledSourceNode->CACHE = V;


// ------ Constructor and Destructor

AudioScheduledSourceNode::AudioScheduledSourceNode() : AudioNode() {
	
	_isDestroyed = false;
	
}


AudioScheduledSourceNode::~AudioScheduledSourceNode() {
	
	_destroy();
	
}


void AudioScheduledSourceNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	AudioNode::_destroy();
	
}


// ------ Methods and props


NAN_METHOD(AudioScheduledSourceNode::start) { THIS_AUDIO_SCHEDULED_SOURCE_NODE; THIS_CHECK;
	
	REQ_DOUBLE_ARG(0, when);
	
	// TODO: do something?
	
}


NAN_METHOD(AudioScheduledSourceNode::stop) { THIS_AUDIO_SCHEDULED_SOURCE_NODE; THIS_CHECK;
	
	REQ_DOUBLE_ARG(0, when);
	
	// TODO: do something?
	
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



// ------ System methods and props for ObjectWrap

Nan::Persistent<v8::FunctionTemplate> AudioScheduledSourceNode::_protoAudioScheduledSourceNode;
Nan::Persistent<v8::Function> AudioScheduledSourceNode::_ctorAudioScheduledSourceNode;


void AudioScheduledSourceNode::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	// class AudioScheduledSourceNode inherits AudioNode
	Local<FunctionTemplate> parent = Nan::New(AudioNode::_protoAudioNode);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AudioScheduledSourceNode"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_RW(obj, onended);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	Nan::SetPrototypeMethod(proto, "start", start);
	Nan::SetPrototypeMethod(proto, "stop", stop);
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoAudioScheduledSourceNode.Reset(proto);
	_ctorAudioScheduledSourceNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("AudioScheduledSourceNode"), ctor);
	
	
}


NAN_METHOD(AudioScheduledSourceNode::newCtor) {
	
	CTOR_CHECK("AudioScheduledSourceNode");
	
	AudioScheduledSourceNode *audioScheduledSourceNode = new AudioScheduledSourceNode();
	audioScheduledSourceNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(AudioScheduledSourceNode::destroy) { THIS_AUDIO_SCHEDULED_SOURCE_NODE; THIS_CHECK;
	
	audioScheduledSourceNode->_destroy();
	
}


NAN_GETTER(AudioScheduledSourceNode::isDestroyedGetter) { THIS_AUDIO_SCHEDULED_SOURCE_NODE;
	
	RET_VALUE(JS_BOOL(audioScheduledSourceNode->_isDestroyed));
	
}
