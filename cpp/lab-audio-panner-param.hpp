#ifndef _LAB_AUDIO_PANNER_PARAM_HPP_
#define _LAB_AUDIO_PANNER_PARAM_HPP_


#include <string>

#include <LabSound/core/AudioParam.h>

namespace lab { class PannerNode; };


class LabAudioPannerParam : public lab::AudioParam {
	
public:
	
	enum ParamName {
		positionX,
		positionY,
		positionZ,
		orientationX,
		orientationY,
		orientationZ,
	};
	
	LabAudioPannerParam(const std::string &id, lab::PannerNode *target, ParamName name);
	
	float value();
	void setValue(float v);
	
	
private:
	
	lab::PannerNode *_target;
	ParamName _name;
	
	static double _inf;
	
};


#endif // _LAB_AUDIO_PANNER_PARAM_HPP_
