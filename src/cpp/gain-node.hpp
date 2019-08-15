#ifndef _GAIN_NODE_HPP_
#define _GAIN_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class GainNode : public Napi::ObjectWrap<GainNode> {
	
public:
	
	~GainNode();
	GainNode(const Napi::CallbackInfo &info);
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	// Make a new instance from C++ land
	explicit GainNode(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
protected:
	
	explicit GainNode(Napi::Object context);
	
	static Napi::FunctionReference _ctorGainNode;
	
	bool _isDestroyed;
	
	Napi::ObjectReference _gain;
	
	
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	JS_GETTER(gainGetter);
	
};


#endif // _GAIN_NODE_HPP_
