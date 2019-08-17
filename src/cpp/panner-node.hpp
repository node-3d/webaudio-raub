#ifndef _PANNER_NODE_HPP_
#define _PANNER_NODE_HPP_


#include "audio-node.hpp"

#include "audio-param.hpp"


class PannerNode : public Napi::ObjectWrap<PannerNode>, private CommonNode {
	
public:
	
	~PannerNode();
	explicit PannerNode(const Napi::CallbackInfo &info);
	
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isPannerNode(Napi::Object obj);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
protected:
	
	PannerNode(Napi::Object context, float sampleRate, const std::string &hrtf);
	
	static Napi::FunctionReference _constructor;
	
	bool _isDestroyed;
	
	Napi::ObjectReference _positionX;
	Napi::ObjectReference _positionY;
	Napi::ObjectReference _positionZ;
	Napi::ObjectReference _orientationX;
	Napi::ObjectReference _orientationY;
	Napi::ObjectReference _orientationZ;
	
	
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	JS_METHOD(setPosition);
	JS_METHOD(setOrientation);
	JS_METHOD(setVelocity);
	
	JS_GETTER(panningModelGetter);
	JS_SETTER(panningModelSetter);
	
	JS_GETTER(positionXGetter);
	
	JS_GETTER(positionYGetter);
	
	JS_GETTER(positionZGetter);
	
	JS_GETTER(orientationXGetter);
	
	JS_GETTER(orientationYGetter);
	
	JS_GETTER(orientationZGetter);
	
	JS_GETTER(distanceModelGetter);
	JS_SETTER(distanceModelSetter);
	
	JS_GETTER(refDistanceGetter);
	JS_SETTER(refDistanceSetter);
	
	JS_GETTER(maxDistanceGetter);
	JS_SETTER(maxDistanceSetter);
	
	JS_GETTER(rolloffFactorGetter);
	JS_SETTER(rolloffFactorSetter);
	
	JS_GETTER(coneInnerAngleGetter);
	JS_SETTER(coneInnerAngleSetter);
	
	JS_GETTER(coneOuterAngleGetter);
	JS_SETTER(coneOuterAngleSetter);
	
	JS_GETTER(coneOuterGainGetter);
	JS_SETTER(coneOuterGainSetter);
	
};


#endif // _PANNER_NODE_HPP_
