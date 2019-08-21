#ifndef _CONVOLVER_NODE_HPP_
#define _CONVOLVER_NODE_HPP_

#include "common.hpp"

#include "audio-node.hpp"


class ConvolverNode : public Napi::ObjectWrap<ConvolverNode>, private CommonNode {
	
public:
	
	static void init(Napi::Env env, Napi::Object exports);
	static Napi::Object create(Napi::Env env, Napi::Object context);
	
	explicit ConvolverNode(const Napi::CallbackInfo &info);
	~ConvolverNode();
	
	void _destroy();
	
private:
	
	static Napi::FunctionReference _constructor;
	
	Napi::ObjectReference _buffer;
	
	JS_METHOD(destroy);
	
	JS_GETTER(bufferGetter);
	JS_SETTER(bufferSetter);
	
	JS_GETTER(normalizeGetter);
	JS_SETTER(normalizeSetter);
	
};


#endif // _CONVOLVER_NODE_HPP_
