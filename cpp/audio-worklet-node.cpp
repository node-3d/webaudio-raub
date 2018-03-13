#include <cstdlib>
#include <iostream>

#include "audio-worklet-node.hpp"

using namespace v8;
using namespace node;
using namespace std;


#define THIS_AUDIO_WORKLET_NODE                                                    \
	AudioWorkletNode *audioWorkletNode = ObjectWrap::Unwrap<AudioWorkletNode>(info.This());

#define THIS_CHECK                                                            \
	if (audioWorkletNode->_isDestroyed) return;

#define DES_CHECK                                                             \
	if (_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (audioWorkletNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	audioWorkletNode->CACHE = V;


Nan::Persistent<v8::Function> AudioWorkletNode::_constructor;


void AudioWorkletNode::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AudioWorkletNode"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	
	// -------- dynamic
	
	
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	
	
	
	_constructor.Reset(ctor);
	Nan::Set(target, JS_STR("AudioWorkletNode"), ctor);
	
	
}


NAN_METHOD(AudioWorkletNode::newCtor) {
	
	CTOR_CHECK("AudioWorkletNode");
	
	AudioWorkletNode *audioWorkletNode = new AudioWorkletNode();
	audioWorkletNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


AudioWorkletNode::AudioWorkletNode() {
	
	_isDestroyed = false;
	
}


AudioWorkletNode::~AudioWorkletNode() {
	
	_destroy();
	
}


void AudioWorkletNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	
	
}



NAN_METHOD(AudioWorkletNode::destroy) { THIS_AUDIO_WORKLET_NODE; THIS_CHECK;
	
	audioWorkletNode->_destroy();
	
}




NAN_GETTER(AudioWorkletNode::isDestroyedGetter) { THIS_AUDIO_WORKLET_NODE;
	
	RET_VALUE(JS_BOOL(audioWorkletNode->_isDestroyed));
	
}


NAN_GETTER(AudioWorkletNode::parametersGetter) { THIS_AUDIO_WORKLET_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(audioWorkletNode->_parameters));
	
}

NAN_SETTER(AudioWorkletNode::parametersSetter) { THIS_AUDIO_WORKLET_NODE; THIS_CHECK; SETTER_OBJ_ARG;
	
	if (Nan::New(audioWorkletNode->_parameters) == v) {
		return;
	}
	audioWorkletNode->_parameters.Reset(v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(AudioWorkletNode::portGetter) { THIS_AUDIO_WORKLET_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(audioWorkletNode->_port));
	
}

NAN_SETTER(AudioWorkletNode::portSetter) { THIS_AUDIO_WORKLET_NODE; THIS_CHECK; SETTER_OBJ_ARG;
	
	if (Nan::New(audioWorkletNode->_port) == v) {
		return;
	}
	audioWorkletNode->_port.Reset(v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(AudioWorkletNode::onprocessorerrorGetter) { THIS_AUDIO_WORKLET_NODE; THIS_CHECK;
	
	RET_VALUE(JS_FUN(audioWorkletNode->_onprocessorerror));
	
}

NAN_SETTER(AudioWorkletNode::onprocessorerrorSetter) { THIS_AUDIO_WORKLET_NODE; THIS_CHECK; SETTER_FUN_ARG;
	
	if (Nan::New(audioWorkletNode->_onprocessorerror) == v) {
		return;
	}
	audioWorkletNode->_onprocessorerror.Reset(v);
	
	// TODO: may be additional actions on change?
	
}

