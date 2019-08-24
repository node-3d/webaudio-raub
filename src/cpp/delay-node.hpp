#ifndef _DELAY_NODE_HPP_
#define _DELAY_NODE_HPP_

#include "common.hpp"

#include "audio-node.hpp"


class DelayNode : public CommonNode<DelayNode> {
	
public:
	
	static void init(Napi::Env env, Napi::Object exports);
	static Napi::Object create(Napi::Env env, Napi::Object context);
	
	explicit DelayNode(const Napi::CallbackInfo &info);
	~DelayNode();
	
	void _destroy();
	
private:
	
	static Napi::FunctionReference _constructor;
	
	Napi::ObjectReference _delayTime;
	
	JS_METHOD(destroy);
	
	JS_GETTER(delayTimeGetter);
	
};


#endif // _DELAY_NODE_HPP_
