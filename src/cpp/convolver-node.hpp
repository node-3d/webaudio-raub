#ifndef _CONVOLVER_NODE_HPP_
#define _CONVOLVER_NODE_HPP_

#include "common.hpp"

#include "audio-node.hpp"


class ConvolverNode : public CommonNode<ConvolverNode> {
	
public:
	
	static void init(Napi::Env env, Napi::Object exports);
	static Napi::Object create(Napi::Env env, Napi::Object context);
	
	explicit ConvolverNode(const Napi::CallbackInfo &info);
	~ConvolverNode();
	
	void _destroy();
	
private:
	
	static Napi::FunctionReference _constructor;
	
	Napi::ObjectReference _buffer;
	
	JS_DECLARE_METHOD(destroy);
	
	JS_DECLARE_GETTER(buffer);
	JS_DECLARE_SETTER(buffer);
	
	JS_DECLARE_GETTER(normalize);
	JS_DECLARE_SETTER(normalize);
	
};


#endif // _CONVOLVER_NODE_HPP_
