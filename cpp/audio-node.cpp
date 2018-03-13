#include <cstdlib>
#include <iostream>

#include "audio-node.hpp"

using namespace v8;
using namespace node;
using namespace std;


#define THIS_AUDIO_NODE                                                    \
	AudioNode *audioNode = ObjectWrap::Unwrap<AudioNode>(info.This());

#define THIS_CHECK                                                            \
	if (audioNode->_isDestroyed) return;

#define DES_CHECK                                                             \
	if (_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (audioNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	audioNode->CACHE = V;


Nan::Persistent<v8::Function> AudioNode::_constructor;


void AudioNode::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AudioNode"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	
	// -------- dynamic
	
	
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	
	
	
	_constructor.Reset(ctor);
	Nan::Set(target, JS_STR("AudioNode"), ctor);
	
	
}


NAN_METHOD(AudioNode::newCtor) {
	
	CTOR_CHECK("AudioNode");
	
	AudioNode *audioNode = new AudioNode();
	audioNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


AudioNode::AudioNode() {
	
	_isDestroyed = false;
	
}


AudioNode::~AudioNode() {
	
	_destroy();
	
}


void AudioNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	
	
}



NAN_METHOD(AudioNode::destroy) { THIS_AUDIO_NODE; THIS_CHECK;
	
	audioNode->_destroy();
	
}


NAN_METHOD(AudioNode::connect) { THIS_AUDIO_NODE; THIS_CHECK;
	
	REQ_OBJ_ARG(0, destination);
	REQ_INT32_ARG(1, output);
	REQ_INT32_ARG(2, input);
	
	// TODO: do something?
	
}


NAN_METHOD(AudioNode::disconnect) { THIS_AUDIO_NODE; THIS_CHECK;
	
	REQ_OBJ_ARG(0, destination);
	REQ_INT32_ARG(1, output);
	REQ_INT32_ARG(2, input);
	
	// TODO: do something?
	
}



NAN_GETTER(AudioNode::isDestroyedGetter) { THIS_AUDIO_NODE;
	
	RET_VALUE(JS_BOOL(audioNode->_isDestroyed));
	
}


NAN_GETTER(AudioNode::contextGetter) { THIS_AUDIO_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(audioNode->_context));
	
}

NAN_SETTER(AudioNode::contextSetter) { THIS_AUDIO_NODE; THIS_CHECK; SETTER_OBJ_ARG;
	
	if (Nan::New(audioNode->_context) == v) {
		return;
	}
	audioNode->_context.Reset(v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(AudioNode::numberOfInputsGetter) { THIS_AUDIO_NODE; THIS_CHECK;
	
	RET_VALUE(JS_INT32(audioNode->_numberOfInputs));
	
}

NAN_SETTER(AudioNode::numberOfInputsSetter) { THIS_AUDIO_NODE; THIS_CHECK; SETTER_INT32_ARG;
	
	CACHE_CAS(_numberOfInputs, v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(AudioNode::numberOfOutputsGetter) { THIS_AUDIO_NODE; THIS_CHECK;
	
	RET_VALUE(JS_INT32(audioNode->_numberOfOutputs));
	
}

NAN_SETTER(AudioNode::numberOfOutputsSetter) { THIS_AUDIO_NODE; THIS_CHECK; SETTER_INT32_ARG;
	
	CACHE_CAS(_numberOfOutputs, v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(AudioNode::channelCountGetter) { THIS_AUDIO_NODE; THIS_CHECK;
	
	RET_VALUE(JS_INT32(audioNode->_channelCount));
	
}

NAN_SETTER(AudioNode::channelCountSetter) { THIS_AUDIO_NODE; THIS_CHECK; SETTER_INT32_ARG;
	
	CACHE_CAS(_channelCount, v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(AudioNode::channelCountModeGetter) { THIS_AUDIO_NODE; THIS_CHECK;
	
	RET_VALUE(JS_UTF8(audioNode->_channelCountMode));
	
}

NAN_SETTER(AudioNode::channelCountModeSetter) { THIS_AUDIO_NODE; THIS_CHECK; SETTER_UTF8_ARG;
	
	if (audioNode->_channelCountMode == *v) {
		return;
	}
	audioNode->_channelCountMode = *v;
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(AudioNode::channelInterpretationGetter) { THIS_AUDIO_NODE; THIS_CHECK;
	
	RET_VALUE(JS_UTF8(audioNode->_channelInterpretation));
	
}

NAN_SETTER(AudioNode::channelInterpretationSetter) { THIS_AUDIO_NODE; THIS_CHECK; SETTER_UTF8_ARG;
	
	if (audioNode->_channelInterpretation == *v) {
		return;
	}
	audioNode->_channelInterpretation = *v;
	
	// TODO: may be additional actions on change?
	
}

