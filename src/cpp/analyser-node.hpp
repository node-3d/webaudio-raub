#ifndef _ANALYSER_NODE_HPP_
#define _ANALYSER_NODE_HPP_


#include "common.hpp"

#include "audio-node.hpp"


class AnalyserNode : public Napi::ObjectWrap<AnalyserNode>, private CommonNode, private CommonNode {
	
public:
	
	~AnalyserNode();
	explicit AnalyserNode(const Napi::CallbackInfo &info);
	
	static void init(Napi::Env env, Napi::Object exports);
	
	
protected:
	
	uint32_t _frequencyBinCount;
	uint32_t _fftSize;
	double _minDecibels;
	double _maxDecibels;
	double _smoothingTimeConstant;
	
	
private:
	
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
