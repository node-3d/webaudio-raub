#include <cstdlib>

#include <LabSound/core/AudioContext.h>
#include <LabSound/core/ConvolverNode.h>

#include "convolver-node.hpp"
#include "audio-context.hpp"
#include "audio-buffer.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_CONVOLVER_NODE                                                   \
	ConvolverNode *convolverNode = Nan::ObjectWrap::Unwrap<ConvolverNode>(info.This());

#define THIS_CHECK                                                            \
	if (convolverNode->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (convolverNode->CACHE == V) {                                          \
		return;                                                               \
	}                                                                         \
	convolverNode->CACHE = V;


// ------ Constructor and Destructor

ConvolverNode::ConvolverNode(V8_VAR_OBJ context) :
AudioNode(context, NodePtr(new lab::ConvolverNode())) {
	
	lab::ConvolverNode *node = static_cast<lab::ConvolverNode*>(_impl.get());
	
	_isDestroyed = false;
	
}


ConvolverNode::~ConvolverNode() {
	
	_destroy();
	
}


void ConvolverNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	AudioNode::_destroy();
	
}


// ------ Methods and props



NAN_GETTER(ConvolverNode::bufferGetter) { THIS_CONVOLVER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(convolverNode->_buffer));
	
}

NAN_SETTER(ConvolverNode::bufferSetter) { THIS_CONVOLVER_NODE; THIS_CHECK; SETTER_OBJ_ARG;
	
	if (Nan::New(convolverNode->_buffer) == v) {
		return;
	}
	
	convolverNode->_buffer.Reset(v);
	
	V8_VAR_OBJ context = JS_OBJ(convolverNode->_context);
	AudioContext *audioContext = ObjectWrap::Unwrap<AudioContext>(context);
	
	lab::AudioContext *ctx = audioContext->getContext().get();
	
	AudioBuffer *audioBuffer = ObjectWrap::Unwrap<AudioBuffer>(v);
	AudioBuffer::BusPtr bus = audioBuffer->getBus();
	
	lab::ConvolverNode *node = static_cast<lab::ConvolverNode*>(
		convolverNode->_impl.get()
	);
	node->setImpulse(bus);
	
	convolverNode->emit("buffer", 1, &value);
	
}


NAN_GETTER(ConvolverNode::normalizeGetter) { THIS_CONVOLVER_NODE; THIS_CHECK;
	
	lab::ConvolverNode *node = static_cast<lab::ConvolverNode*>(
		convolverNode->_impl.get()
	);
	
	RET_VALUE(JS_BOOL(node->normalize()));
	
}

NAN_SETTER(ConvolverNode::normalizeSetter) { THIS_CONVOLVER_NODE; THIS_CHECK; SETTER_BOOL_ARG;
	
	lab::ConvolverNode *node = static_cast<lab::ConvolverNode*>(
		convolverNode->_impl.get()
	);
	
	node->setNormalize(v);
	
	convolverNode->emit("normalize", 1, &value);
	
}


// ------ System methods and props for ObjectWrap

V8_STORE_FT ConvolverNode::_protoConvolverNode;
V8_STORE_FUNC ConvolverNode::_ctorConvolverNode;


void ConvolverNode::init(V8_VAR_OBJ target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);
	
	// class ConvolverNode inherits AudioNode
	V8_VAR_FT parent = Nan::New(AudioNode::_protoAudioNode);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("ConvolverNode"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_RW(obj, buffer);
	ACCESSOR_RW(obj, normalize);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	// -------- static
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoConvolverNode.Reset(proto);
	_ctorConvolverNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("ConvolverNode"), ctor);
	
}


V8_VAR_OBJ ConvolverNode::getNew(V8_VAR_OBJ context) {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorConvolverNode);
	V8_VAR_VAL argv[] = { context };
	return Nan::NewInstance(ctor, 1, argv).ToLocalChecked();
	
}


NAN_METHOD(ConvolverNode::newCtor) {
	
	CTOR_CHECK("ConvolverNode");
	
	REQ_OBJ_ARG(0, context);
	
	ConvolverNode *convolverNode = new ConvolverNode(context);
	convolverNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(ConvolverNode::destroy) { THIS_CONVOLVER_NODE; THIS_CHECK;
	
	convolverNode->emit("destroy");
	
	convolverNode->_destroy();
	
}


NAN_GETTER(ConvolverNode::isDestroyedGetter) { THIS_CONVOLVER_NODE;
	
	RET_VALUE(JS_BOOL(convolverNode->_isDestroyed));
	
}
