#ifndef _CONVOLVER_NODE_HPP_
#define _CONVOLVER_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class ConvolverNode : public Napi::ObjectWrap<ConvolverNode> {
	
public:
	
	~ConvolverNode();
	ConvolverNode(const Napi::CallbackInfo &info);
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	// Make a new instance from C++ land
	explicit ConvolverNode(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
protected:
	
	explicit ConvolverNode(Napi::Object context);
	
	static Napi::FunctionReference _constructor;
	
	bool _isDestroyed;
	
	Napi::ObjectReference _buffer;
	
	
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	JS_GETTER(bufferGetter);
	JS_SETTER(bufferSetter);
	
	JS_GETTER(normalizeGetter);
	JS_SETTER(normalizeSetter);
	
};


#endif // _CONVOLVER_NODE_HPP_
