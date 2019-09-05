'use strict';

const { inspect, inherits } = require('util');

const { AudioContext } = require('../core');
const JsBaseAudioContext = require('./base-audio-context');

console.log('AC', AudioContext, JsBaseAudioContext);
inherits(AudioContext, JsBaseAudioContext);


function JsAudioContext(opts = {}) {
	if (opts.sampleRate) {
		AudioContext.call(this, opts.sampleRate);
	} else {
		console.log('audio-context.js', 'cs1');
		AudioContext.call(this);
		console.log('audio-context.js', 'cs2');
	}
}
inherits(JsAudioContext, AudioContext);


JsAudioContext.prototype = {
	
	[inspect.custom]() { return this.toString(); },
	
	toString() {
		return 'AudioContext {}';
	},
	
};


module.exports = JsAudioContext;
