#ifndef _DELAY_NODE_HPP_
#define _DELAY_NODE_HPP_

#include "common.hpp"

#include "audio-node.hpp"


class DelayNode : public CommonNode<DelayNode> {
DECLARE_ES5_CLASS(DelayNode, DelayNode);
	
public:
	
	static void init(Napi::Env env, Napi::Object exports);
	static Napi::Object create(Napi::Env env, Napi::Object context);
	
	explicit DelayNode(const Napi::CallbackInfo &info);
	~DelayNode();
	
	void _destroy();
	
private:
	
	Napi::ObjectReference _delayTime;
	
	JS_DECLARE_METHOD(DelayNode, destroy);
	
	JS_DECLARE_GETTER(DelayNode, delayTime);
	
};


#endif // _DELAY_NODE_HPP_
