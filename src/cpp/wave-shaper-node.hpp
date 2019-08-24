#ifndef _WAVE_SHAPER_NODE_HPP_
#define _WAVE_SHAPER_NODE_HPP_


#include "common.hpp"

#include "audio-node.hpp"


class WaveShaperNode : public CommonNode<WaveShaperNode> {
	
public:
	
	~WaveShaperNode();
	explicit WaveShaperNode(const Napi::CallbackInfo &info);
	
	static void init(Napi::Env env, Napi::Object exports);
	
	
protected:
	
	WaveShaperNode();
	
	Napi::ObjectReference _curve;
	std::string _oversample;
	
	
private:
	
	JS_GETTER(curveGetter);
	JS_SETTER(curveSetter);
	
	JS_GETTER(oversampleGetter);
	JS_SETTER(oversampleSetter);
	
};


#endif // _WAVE_SHAPER_NODE_HPP_
