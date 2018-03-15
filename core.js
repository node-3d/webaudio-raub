'use strict';


const util = require('util');

// Add deps dll dirs
require('deps-labsound-raub');

const { AudioContext, GainNode, OscillatorNode } = require('./binary/waa');


AudioContext.prototype.createGain = function() {
	return new GainNode();
};

AudioContext.prototype.createOscillator = function() {
	return new OscillatorNode();
};


AudioContext.prototype[util.inspect.custom] = function() {
	return `AudioContext { }`;
};

module.exports = require('./binary/waa');
