'use strict';


const util = require('util');

// Add deps dll dirs
require('deps-labsound-raub');

const core = require('./binary/waa');
const { AudioContext, BaseAudioContext } = core;

console.log('AudioContext', AudioContext);
console.log('BaseAudioContext', BaseAudioContext);
console.log('AudioContext', Object.getPrototypeOf(AudioContext));


AudioContext.prototype[util.inspect.custom] = function () {
	return 'AudioContext { }';
};

module.exports = core;
