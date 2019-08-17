#ifndef _IIR_FILTER_NODE_HPP_
#define _IIR_FILTER_NODE_HPP_


#include "common.hpp"

#include "audio-node.hpp"


class IIRFilterNode : public Napi::ObjectWrap<IIRFilterNode>, private CommonNode {
	
public:
	
	~IIRFilterNode();
	explicit IIRFilterNode(const Napi::CallbackInfo &info);
	
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isIIRFilterNode(Napi::Object obj);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
protected:
	
	IIRFilterNode();
	
	static Napi::FunctionReference _constructor;
	
	bool _isDestroyed;
	
	
	
	
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	JS_METHOD(getFrequencyResponse);
	
};


#endif // _IIR_FILTER_NODE_HPP_
