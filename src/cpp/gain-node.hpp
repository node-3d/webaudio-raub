#ifndef _GAIN_NODE_HPP_
#define _GAIN_NODE_HPP_

#include "common.hpp"

#include "audio-node.hpp"


class GainNode : public CommonNode<GainNode> {
DECLARE_ES5_CLASS(GainNode, GainNode);
	
public:
	static void init(Napi::Env env, Napi::Object exports);
	static Napi::Object create(Napi::Env env, Napi::Object context);
	
	explicit GainNode(const Napi::CallbackInfo &info);
	~GainNode();
	
	void _destroy();
	
private:
	Napi::ObjectReference _gain;
	
	JS_DECLARE_METHOD(GainNode, destroy);
	
	JS_DECLARE_GETTER(GainNode, gain);
	
};


#endif // _GAIN_NODE_HPP_
