'use strict';

const { inspect, inherits } = require('util');

const { AudioContext } = require('../core');
const JsBaseAudioContext = require('./base-audio-context');


inherits(AudioContext, JsBaseAudioContext);


function JsAudioContext(opts = {}) {
	if (opts.sampleRate) {
		AudioContext.call(this, opts.sampleRate);
	} else {
		console.log('AudioContext this', this, JsAudioContext.prototype, AudioContext.prototype);

		AudioContext.call(this);
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
