'use strict';


const util = require('util');

// Add deps dll dirs
require('deps-labsound-raub');

const core = require('./binary/waa');
const { AudioContext, BaseAudioContext/*, GainNode, OscillatorNode*/ } = core;

console.log('AudioContext', AudioContext);
console.log('BaseAudioContext', BaseAudioContext);
console.log('AudioContext', Object.getPrototypeOf(AudioContext));
// AudioContext.prototype.createGain = function() {
// 	return new GainNode();
// };

// AudioContext.prototype.createOscillator = function() {
// 	return new OscillatorNode();
// };


AudioContext.prototype[util.inspect.custom] = function() {
	return `AudioContext { }`;
};

module.exports = core;
