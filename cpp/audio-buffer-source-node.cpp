#include <cstdlib>
//#include <iostream> // -> std::cout << "..." << std::endl;


#include "audio-buffer-source-node.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_AUDIO_BUFFER_SOURCE_NODE                                                    \
	AudioBufferSourceNode *audioBufferSourceNode = ObjectWrap::Unwrap<AudioBufferSourceNode>(info.This());

#define THIS_CHECK                                                            \
	if (audioBufferSourceNode->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (audioBufferSourceNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	audioBufferSourceNode->CACHE = V;


// ------ Constructor and Destructor

AudioBufferSourceNode::AudioBufferSourceNode() : AudioNode() {
	
	_isDestroyed = false;
	
}


AudioBufferSourceNode::~AudioBufferSourceNode() {
	
	_destroy();
	
}


void AudioBufferSourceNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	AudioNode::_destroy();
	
}


// ------ Methods and props


NAN_METHOD(AudioBufferSourceNode::start) { THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK;
	
	REQ_DOUBLE_ARG(0, when);
	REQ_DOUBLE_ARG(1, grainOffset);
	REQ_DOUBLE_ARG(2, grainDuration );
	
	// TODO: do something?
	
}


NAN_GETTER(AudioBufferSourceNode::bufferGetter) { THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(audioBufferSourceNode->_buffer));
	
}

NAN_SETTER(AudioBufferSourceNode::bufferSetter) { THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK; SETTER_OBJ_ARG;
	
	if (Nan::New(audioBufferSourceNode->_buffer) == v) {
		return;
	}
	audioBufferSourceNode->_buffer.Reset(v);
	
	// TODO: may be additional actions on change?
	
	audioBufferSourceNode->emit("buffer", 1, &value);
	
}


NAN_GETTER(AudioBufferSourceNode::playbackRateGetter) { THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(audioBufferSourceNode->_playbackRate));
	
}


NAN_GETTER(AudioBufferSourceNode::detuneGetter) { THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(audioBufferSourceNode->_detune));
	
}


NAN_GETTER(AudioBufferSourceNode::loopGetter) { THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK;
	
	RET_VALUE(JS_BOOL(audioBufferSourceNode->_loop));
	
}

NAN_SETTER(AudioBufferSourceNode::loopSetter) { THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK; SETTER_BOOL_ARG;
	
	CACHE_CAS(_loop, v);
	
	// TODO: may be additional actions on change?
	
	audioBufferSourceNode->emit("loop", 1, &value);
	
}


NAN_GETTER(AudioBufferSourceNode::loopStartGetter) { THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK;
	
	RET_VALUE(JS_DOUBLE(audioBufferSourceNode->_loopStart));
	
}

NAN_SETTER(AudioBufferSourceNode::loopStartSetter) { THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	CACHE_CAS(_loopStart, v);
	
	// TODO: may be additional actions on change?
	
	audioBufferSourceNode->emit("loopStart", 1, &value);
	
}


NAN_GETTER(AudioBufferSourceNode::loopEndGetter) { THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK;
	
	RET_VALUE(JS_DOUBLE(audioBufferSourceNode->_loopEnd));
	
}

NAN_SETTER(AudioBufferSourceNode::loopEndSetter) { THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	CACHE_CAS(_loopEnd, v);
	
	// TODO: may be additional actions on change?
	
	audioBufferSourceNode->emit("loopEnd", 1, &value);
	
}


// ------ System methods and props for ObjectWrap

Nan::Persistent<v8::FunctionTemplate> AudioBufferSourceNode::_protoAudioBufferSourceNode;
Nan::Persistent<v8::Function> AudioBufferSourceNode::_ctorAudioBufferSourceNode;


void AudioBufferSourceNode::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	// class AudioBufferSourceNode inherits AudioNode
	Local<FunctionTemplate> parent = Nan::New(AudioNode::_protoAudioNode);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AudioBufferSourceNode"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_RW(obj, buffer);
	ACCESSOR_R(obj, playbackRate);
	ACCESSOR_R(obj, detune);
	ACCESSOR_RW(obj, loop);
	ACCESSOR_RW(obj, loopStart);
	ACCESSOR_RW(obj, loopEnd);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	Nan::SetPrototypeMethod(proto, "start", start);
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoAudioBufferSourceNode.Reset(proto);
	_ctorAudioBufferSourceNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("AudioBufferSourceNode"), ctor);
	
	
}


NAN_METHOD(AudioBufferSourceNode::newCtor) {
	
	CTOR_CHECK("AudioBufferSourceNode");
	
	AudioBufferSourceNode *audioBufferSourceNode = new AudioBufferSourceNode();
	audioBufferSourceNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(AudioBufferSourceNode::destroy) { THIS_AUDIO_BUFFER_SOURCE_NODE; THIS_CHECK;
	
	audioBufferSourceNode->_destroy();
	
}


NAN_GETTER(AudioBufferSourceNode::isDestroyedGetter) { THIS_AUDIO_BUFFER_SOURCE_NODE;
	
	RET_VALUE(JS_BOOL(audioBufferSourceNode->_isDestroyed));
	
}
