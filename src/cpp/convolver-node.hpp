#ifndef _CONVOLVER_NODE_HPP_
#define _CONVOLVER_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class ConvolverNode : public AudioNode {
	
public:
	
	~ConvolverNode();
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	// Make a new instance from C++ land
	explicit ConvolverNode(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	explicit ConvolverNode(Napi::Object context);
	
	static Napi::FunctionReference _ctorConvolverNode;
	
	bool _isDestroyed;
	
	Napi::ObjectReference _buffer;
	
	
// JS methods and props, available through V8 APIs
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	JS_GETTER(bufferGetter);
	JS_SETTER(bufferSetter);
	
	JS_GETTER(normalizeGetter);
	JS_SETTER(normalizeSetter);
	
};


#endif // _CONVOLVER_NODE_HPP_
