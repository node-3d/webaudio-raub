#ifndef _ANALYSER_NODE_HPP_
#define _ANALYSER_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class AnalyserNode : public Napi::ObjectWrap<AnalyserNode> {
	
public:
	
	~AnalyserNode();
	AnalyserNode(const Napi::CallbackInfo &info);
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isAnalyserNode(Napi::Object obj);
	
	// Make a new instance from C++ land
	explicit AnalyserNode(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
protected:
	
	AnalyserNode();
	
	static Napi::FunctionReference _constructor;
	
	bool _isDestroyed;
	
	uint32_t _frequencyBinCount;
	uint32_t _fftSize;
	double _minDecibels;
	double _maxDecibels;
	double _smoothingTimeConstant;
	
	
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	JS_METHOD(getFloatFrequencyData);
	JS_METHOD(getByteFrequencyData);
	JS_METHOD(getFloatTimeDomainData);
	JS_METHOD(getByteTimeDomainData);
	
	JS_GETTER(frequencyBinCountGetter);
	
	JS_GETTER(fftSizeGetter);
	JS_SETTER(fftSizeSetter);
	
	JS_GETTER(minDecibelsGetter);
	JS_SETTER(minDecibelsSetter);
	
	JS_GETTER(maxDecibelsGetter);
	JS_SETTER(maxDecibelsSetter);
	
	JS_GETTER(smoothingTimeConstantGetter);
	JS_SETTER(smoothingTimeConstantSetter);
	
};


#endif // _ANALYSER_NODE_HPP_
