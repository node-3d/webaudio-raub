#include <cstdlib>
//#include <iostream> // -> cout << "..." << endl;


#include "audio-worklet-node.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_AUDIO_WORKLET_NODE                                                    \
	AudioWorkletNode *audioWorkletNode = Nan::ObjectWrap::Unwrap<AudioWorkletNode>(info.This());

#define THIS_CHECK                                                            \
	if (audioWorkletNode->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (audioWorkletNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	audioWorkletNode->CACHE = V;


// ------ Constructor and Destructor

AudioWorkletNode::AudioWorkletNode() {
	
	_isDestroyed = false;
	
}


AudioWorkletNode::~AudioWorkletNode() {
	
	_destroy();
	
}


void AudioWorkletNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
}


// ------ Methods and props



NAN_GETTER(AudioWorkletNode::parametersGetter) { THIS_AUDIO_WORKLET_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(audioWorkletNode->_parameters));
	
}


NAN_GETTER(AudioWorkletNode::portGetter) { THIS_AUDIO_WORKLET_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(audioWorkletNode->_port));
	
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


// ------ System methods and props for ObjectWrap

V8_STORE_FT AudioWorkletNode::_protoAudioWorkletNode;
V8_STORE_FUNC AudioWorkletNode::_ctorAudioWorkletNode;


void AudioWorkletNode::init(V8_VAR_OBJ target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);

	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AudioWorkletNode"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, parameters);
	ACCESSOR_R(obj, port);
	ACCESSOR_RW(obj, onprocessorerror);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoAudioWorkletNode.Reset(proto);
	_ctorAudioWorkletNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("AudioWorkletNode"), ctor);
	
	
}


V8_VAR_OBJ AudioWorkletNode::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorAudioWorkletNode);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


NAN_METHOD(AudioWorkletNode::newCtor) {
	
	CTOR_CHECK("AudioWorkletNode");
	
	AudioWorkletNode *audioWorkletNode = new AudioWorkletNode();
	audioWorkletNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(AudioWorkletNode::destroy) { THIS_AUDIO_WORKLET_NODE; THIS_CHECK;
	
	audioWorkletNode->_destroy();
	
}


NAN_GETTER(AudioWorkletNode::isDestroyedGetter) { THIS_AUDIO_WORKLET_NODE;
	
	RET_VALUE(JS_BOOL(audioWorkletNode->_isDestroyed));
	
}
