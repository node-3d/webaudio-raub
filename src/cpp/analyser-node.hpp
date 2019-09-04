#ifndef _ANALYSER_NODE_HPP_
#define _ANALYSER_NODE_HPP_


#include "common.hpp"

#include "audio-node.hpp"


class AnalyserNode : public CommonNode<AnalyserNode> {
DECLARE_ES5_CLASS(AnalyserNode, AnalyserNode);
	
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
	
	JS_DECLARE_METHOD(getFloatFrequencyData);
	JS_DECLARE_METHOD(getByteFrequencyData);
	JS_DECLARE_METHOD(getFloatTimeDomainData);
	JS_DECLARE_METHOD(getByteTimeDomainData);
	
	JS_DECLARE_GETTER(frequencyBinCount);
	
	JS_DECLARE_GETTER(fftSize);
	JS_DECLARE_SETTER(fftSize);
	
	JS_DECLARE_GETTER(minDecibels);
	JS_DECLARE_SETTER(minDecibels);
	
	JS_DECLARE_GETTER(maxDecibels);
	JS_DECLARE_SETTER(maxDecibels);
	
	JS_DECLARE_GETTER(smoothingTimeConstant);
	JS_DECLARE_SETTER(smoothingTimeConstant);
	
};


#endif // _ANALYSER_NODE_HPP_
