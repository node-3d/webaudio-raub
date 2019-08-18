
#include "analyser-node.hpp"

#include "common.hpp"


Napi::FunctionReference AnalyserNode::_constructor;

void AnalyserNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "AnalyserNode", {
		ACCESSOR_RW(AnalyserNode, smoothingTimeConstant),
		ACCESSOR_RW(AnalyserNode, maxDecibels),
		ACCESSOR_RW(AnalyserNode, minDecibels),
		ACCESSOR_RW(AnalyserNode, fftSize),
		ACCESSOR_M(AnalyserNode, getByteTimeDomainData),
		ACCESSOR_M(AnalyserNode, getFloatTimeDomainData),
		ACCESSOR_M(AnalyserNode, getByteFrequencyData),
		ACCESSOR_M(AnalyserNode, getFloatFrequencyData),
		ACCESSOR_M(AnalyserNode, destroy),
		ACCESSOR_R(AnalyserNode, frequencyBinCount),
		ACCESSOR_R(AnalyserNode, isDestroyed)
	});
	
	_constructor = Napi::Persistent(ctor);
	_constructor.SuppressDestruct();
	
	exports.Set("AnalyserNode", ctor);
	
}

// Image.prototype.__proto__ = EventEmitter.prototype;
AnalyserNode::AnalyserNode(const Napi::CallbackInfo &info):
Napi::ObjectWrap<AnalyserNode>(info) {
	
	CTOR_CHECK("AnalyserNode");
	
	std::make_shared<lab::AnalyserNode>();
	
	Napi::Object that = info.This().As<Napi::Object>();
	Napi::Function ctor = _constructor.Value().As<Napi::Function>();
	Napi::Function _Super = ctor.Get("_Super").As<Napi::Function>();
	_Super.Call(that, 2, {  });
	
}


// ------ Methods and props


JS_METHOD(AnalyserNode::getFloatFrequencyData) { THIS_CHECK;
	
	REQ_OBJ_ARG(0, array);
	
	// TODO: do something?
	
}


JS_METHOD(AnalyserNode::getByteFrequencyData) { THIS_CHECK;
	
	REQ_OBJ_ARG(0, array);
	
	// TODO: do something?
	
}


JS_METHOD(AnalyserNode::getFloatTimeDomainData) { THIS_CHECK;
	
	REQ_OBJ_ARG(0, array);
	
	// TODO: do something?
	
}


JS_METHOD(AnalyserNode::getByteTimeDomainData) { THIS_CHECK;
	
	REQ_OBJ_ARG(0, array);
	
	// TODO: do something?
	
}


JS_GETTER(AnalyserNode::frequencyBinCountGetter) { THIS_CHECK;
	
	RET_NUM(_frequencyBinCount);
	
}


JS_GETTER(AnalyserNode::fftSizeGetter) { THIS_CHECK;
	
	RET_NUM(_fftSize);
	
}

JS_SETTER(AnalyserNode::fftSizeSetter) { THIS_CHECK; SETTER_UINT32_ARG;
	
	CACHE_CAS(_fftSize, v);
	
	// TODO: may be additional actions on change?
	
	emit("fftSize", 1, &value);
	
}


JS_GETTER(AnalyserNode::minDecibelsGetter) { THIS_CHECK;
	
	RET_NUM(_minDecibels);
	
}

JS_SETTER(AnalyserNode::minDecibelsSetter) { THIS_CHECK; SETTER_DOUBLE_ARG;
	
	CACHE_CAS(_minDecibels, v);
	
	// TODO: may be additional actions on change?
	
	emit("minDecibels", 1, &value);
	
}


JS_GETTER(AnalyserNode::maxDecibelsGetter) { THIS_CHECK;
	
	RET_NUM(_maxDecibels);
	
}

JS_SETTER(AnalyserNode::maxDecibelsSetter) { THIS_CHECK; SETTER_DOUBLE_ARG;
	
	CACHE_CAS(_maxDecibels, v);
	
	// TODO: may be additional actions on change?
	
	emit("maxDecibels", 1, &value);
	
}


JS_GETTER(AnalyserNode::smoothingTimeConstantGetter) { THIS_CHECK;
	
	RET_NUM(_smoothingTimeConstant);
	
}

JS_SETTER(AnalyserNode::smoothingTimeConstantSetter) { THIS_CHECK; SETTER_DOUBLE_ARG;
	
	CACHE_CAS(_smoothingTimeConstant, v);
	
	// TODO: may be additional actions on change?
	
	emit("smoothingTimeConstant", 1, &value);
	
}
