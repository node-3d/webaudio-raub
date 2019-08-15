#ifndef _IIR_FILTER_NODE_HPP_
#define _IIR_FILTER_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class IIRFilterNode : public Napi::ObjectWrap<IIRFilterNode> {
	
public:
	
	~IIRFilterNode();
	IIRFilterNode(const Napi::CallbackInfo &info);
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isIIRFilterNode(Napi::Object obj);
	
	// Make a new instance from C++ land
	explicit IIRFilterNode(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
protected:
	
	IIRFilterNode();
	
	static Napi::FunctionReference _ctorIIRFilterNode;
	
	bool _isDestroyed;
	
	
	
	
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	JS_METHOD(getFrequencyResponse);
	
};


#endif // _IIR_FILTER_NODE_HPP_
