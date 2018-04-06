#ifndef _LAB_AUDIO_LISTENER_PARAM_HPP_
#define _LAB_AUDIO_LISTENER_PARAM_HPP_


#include <string>

#include <LabSound/core/AudioParam.h>

namespace lab { class AudioListener; };


class LabAudioListenerParam : public lab::AudioParam {
	
public:
	
	enum ParamName {
		positionX,
		positionY,
		positionZ,
		forwardX,
		forwardY,
		forwardZ,
		upX,
		upY,
		upZ,
	};
	
	LabAudioListenerParam(const std::string &id, lab::AudioListener *target, ParamName name);
	
	float value();
	void setValue(float v);
	
	
private:
	
	lab::AudioListener *_target;
	ParamName _name;
	
	static double _inf;
	
};


#endif // _LAB_AUDIO_LISTENER_PARAM_HPP_
