#ifndef _PANNER_NODE_HPP_
#define _PANNER_NODE_HPP_

#include "common.hpp"

#include "audio-node.hpp"
#include "audio-param.hpp"


class PannerNode : public CommonNode<PannerNode> {
	
public:
	
	static void init(Napi::Env env, Napi::Object exports);
	static Napi::Object create(Napi::Env env, Napi::Object context);
	
	explicit PannerNode(const Napi::CallbackInfo &info);
	~PannerNode();
	
	void _destroy();
	
private:
	
	static Napi::FunctionReference _constructor;
	
	Napi::ObjectReference _positionX;
	Napi::ObjectReference _positionY;
	Napi::ObjectReference _positionZ;
	Napi::ObjectReference _orientationX;
	Napi::ObjectReference _orientationY;
	Napi::ObjectReference _orientationZ;
	
	JS_DECLARE_METHOD(destroy);
	
	JS_DECLARE_METHOD(setPosition);
	JS_DECLARE_METHOD(setOrientation);
	JS_DECLARE_METHOD(setVelocity);
	
	JS_DECLARE_GETTER(panningModel);
	JS_DECLARE_SETTER(panningModel);
	
	JS_DECLARE_GETTER(positionX);
	
	JS_DECLARE_GETTER(positionY);
	
	JS_DECLARE_GETTER(positionZ);
	
	JS_DECLARE_GETTER(orientationX);
	
	JS_DECLARE_GETTER(orientationY);
	
	JS_DECLARE_GETTER(orientationZ);
	
	JS_DECLARE_GETTER(distanceModel);
	JS_DECLARE_SETTER(distanceModel);
	
	JS_DECLARE_GETTER(refDistance);
	JS_DECLARE_SETTER(refDistance);
	
	JS_DECLARE_GETTER(maxDistance);
	JS_DECLARE_SETTER(maxDistance);
	
	JS_DECLARE_GETTER(rolloffFactor);
	JS_DECLARE_SETTER(rolloffFactor);
	
	JS_DECLARE_GETTER(coneInnerAngle);
	JS_DECLARE_SETTER(coneInnerAngle);
	
	JS_DECLARE_GETTER(coneOuterAngle);
	JS_DECLARE_SETTER(coneOuterAngle);
	
	JS_DECLARE_GETTER(coneOuterGain);
	JS_DECLARE_SETTER(coneOuterGain);
	
};


#endif // _PANNER_NODE_HPP_
