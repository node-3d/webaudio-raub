'use strict';

const { inspect, inherits } = require('util');

const { AudioContext } = require('../core');
const JsBaseAudioContext = require('./base-audio-context');


inherits(AudioContext, JsBaseAudioContext);


function JsAudioContext(opts = {}) {
	if (opts.sampleRate) {
		AudioContext.call(this, opts.sampleRate);
	} else {
		console.log('xxx1');
		AudioContext.call(this);
		console.log('xxx');
	}
}

JsAudioContext.prototype = {
	
	[inspect.custom]() { return this.toString(); },
	
	toString() {
		return 'AudioContext {}';
	},
	
};

inherits(JsAudioContext, AudioContext);

module.exports = JsAudioContext;
