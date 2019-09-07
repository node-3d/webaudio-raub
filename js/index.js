'use strict';

module.exports = {
	AudioBuffer: require('./audio-buffer'),
	AudioContext: require('./audio-context'),
	AudioParam: require('./audio-param'),
	...(require('./nodes')),
};
