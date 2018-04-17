#include <cstdlib>
//#include <iostream> // -> cout << "..." << endl;


#include <LabSound/core/AudioScheduledSourceNode.h>

#include "audio-scheduled-source-node.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_AUDIO_SCHEDULED_SOURCE_NODE                                      \
	AudioScheduledSourceNode *audioScheduledSourceNode =                      \
		Nan::ObjectWrap::Unwrap<AudioScheduledSourceNode>(info.This());

#define THIS_CHECK                                                            \
	if (audioScheduledSourceNode->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (audioScheduledSourceNode->CACHE == V) {                               \
		return;                                                               \
	}                                                                         \
	audioScheduledSourceNode->CACHE = V;


// ------ Constructor and Destructor

AudioScheduledSourceNode::AudioScheduledSourceNode(V8_VAR_OBJ context, NodePtr node) :
AudioNode(context, node) {
	
	node->setOnEnded(std::bind(&AudioScheduledSourceNode::onEnded, this));
	
	_isDestroyed = false;
	
}


AudioScheduledSourceNode::~AudioScheduledSourceNode() {
	cout << "AudioScheduledSourceNode DESTROY 1" << endl;
	AudioScheduledSourceNode::_destroy();
	
	// AudioNode::~AudioNode();
	cout << "AudioScheduledSourceNode DESTROY 2" << endl;
}


void AudioScheduledSourceNode::onEnded() { NAN_HS;
	
	emit("ended");
	
}


void AudioScheduledSourceNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
}


// ------ Methods and props


NAN_METHOD(AudioScheduledSourceNode::start) { THIS_AUDIO_SCHEDULED_SOURCE_NODE; THIS_CHECK;
	
	REQ_DOUBLE_ARG(0, when);
	
	lab::AudioScheduledSourceNode *node = static_cast<lab::AudioScheduledSourceNode*>(
		audioScheduledSourceNode->_impl.get()
	);
	
	node->start(when);
	
}


NAN_METHOD(AudioScheduledSourceNode::stop) { THIS_AUDIO_SCHEDULED_SOURCE_NODE; THIS_CHECK;
	
	REQ_DOUBLE_ARG(0, when);
	
	lab::AudioScheduledSourceNode *node = static_cast<lab::AudioScheduledSourceNode*>(
		audioScheduledSourceNode->_impl.get()
	);
	
	node->stop(when);
	
}


// ------ System methods and props for ObjectWrap

V8_STORE_FT AudioScheduledSourceNode::_protoAudioScheduledSourceNode;
V8_STORE_FUNC AudioScheduledSourceNode::_ctorAudioScheduledSourceNode;


void AudioScheduledSourceNode::init(V8_VAR_OBJ target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);

	// class AudioScheduledSourceNode inherits AudioNode
	V8_VAR_FT parent = Nan::New(AudioNode::_protoAudioNode);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AudioScheduledSourceNode"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	Nan::SetPrototypeMethod(proto, "start", start);
	Nan::SetPrototypeMethod(proto, "stop", stop);
	
	// -------- static
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoAudioScheduledSourceNode.Reset(proto);
	_ctorAudioScheduledSourceNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("AudioScheduledSourceNode"), ctor);
	
	
}


V8_VAR_OBJ AudioScheduledSourceNode::getNew(V8_VAR_OBJ context, NodePtr node) {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorAudioScheduledSourceNode);
	Local<External> extNode = JS_EXT(&node);
	V8_VAR_VAL argv[] = { context, extNode };
	return Nan::NewInstance(ctor, 2, argv).ToLocalChecked();
	
}


NAN_METHOD(AudioScheduledSourceNode::newCtor) {
	
	CTOR_CHECK("AudioScheduledSourceNode");
	
	REQ_OBJ_ARG(0, context);
	REQ_EXT_ARG(1, extNode);
	
	NodePtr *node = reinterpret_cast<NodePtr *>(extNode->Value());
	
	AudioScheduledSourceNode *audioScheduledSourceNode = new AudioScheduledSourceNode(context, *node);
	audioScheduledSourceNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(AudioScheduledSourceNode::destroy) { THIS_AUDIO_SCHEDULED_SOURCE_NODE; THIS_CHECK;
	
	audioScheduledSourceNode->_destroy();
	
}


NAN_GETTER(AudioScheduledSourceNode::isDestroyedGetter) { THIS_AUDIO_SCHEDULED_SOURCE_NODE;
	
	RET_VALUE(JS_BOOL(audioScheduledSourceNode->_isDestroyed));
	
}
