#include <LabSound/LabSound.h>

#include "convolver-node.hpp"
#include "audio-context.hpp"
#include "audio-buffer.hpp"


Napi::FunctionReference ConvolverNode::_constructor;

void ConvolverNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "ConvolverNode", {
		ACCESSOR_RW(ConvolverNode, normalize),
		ACCESSOR_RW(ConvolverNode, buffer),
		ACCESSOR_M(ConvolverNode, destroy)
	});
	
	_constructor = Napi::Persistent(ctor);
	_constructor.SuppressDestruct();
	
	exports.Set("ConvolverNode", ctor);
	
}


ConvolverNode::ConvolverNode(const Napi::CallbackInfo &info):
CommonNode<ConvolverNode>(info, "ConvolverNode") { NAPI_ENV;
	
	CTOR_CHECK("ConvolverNode");
	
	REQ_OBJ_ARG(0, context);
	
	Napi::Object that = info.This().As<Napi::Object>();
	Napi::Function ctor = _constructor.Value().As<Napi::Function>();
	Napi::Function _Super = ctor.Get("_Super").As<Napi::Function>();
	
	reset(context, std::make_shared<lab::ConvolverNode>());
	
	std::vector<napi_value> args;
	args.push_back(context);
	_Super.Call(that, args);
	
	// lab::ConvolverNode *node = static_cast<lab::ConvolverNode*>(
	// 	_impl.get()
	// );
	
}


ConvolverNode::~ConvolverNode() {
	_destroy();
}


void ConvolverNode::_destroy() { DES_CHECK;
	
	CommonNode::_destroy();
	
}


// ------ Methods and props



JS_GETTER(ConvolverNode::bufferGetter) { THIS_CHECK;
	
	RET_VALUE(_buffer.Value());
	
}

JS_SETTER(ConvolverNode::bufferSetter) { THIS_SETTER_CHECK; SETTER_OBJ_ARG;
	
	if (_buffer.Value() == v) {
		return;
	}
	
	_buffer.Reset(v);
	
	Napi::Object context = _context.Value();
	AudioContext *audioContext = Napi::ObjectWrap<AudioContext>::Unwrap(context);
	
	lab::AudioContext *ctx = audioContext->getCtx().get();
	
	AudioBuffer *audioBuffer = Napi::ObjectWrap<AudioBuffer>::Unwrap(v);
	BusPtr bus = audioBuffer->getBus();
	
	lab::ConvolverNode *node = static_cast<lab::ConvolverNode*>(
		_impl.get()
	);
	node->setImpulse(bus);
	
	emit("buffer", 1, &value);
	
}


JS_GETTER(ConvolverNode::normalizeGetter) { THIS_CHECK;
	
	lab::ConvolverNode *node = static_cast<lab::ConvolverNode*>(
		_impl.get()
	);
	
	RET_BOOL(node->normalize());
	
}

JS_SETTER(ConvolverNode::normalizeSetter) { THIS_SETTER_CHECK; SETTER_BOOL_ARG;
	
	lab::ConvolverNode *node = static_cast<lab::ConvolverNode*>(
		_impl.get()
	);
	
	node->setNormalize(v);
	
	emit("normalize", 1, &value);
	
}


JS_METHOD(ConvolverNode::destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	RET_UNDEFINED;
	
}
